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

    RegisterConverter_QVariant<bool>();

    RegisterConverter_QVariant<quint64>();
    RegisterConverter_QVariant<quint32>();
    RegisterConverter_QVariant<quint16>();
    RegisterConverter_QVariant<quint8>();

    RegisterConverter_QVariant<qint64>();
    RegisterConverter_QVariant<qint32>();
    RegisterConverter_QVariant<qint16>();
    RegisterConverter_QVariant<qint8>();

    RegisterConverter_QVariant<double>();
    RegisterConverter_QVariant<float>();



     RegisterConverter_QString<qint32>();

}

// int OptionalConverters::ToNullable_MetaTypeId(int k)
// {
//     if(!_toOpt.contains(k)) return -1;
//     return _toOpt.value(k);
// }


template<typename T>
void OptionalConverters::RegisterConverter_QVariant(){
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
