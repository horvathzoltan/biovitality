#ifndef MAINVIEWMODEL_H
#define MAINVIEWMODEL_H

#include <QtGlobal>
#include <QList>
#include <QColor>

class MainViewModel
{
public:

    struct DoWorkModel{
        int i;
    };

    struct StringModel{
        QString str;
    };

    struct FileNameModel{
        QString fileName;
        bool isCanceled;
    };

};


#endif // MAINVIEWMODEL_H
