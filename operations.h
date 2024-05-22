#ifndef OPERATIONS_H
#define OPERATIONS_H

#include "helpers/logger.h"
#include "presenter.h"

#include <QObject>
#include <QUuid>
#include <QWidget>
#include <Singleton.h>

class Operations :public Singleton<Operations>
{
public:    
    class Operation{
        QUuid id;
        Presenter presenter;
        QWidget view;
    };

public:
    void foo(){
        zInfo("foo");
    }
};

#endif // OPERATIONS_H
