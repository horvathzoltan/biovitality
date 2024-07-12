#ifndef DATAROWWIDGET_H
#define DATAROWWIDGET_H

#include <QLabel>
#include <QLineEdit>
#include <QWidget>

class DataRowWidget: public QWidget
{
    Q_OBJECT

private:
    QLabel* _label;
    QLineEdit* _edit;
public:
    DataRowWidget(const QString& label, int w);

    ~DataRowWidget();
};

#endif // DATAROWWIDGET_H
