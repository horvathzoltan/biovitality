#ifndef OPTIONALCONVERTERS_H
#define OPTIONALCONVERTERS_H

#include <optional>
#include "qtypes.h"
#include "qvariant.h"


class OptionalConverters
{
private:
    int _quint64;
public:
    OptionalConverters();
    void RegisterAll();

    int TypeCode_quint64(){return _quint64;}

    static std::optional<quint64> QVariantToOptionalQuint64(const QVariant& v);
    static QVariant OptionalQuint64ToQVariant(const std::optional<quint64>& v);
};

#endif // OPTIONALCONVERTERS_H
