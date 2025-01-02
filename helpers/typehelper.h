#ifndef TYPEHELPER_H
#define TYPEHELPER_H

#include <QString>
#include <typeindex>

#define GetTypeName(b) TypeHelper::GetTypeName_(QStringLiteral(#b), sizeof(b))

class TypeHelper
{
public:
    template<typename T>
    static std::type_index GetIndex(){return std::type_index(typeid(T));}

    static QString GetTypeName_(const QString& key, unsigned long l)
    {
        Q_UNUSED(l)
        return key;
    }
};

#endif // TYPEHELPER_H
