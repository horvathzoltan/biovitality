#ifndef OPTIONALCONVERTERS_H
#define OPTIONALCONVERTERS_H

#include <optional>
#include "qtypes.h"
#include "qvariant.h"


class OptionalConverters
{
public:
    OptionalConverters();
    void RegisterAll();

    static QMap<int, int> _toOpt;

    static int ToNullable_MetaTypeId(int k);

    static std::optional<quint64> QVariantToOptionalQuint64(const QVariant& v);
    static QVariant OptionalQuint64ToQVariant(const std::optional<quint64>& v);
};

#endif // OPTIONALCONVERTERS_H
