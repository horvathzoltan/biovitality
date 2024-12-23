#include "optionalconverters.h"


OptionalConverters::OptionalConverters() {}

void OptionalConverters::RegisterAll()
{
    _quint64 = qRegisterMetaType<std::optional<quint64>>();

    QMetaType::registerConverter<QVariant, std::optional<quint64>>(
        &OptionalConverters::QVariantToOptionalQuint64);
    QMetaType::registerConverter<std::optional<quint64>, QVariant>(
        &OptionalConverters::OptionalQuint64ToQVariant);
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
