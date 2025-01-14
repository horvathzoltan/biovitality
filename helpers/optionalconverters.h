#ifndef OPTIONALCONVERTERS_H
#define OPTIONALCONVERTERS_H

#include <optional>
#include "helpers/logger.h"
#include "qtypes.h"
#include "qvariant.h"


class OptionalConverters
{
public:
    OptionalConverters();
    void RegisterAll();

    static QMap<int, int> _toOpt;

    static int ToNullable_MetaTypeId(int k);

//    static std::optional<quint64> QVariantToOptionalQuint64(const QVariant& v);
//    static QVariant OptionalQuint64ToQVariant(const std::optional<quint64>& v);

    template<typename T>
    static std::optional<T> QVariantToType(const QVariant &v);

    template<typename T>
    static QVariant OptionalTypeToQVariant(const std::optional<T> &v);

    template<typename T>
    static void RegisterQVariant();

    //
    template<typename T>
    static void RegisterQString();

    template<typename T>
    static std::optional<T> QStringToType(const QString &v);

    template<typename T>
    static QString OptionalTypeToQString(const std::optional<T> &v);
};

#endif // OPTIONALCONVERTERS_H
