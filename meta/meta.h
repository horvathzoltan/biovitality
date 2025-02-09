#ifndef META_H
#define META_H

#include <typeindex>

#include <QList>
#include <QMetaType>
#include <QString>
#include <QVariant>
#include "helpers/logger.h"
#include "metafield.h"
#include "metavalue.h"
#include "helpers/sqlhelper.h"
#include "helpers/typehelper.h"


#define AddMetaField(b) _meta.AddField(#b, QMetaType::fromType<decltype(_meta._instance.b)>(), (char*)(&_meta._instance.b));
#define AddMetaBase(b) _meta.AddBaseName(#b, sizeof(b));

//#define AddRowToField(b,c) Add_RowToField(#b, c); {(void)_meta._instance.b;}
#define FieldName(t, b) TypeHelper::GetTypeName_(QStringLiteral(#b), sizeof(t::Meta()._instance.b))
#define AddRowToField(a,b,c) if(_meta.Contains(#b)){a.Add_RowToField(#b, c); {(void)_meta._instance.b;}} else {zWarning(QStringLiteral("MetaField is not exists: ")+#b);}

//
//#define SetName(t, b) SetName_(QStringLiteral(#b), sizeof(t::Meta()._instance.b))
#define SetName(t, b) SetName_(FieldName(t,b))
#define AddMetaReference_1N(t, b, r, c) AddMetaRef_<r>(FieldName(t,b), #r, FieldName(r,c), RefType::R_1N)
#define AddMetaReference_NM(t, b, r, c) AddMetaRef_<r>(FieldName(t,b), #r, FieldName(r,c), RefType::R_NM)
#define DeleteMetaReference(t, b, r) DeleteMetaRef_<r>(FieldName(t,b))

#define CheckRef(t, b, r) CheckRef_<t,r>(FieldName(t,b))
#define Get_DataRowDefaultModel(t, b, r) Get_DataRowDefaultModel_<t,r>(FieldName(t,b))
#define Copy_DataRowDefaultModel(v, t, b) Copy_DataRowDefaultModel_(v, FieldName(t,b))

// class optConv{

//     quint64 ToUint64(bool *ok = nullptr) const
//     {
//          const bool canConvertSafely = l < std::numeric_limits<int>::max();
//     }
// }

class RefBase{
public:
    RefBase(){}
protected:
    int _fieldIx;
    QString _refTypeName;
    int _refIx;
    std::type_index _a1 = std::type_index(typeid(void*));
    void* _metaInstancePtr;
    RefType _refType;

public:
    RefBase(int f, const QString& rt, int rf,RefType refType)
    {
        _fieldIx = f;
        _refTypeName = rt;
        _refIx = rf;
        _metaInstancePtr = nullptr;
        _refType = refType;
    }    

    std::type_index a1(){return _a1;}
    QString refTypeName(){ return _refTypeName;}
    int fieldIx(){return _fieldIx;}
};

template<typename T>
class Ref : public RefBase
{
private:
    Ref(){}

public:

    Ref(int f, const QString& rt, int rf, RefType refType) : RefBase(f, rt, rf, refType)
    {
        _metaInstancePtr = &(T::Meta()._instance);//Address();
        _a1 = std::type_index(typeid(T));
    }

    T* metaInstance(){return reinterpret_cast<T*>(_metaInstancePtr);}
};

struct RefContainerKey
{
private:
    std::type_index _typeIndex = std::type_index(typeid(void*));
    int _fieldIndex = -1;

    RefContainerKey(){};

public:
    RefContainerKey(const std::type_index& a, int b)
    {
        _typeIndex = a;
        _fieldIndex = b;
    };

    bool
    operator<(const RefContainerKey& b) const{
        if(_typeIndex == b._typeIndex){
            return _fieldIndex < b._fieldIndex;
        }
        return _typeIndex<b._typeIndex;
    }

    QString name(){return _typeIndex.name();}
};

class RefContainer{
private:
    QMap<RefContainerKey, void*> _references;

    template<typename R>
    static RefContainerKey GetKey(int ix){
        RefContainerKey r(std::type_index(typeid(R)), ix);
        return r;
    }

public:
    template< typename R>
    void Add(int fIx, const QString& rt, const QString& rf, RefType refType){
        //int fIx = T::GetMetaFieldIx(f);
        int rIx = R::Meta().GetMetaFieldIx(rf);

        Ref<R>* r = new Ref<R>(fIx, rt, rIx, refType);
        RefContainerKey key = GetKey<Ref<R>>(fIx);
        _references.insert(key, r);

        zInfo("RefContainer added: "+QString(key.name()));
    }

    template<typename R>
    void Delete(int fIx){
        RefContainerKey key = GetKey<Ref<R>>(fIx);
        if(_references.contains(key)){
            void* b = _references.take(key);
            Ref<R>* e = reinterpret_cast<Ref<R>*>(b);
            delete e;

            zInfo("RefContainer deleted: "+QString(key.name()));
        } else{
            zWarning("RefContainer cannot delete: "+QString(key.name()));
        }
    }

    template<typename R>
    Ref<R>* Get(int fIx)
    {
        RefContainerKey key = GetKey<Ref<R>>(fIx);
        if(_references.contains(key))
        {
            void* b = _references.value(key);
            Ref<R>* e = reinterpret_cast<Ref<R>*>(b);
            zInfo("RefContainer find:" +e->refTypeName());
            return e;
        } else{
            zWarning("RefContainer cannnot found: "+QString(key.name()));
        }
        return nullptr;
    }
};

class IdMegnev{
public:
    int id = -1;
    QString name;
    QString code;
};

struct IdMegnevIxs{
public:
    int id = -1;
    QList<int> megnev;
    int code = -1;
};

struct DataRowDefaultModel{
private:
    DataRowDefaultModel(){};
    QString _name;
    QList<IdMegnev> _values;
public:
    DataRowDefaultModel(const QString& n){ _name=n;};
    void SetName_(const QString& v){ _name = v;}
    void AddValue(const IdMegnev& v){ _values.append(v);}
    QString name(){return _name;}
    const QList<IdMegnev>& values(){return _values;}

    bool IsValid(){return !_name.isEmpty();}

    QString GetMegnev(int id)
    {
        for(auto&v:_values){
            if(v.id==id) return v.name;
        }
        return {};
    }

    // void SetName_(const QString& v, unsigned long l){
    //     Q_UNUSED(l);
    //     _name = v;
    // };
};

struct FieldType{
    QMetaType declType;
    QMetaType keyType;
    QMetaType valueType;
};

template<typename T>
class MetaData{
    QList<MetaField> _fields;
    IdMegnevIxs _idMegnevIxs;
    bool _verbose = true;
public:
    T _instance;

    //QVariantList _references;
    //QList<RefBase> _references;

    RefContainer _refcontainer;

    template<typename R>
    Ref<R>* GetRef2(const QString& f)
    {
        int fIx = GetMetaFieldIx(f);
        return _refcontainer.Get<R>(fIx);
    }

    template<typename R>
    QString GetRef_FieldName(const QString& f)
    {
        int fIx = GetMetaFieldIx(f);
        Ref<R>* r1 = T::Meta().template GetRef2<R>(fIx);
        if(!r1) return {};
        int rIx = r1->fieldIx();
        if(rIx<0) return{};
        MetaField a = _fields[rIx];
        return a.name;
    }

    template<typename R>
    void AddMetaRef_(const QString& f, const QString& rt, const QString& rf, RefType refType){
        int fIx = GetMetaFieldIx(f);
        _fields[fIx].refType = refType;
        return _refcontainer.Add<R>(fIx, rt, rf, refType);
    };

    template<typename R>
    void DeleteMetaRef_(const QString& f){
        int fIx = GetMetaFieldIx(f);

        _refcontainer.Delete<R>(fIx);
    }

    // void DeleteMetaRef_All(){
    //     _refcontainer.DeleteMetaRef_All();
    // }

    QString _baseName;
    QString _baseWcode;

    void SetVerbose(bool v){_verbose = v;};

    ~MetaData(){
        //T::DeleteRefs();
    }
    // QString GetFieldName(const QString& name, char* field_ptr){
    //      return name;
    //  }    

    void AddField(const QString& name, const QMetaType& t, char* field_ptr)
    {
        // if(name == "alimedCode"){
        //       zInfo("alimedCode megvan");
        // }
        if(t.id() == QMetaType::QVariant){
            zWarning("AddField: Do not use QVariant "+name+" in model!");
        }
        MetaField f;
        f.name=name;
        f.wcode = _baseWcode+"::"+f.name;
        f.type = t;
        int offset = field_ptr - (char*)(&_instance);
        f._offset = offset;

        if(_verbose){
            QString msg = QStringLiteral("AddField: ")
                          +QString::number(offset)
                          +" "+t.name() + '('+QString::number(t.sizeOf())+")"
                          +" "+name
                          +" to "+ _baseName;
            zInfo(msg);
        }

        _fields.append(f);        
    }

    bool Contains(const QString& name)
    {
        for(auto&a:_fields) if(a.name == name) return true;
        return false;
    }

    // Gets field names separated with comma
    // SqlRepo: Get, GetAll
    QString GetFieldNames(){
        if(_fields.isEmpty()) return {};
        QString e;
        for(auto&a:_fields){
            //if(a.name.toLower()=="id") continue;
            if(!e.isEmpty()) e+=",";
            e+=a.name;
        }
        return e;
    }

    void AddBaseName(char const *y, unsigned long){
        _baseName = QString(y);
        _baseWcode = "WCodes::"+_baseName;
    }

    QString GetBaseTypeName() {
        return _baseName;
    }

    // QString GetFieldList_UPDATE(){
    //     if(_fields.isEmpty()) return {};
    //     QString e;
    //     int i = 0;
    //     for(auto&a:_fields){
    //         if(a.name.toLower()=="id") continue;
    //         if(!e.isEmpty()) e+=",";
    //         e+=a.name+"=: "+a.name;
    //     }
    //     return e;
    // }

private:
    MetaField* GetMetaField(const QString& name){
        for(auto&a:_fields){
            if(a.name==name) return &a;
        }
        return nullptr;
    }

public:
    // AddMetaRef-ben használjuk az indexét
    int GetMetaFieldIx(const QString& name){
        int L= _fields.count();
        for(int i=0;i<L;i++){
            if(_fields[i].name==name) return i;
        }
        return -1;
    }

    // Parses T from a list of MetaValue
    // SqlRepo: Get, GetAll
    T FromMetaValues(const QList<MetaValue>& metaValues){
        T s;
        for(auto&m:metaValues){
            // if(m.metaField_name == "postalCode"){
            //       zInfo("postalCode megvan");
            // }
            MetaField* f = GetMetaField(m.metaField_name);
            if(f){
                char* ptr = f->GetPtr((char*)&s);
                auto typeId = f->type.id();

                if(typeId==QMetaType::QVariant){
                    qWarning("Do not use QVariant in model!");                  
                }
                else if(typeId < QMetaType::User)
                {
                    // mivel a konverter QMetaTypeok közt működik
                    // ha a qvariant egyszerű típusú értéket tárol
                    // QVariant értékét kell átadni a konverternek
                    // kell konvertálni
                    QMetaType qvm = m.value.metaType();

                    QString msg2 = QString(qvm.name())+" to "+ f->type.name();

                    bool cc = QMetaType::canConvert(qvm, f->type);
                    if(cc)
                    {
                        QMetaType::convert(qvm, m.value.constData(), f->type, ptr);
                    } else{
                        QString msg = QStringLiteral("No converter registered from ") +msg2;
                        zWarning(msg);
                    }
                }
                else
                {
                    // mivel a konverter QMetaTypeok közt működik
                    // és mivel az optionalból qvariantot csinálunk
                    // ezért a qvariantot MAGÁT kell átadni a konverternek
                    // QVariant értékű QVariantoit user típusba
                    QMetaType qvm = QMetaType(QMetaType::QVariant);

                    QMetaType qvm2 = m.value.metaType();

                    QString msg2 = QString(qvm.name())+"("+qvm2.name()+") to "+ f->type.name();

                    bool cc = QMetaType::canConvert(qvm, f->type);
                    if(cc)
                    {
                        QMetaType::convert(qvm, &m.value, f->type, ptr);
                    } else{
                        QString msg = QStringLiteral("No converter registered from ") +msg2;
                        zWarning(msg);
                    }
                }
            }
        }
        return s;
    }

    QList<MetaValue> ToMetaValues(const T& s){
        QList<MetaValue> m;

        for (MetaField &f : _fields) {
            MetaValue mv =  f.GetMetaValue((char*)(&s));
            m.append(mv);
        }

        return m;
    }

    QList<QList<MetaValue>> ToMetaValueList(const QList<T>& values){
        QList<QList<MetaValue>> e;

        for(auto&a:values)
        {
            QList<MetaValue> m = ToMetaValues(a);
            e.append(m);
        }

        return e;
    }

    QList<SQLHelper::SQLParam> ToSQLParams(const T* s){
        QList<SQLHelper::SQLParam> m;
        if(s){
            int i=1;
            for (MetaField &f : _fields) {
                bool isId = f.name.toLower()=="id";
                MetaValue mv =  f.GetMetaValue((char*)s);

                SQLHelper::SQLParam p;
                p.paramName = isId?"id":"p"+QString::number(i++);
                p.fieldName = mv.metaField_name;
                p.fieldValue = mv.value;
                m.append(p);
            }
        }
        return m;
    }

    QList<MetaFieldBase> ToMetaFieldBases()
    {
        QList<MetaFieldBase> m;
        for (auto&f : _fields) {
            m.append(f);
        }
        return m;
    }

    
    void MetaIdMegnevIndex(int indexId, const QList<int> m, int c){
        _idMegnevIxs.id = indexId;
        _idMegnevIxs.megnev = m;
        _idMegnevIxs.code = c;
    }
    
    IdMegnev ToIdMegnev(const T* s){
        IdMegnev e;
        if(_idMegnevIxs.id>-1){
            MetaField idf = _fields[_idMegnevIxs.id];
            MetaValue mv =  idf.GetMetaValue((char*)s);
            e.id = mv.value.toInt();
        }

        e.name.clear();
        for(auto &megnev:_idMegnevIxs.megnev){
            if(megnev>-1){
                MetaField idn = _fields[megnev];
                MetaValue mv2 =  idn.GetMetaValue((char*)s);
                if(!e.name.isEmpty()) e.name+=",";
                e.name += mv2.value.toString();
            }
        }

        if(_idMegnevIxs.code>-1){
            MetaField idc = _fields[_idMegnevIxs.code];
            MetaValue mv3 =  idc.GetMetaValue((char*)s);
            e.code = mv3.value.toString();
        }
        return e;


    }


    DataRowDefaultModel ToIdMegnevs(const QList<T>& data){
        DataRowDefaultModel e(_baseName);

        for(auto&a:data){
            IdMegnev i = ToIdMegnev(&a);
            e.AddValue(i);
        }

        return e;
    }

    // GUI_ADD
    MetaValue GetMetaValue(const T* s, const QString& fieldName){
        if(!s) return MetaValue("","",QMetaType(), RefType::None);
        //MetaField* field = T::Meta().GetMetaField(fieldName);
        MetaField* field = GetMetaField(fieldName);
        if(!field) return MetaValue("","",QMetaType(), RefType::None);
        MetaValue value = field->GetMetaValue((char*)s);
        return value;
    }

    QVariant GetValue(const T* s, const QString& fieldName){
        if(!s) return {};
        //MetaField* field = T::Meta().GetMetaField(fieldName);
        MetaField* field = GetMetaField(fieldName);
        if(!field) return {};
        QVariant value = field->GetValue((char*)s);
        return value;
    }

};



#endif // META_H
