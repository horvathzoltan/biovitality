#ifndef DATAROWWIDGET_H
#define DATAROWWIDGET_H

#include <QLabel>
#include <QLineEdit>
#include <QSpacerItem>
#include <QWidget>

#include <bi/meta/meta.h>

class DataRowWidget: public QWidget
{
    Q_OBJECT

private:
    QLabel* _label;
    QLineEdit* _edit;
    QSpacerItem* _spacer;
    MetaValue _metaValue {"", "", QMetaType()};
public:
    DataRowWidget(const MetaValue& m, int w,bool isLight);
    MetaValue metaValue(){return _metaValue;}
    ~DataRowWidget();
};

#endif // DATAROWWIDGET_H
