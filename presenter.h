#ifndef PRESENTER_H
#define PRESENTER_H

#include <QObject>


class Presenter: public QObject
{
    Q_OBJECT

public:
    explicit Presenter(QObject *parent = nullptr);
};

#endif // PRESENTER_H
