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

    //_toOpt.insert(QMetaType::Type::QReal, qRegisterMetaType<std::optional<qreal>>());
    _toOpt.insert(QMetaType::Type::Double, qRegisterMetaType<std::optional<double>>());
    _toOpt.insert(QMetaType::Type::Float, qRegisterMetaType<std::optional<float>>());

    Register<bool>();

    Register<quint64>();
    Register<quint32>();
    Register<quint16>();
    Register<quint8>();

    Register<qint64>();
    Register<qint32>();
    Register<qint16>();
    Register<qint8>();

    Register<double>();
    Register<float>();

    //quint64
    // QMetaType::registerConverter<QVariant, std::optional<quint64>>(
    //     &OptionalConverters::QVariantToOptionalQuint64);
    // QMetaType::registerConverter<std::optional<quint64>, QVariant>(
    //     &OptionalConverters::OptionalQuint64ToQVariant);

    //quint64
    // QMetaType::registerConverter<QVariant, std::optional<quint64>>(
    //     &OptionalConverters::QVariantToType<quint64>);
    // QMetaType::registerConverter<std::optional<quint64>, QVariant>(
    //     &OptionalConverters::OptionalTypeToQVariant<quint64>);

    //quint32
    // QMetaType::registerConverter<QVariant, std::optional<quint32>>(
    //     &OptionalConverters::QVariantToType<quint32>);
    // QMetaType::registerConverter<std::optional<quint32>, QVariant>(
    //     &OptionalConverters::OptionalTypeToQVariant<quint32>);

    //int
    // QMetaType::registerConverter<QVariant, std::optional<qint32>>(
    //     &OptionalConverters::QVariantToType<qint32>);
    // QMetaType::registerConverter<std::optional<qint32>, QVariant>(
    //      &OptionalConverters::OptionalTypeToQVariant<qint32>);
}

int OptionalConverters::ToNullable_MetaTypeId(int k)
{
    if(!_toOpt.contains(k)) return -1;
    return _toOpt.value(k);
}

// std::optional<quint64> OptionalConverters::QVariantToOptionalQuint64(const QVariant &v)
// {
//     if(!v.isValid()) return std::optional<quint64>();
//     if(v.isNull()) return std::optional<quint64>();
//     bool ok;
//     qulonglong e = v.toULongLong(&ok);
//     return (ok)?std::optional<quint64>(e):std::optional<quint64>();
// }

// QVariant OptionalConverters::OptionalQuint64ToQVariant(const std::optional<quint64> &v)
// {
//     if(!v.has_value()) return {};
//     return QVariant(v.value());
// }



template<typename T>
void OptionalConverters::Register(){
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
