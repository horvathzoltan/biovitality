#include "stringhelper.h"
#include <QRegularExpression>

StringHelper::StringHelper() {}

QString StringHelper::Normalize(const QString s)
{
    QString s2 = s.normalized(QString::NormalizationForm_KD)
                     //.toLatin1()
                     .remove(QRegularExpression("[^a-zA-Z\\d\\s]"))
                     .toLower();
    return s2;
}


QStringList StringHelper::Normalize(const QStringList strings)
{
    QStringList e;

    for(auto&s:strings){
        QString s2 = Normalize(s);
        e.append(s2);
    }

    return e;
}
