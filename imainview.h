#ifndef IMAINVIEW_H
#define IMAINVIEW_H

#include "mainviewmodel.h"

#include <IView.h>
#include <QColor>
#include <QPointF>
#include <QRect>
#include <QSet>

class IMainView : public IView
{
public:
    virtual void set_DoWorkRModel(const MainViewModel::StringModel& m) = 0;
    virtual MainViewModel::DoWorkModel get_DoWorkModel() =0;
    virtual MainViewModel::StringModel get_TetelCSVFileName() = 0;
    virtual MainViewModel::StringModel get_CimCSVFileName() = 0;
    virtual void set_StatusLine(const MainViewModel::StringModel &m) = 0;
    virtual MainViewModel::StringModel get_StatusLine() = 0;
public: // signals
    virtual void PushButtonActionTriggered(IMainView *sender) = 0;
    virtual void TetelImportActionTriggered(IMainView *sender) = 0;
    virtual void AddSoldItemActionTriggered(IMainView *sender) = 0;
    virtual void CimImport_ActionTriggered(IMainView *sender) = 0;
    virtual void ToClipBoard_ActionTriggered(IMainView *sender) = 0;
    virtual void ToLogFile_ActionTriggered(IMainView *sender) = 0;
};

#endif // IMAINVIEW_H
