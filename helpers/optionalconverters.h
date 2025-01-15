#ifndef OPTIONALCONVERTERS_H
#define OPTIONALCONVERTERS_H

#include <optional>
#include "helpers/logger.h"
#include "qvariant.h"

class OptionalConverters
{
public:
    OptionalConverters();
    void RegisterAll();


    template<typename T>
    static std::optional<T> QVariantToType(const QVariant &v);

    template<typename T>
    static QVariant OptionalTypeToQVariant(const std::optional<T> &v);

    template<typename T>
    static void Register_OptionalConverter_QVariant();

    //
    template<typename T>
    static void RegisterConverter_QString();

    template<typename T>
    static std::optional<T> QStringToType(const QString &v);

    template<typename T>
    static QString OptionalTypeToQString(const std::optional<T> &v);
};

#endif // OPTIONALCONVERTERS_H
