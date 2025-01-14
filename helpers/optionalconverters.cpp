#include "optionalconverters.h"

QMap<int, int> OptionalConverters::_toOpt;

OptionalConverters::OptionalConverters() {}

void OptionalConverters::RegisterAll()
{
    _toOpt.insert(QMetaType::Type::Bool, qRegisterMetaType<std::optional<bool>>());

    _toOpt.insert(QMetaType::Type::LongLong, qRegisterMetaType<std::optional<qint64>>());
    _toOpt.insert(QMetaType::Type::Int, qRegisterMetaType<std::optional<qint32>>());
    _toOpt.insert(QMetaType::Type::Short, qRegisterMetaType<std::optional<qint16>>());
    _toOpt.insert(QMetaType::Type::Char, qRegisterMetaType<std::optional<qint8>>());

    _toOpt.insert(QMetaType::Type::ULongLong, qRegisterMetaType<std::optional<quint64>>());
    _toOpt.insert(QMetaType::Type::UInt, qRegisterMetaType<std::optional<quint32>>());
    _toOpt.insert(QMetaType::Type::UShort, qRegisterMetaType<std::optional<quint16>>());
    _toOpt.insert(QMetaType::Type::UChar, qRegisterMetaType<std::optional<quint8>>());

    _toOpt.insert(QMetaType::Type::Double, qRegisterMetaType<std::optional<double>>());
    _toOpt.insert(QMetaType::Type::Float, qRegisterMetaType<std::optional<float>>());


    RegisterQVariant<bool>();

    RegisterQVariant<quint64>();
    RegisterQVariant<quint32>();
    RegisterQVariant<quint16>();
    RegisterQVariant<quint8>();

    RegisterQVariant<qint64>();
    RegisterQVariant<qint32>();
    RegisterQVariant<qint16>();
    RegisterQVariant<qint8>();

    RegisterQVariant<double>();
    RegisterQVariant<float>();


    // _toOpt.insert(QMetaType::Type::QString, qRegisterMetaType<std::optional<qint64>>());
     _toOpt.insert(QMetaType::Type::QString, qRegisterMetaType<std::optional<qint32>>());
    // _toOpt.insert(QMetaType::Type::QString, qRegisterMetaType<std::optional<qint16>>());
    // _toOpt.insert(QMetaType::Type::QString, qRegisterMetaType<std::optional<qint8>>());

    // RegisterQString<qint64>();
     RegisterQString<qint32>();
    // RegisterQString<qint16>();
    // RegisterQString<qint8>();

}

int OptionalConverters::ToNullable_MetaTypeId(int k)
{
    if(!_toOpt.contains(k)) return -1;
    return _toOpt.value(k);
}


template<typename T>
void OptionalConverters::RegisterQVariant(){
    QMetaType::registerConverter<QVariant, std::optional<T>>(
        &OptionalConverters::QVariantToType<T>);
    QMetaType::registerConverter<std::optional<T>, QVariant>(
        &OptionalConverters::OptionalTypeToQVariant<T>);
}

template<typename T>
std::optional<T> OptionalConverters::QVariantToType(const QVariant &v)
{
    if(!v.isValid()) return std::optional<T>();
    if(v.isNull()) return std::optional<T>();

    QMetaType qvm = v.metaType();
    QMetaType f_type = QMetaType::fromType<T>();

    bool cc = QMetaType::canConvert(qvm, f_type);
    if(cc){
        T e;
        bool ok = QMetaType::convert(qvm, v.constData(), f_type, &e);
        if(!ok) return std::optional<T>();
        auto r = std::optional<T>(e);
        return r;
    }

    QString msg = QStringLiteral("Cannot convert QVariant from ")
                  +qvm.name()+" to "+ f_type.name();
    zWarning(msg);
    return {};
}

template<typename T>
QVariant OptionalConverters::OptionalTypeToQVariant(const std::optional<T> &v)
{
    if(!v.has_value()) return {};
    QVariant r = QVariant(v.value());
    return r;
}

//string

template<typename T>
void OptionalConverters::RegisterQString(){
    QMetaType::registerConverter<QString, std::optional<T>>(
        &OptionalConverters::QStringToType<T>);
    QMetaType::registerConverter<std::optional<T>, QString>(
        &OptionalConverters::OptionalTypeToQString<T>);
}

template<typename T>
std::optional<T> OptionalConverters::QStringToType(const QString &v)
{
    if(v.isEmpty()) return std::optional<T>();

    QMetaType qvm = QMetaType(QMetaType::QString);//v.metaType();
    QMetaType f_type = QMetaType::fromType<T>();

    bool cc = QMetaType::canConvert(qvm, f_type);
    if(cc){
        T e;
        bool ok = QMetaType::convert(qvm, v.constData(), f_type, &e);
        if(!ok) return std::optional<T>();
        auto r = std::optional<T>(e);
        return r;
    }

    QString msg = QStringLiteral("Cannot convert QString from ")
                  +qvm.name()+" to "+ f_type.name();
    zWarning(msg);
    return {};
}

template<typename T>
QString OptionalConverters::OptionalTypeToQString(const std::optional<T> &v)
{
    if(!v.has_value()) return {};
    T x = v.value();
    QString r = QString::number(x);
    return r;
}
