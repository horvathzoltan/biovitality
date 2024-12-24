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

    _toOpt.insert(QMetaType::Type::QReal, qRegisterMetaType<std::optional<qreal>>());
    _toOpt.insert(QMetaType::Type::Double, qRegisterMetaType<std::optional<double>>());
    _toOpt.insert(QMetaType::Type::Float, qRegisterMetaType<std::optional<float>>());

    QMetaType::registerConverter<QVariant, std::optional<quint64>>(
        &OptionalConverters::QVariantToOptionalQuint64);
    QMetaType::registerConverter<std::optional<quint64>, QVariant>(
        &OptionalConverters::OptionalQuint64ToQVariant);
}

int OptionalConverters::ToNullable_MetaTypeId(int k)
{
    if(!_toOpt.contains(k)) return -1;
    return _toOpt.value(k);
}

std::optional<quint64> OptionalConverters::QVariantToOptionalQuint64(const QVariant &v)
{
    if(!v.isValid()) return std::optional<quint64>();
    if(v.isNull()) return std::optional<quint64>();
    bool ok;
    qulonglong e = v.toULongLong(&ok);
    return (ok)?std::optional<quint64>(e):std::optional<quint64>();
}

QVariant OptionalConverters::OptionalQuint64ToQVariant(const std::optional<quint64> &v)
{
    if(v.has_value()){
        return QVariant(v.value());
    } else{
        //QVariant a(QMetaType::fromType<quint64>());
        //a.convert((QMetaType(QMetaType::ULongLong)));

        // std::variant<quint64> e;
        // auto a = QVariant::fromStdVariant(e);
        return {};
    }
    //return u;

}

