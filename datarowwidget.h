#ifndef DATAROWWIDGET_H
#define DATAROWWIDGET_H

#include <QLabel>
#include <QWidget>

class DataRowWidget: public QWidget
{
    Q_OBJECT

private:
    QLabel* _label;
public:
    DataRowWidget(const QString& label);

    ~DataRowWidget();
};

#endif // DATAROWWIDGET_H
