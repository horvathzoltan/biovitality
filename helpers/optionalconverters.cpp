#include "optionalconverters.h"

//QMap<int, int> OptionalConverters::_toOpt;

OptionalConverters::OptionalConverters() {}

void OptionalConverters::RegisterAll()
{
    qRegisterMetaType<std::optional<bool>>();

    qRegisterMetaType<std::optional<qint64>>();
    qRegisterMetaType<std::optional<qint32>>();
    qRegisterMetaType<std::optional<qint16>>();
    qRegisterMetaType<std::optional<qint8>>();

    qRegisterMetaType<std::optional<quint64>>();
    qRegisterMetaType<std::optional<quint32>>();
    qRegisterMetaType<std::optional<quint16>>();
    qRegisterMetaType<std::optional<quint8>>();

    qRegisterMetaType<std::optional<double>>();
    qRegisterMetaType<std::optional<float>>();

    //QVariant converters
    Register_OptionalConverter_QVariant<bool>();

    Register_OptionalConverter_QVariant<quint64>();
    Register_OptionalConverter_QVariant<quint32>();
    Register_OptionalConverter_QVariant<quint16>();
    Register_OptionalConverter_QVariant<quint8>();

    Register_OptionalConverter_QVariant<qint64>();
    Register_OptionalConverter_QVariant<qint32>();
    Register_OptionalConverter_QVariant<qint16>();
    Register_OptionalConverter_QVariant<qint8>();

    Register_OptionalConverter_QVariant<double>();
    Register_OptionalConverter_QVariant<float>();

    //QString converters
    RegisterConverter_QString<bool>();

    RegisterConverter_QString<qint64>();
    RegisterConverter_QString<qint32>();
    RegisterConverter_QString<qint16>();
    RegisterConverter_QString<qint8>();

    RegisterConverter_QString<quint64>();
    RegisterConverter_QString<quint32>();
    RegisterConverter_QString<quint16>();
    RegisterConverter_QString<quint8>();

    RegisterConverter_QString<double>();
    RegisterConverter_QString<float>();
}

template<typename T>
void OptionalConverters::Register_OptionalConverter_QVariant(){
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
    QMetaType o_type = QMetaType::fromType<std::optional<T>>();

    // saját típusát kell visszaadni
    if(qvm == o_type) {
        std::optional<T> a = v.value<std::optional<T>>();
        return a;
    }

    // más egyéb típusról kell konvertálni
    QMetaType f_type = QMetaType::fromType<T>();
    bool cc = QMetaType::canConvert(qvm, f_type);
    if(cc){
        T e;
        bool ok = QMetaType::convert(qvm, v.constData(), f_type, &e);
        if(!ok) return std::optional<T>();
        auto r = std::optional<T>(e);
        return r;
    }

    QString msg = QStringLiteral("Cannot convert QVariant(") +qvm.name()+") = "
                  +v.toString()+" to "+ f_type.name();
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
void OptionalConverters::RegisterConverter_QString(){
    QMetaType::registerConverter<QString, std::optional<T>>(
        &OptionalConverters::QStringToType<T>);
    QMetaType::registerConverter<std::optional<T>, QString>(
        &OptionalConverters::OptionalTypeToQString<T>);
}

// QVariant a(v);
// std::optional<T> r = QVariantToType<T>(a);
// return r;

template<typename T>
std::optional<T> OptionalConverters::QStringToType(const QString &v)
{
    if(v.isEmpty()) return std::optional<T>();

    QMetaType qvm = QMetaType(QMetaType::QString);
    QMetaType f_type = QMetaType::fromType<T>();

    bool cc = QMetaType::canConvert(qvm, f_type);
    if(cc){
        T e;
        bool ok = QMetaType::convert(qvm, &v, f_type, &e);
        if(!ok) return std::optional<T>();
        auto r = std::optional<T>(e);
        return r;
    }

    QString msg = QStringLiteral("Cannot convert QString = ")+v
                  +" to " +f_type.name();
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
