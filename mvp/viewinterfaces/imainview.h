#ifndef IMAINVIEW_H
#define IMAINVIEW_H

#include "mvp/viewmodels/mainviewmodel.h"

#include <mvp/viewinterfaces/iview.h>
#include <QColor>
#include <QPointF>
#include <QRect>
#include <QSet>

class IMainView : public IView
{
public:
    virtual void set_DoWorkRModel(const MainViewModel::StringModel& m) = 0;
    virtual MainViewModel::DoWorkModel get_DoWorkModel() =0;
    virtual MainViewModel::FileNameModel get_CSVFileName_SoldItem() = 0;
    virtual MainViewModel::FileNameModel get_CSVFileName_Address() = 0;
    virtual MainViewModel::FileNameModel get_CSVFileName_Partner() =0;

    virtual MainViewModel::FileNameModel get_CSVFileName_Country() = 0;
    virtual MainViewModel::FileNameModel get_CSVFileName_County() = 0;
    virtual MainViewModel::FileNameModel get_CSVFileName_Article() =0;

    virtual void set_StatusLine(const MainViewModel::StringModel &m) = 0;
    virtual MainViewModel::StringModel get_StatusLine() = 0;
public: // signals
//test
    virtual void PushButtonActionTriggered(IMainView *sender) = 0;
//add
    virtual void Add_SoldItem_ActionTriggered(IMainView *sender) = 0;
    virtual void Add_Address_ActionTriggered(IMainView *sender) = 0;
    virtual void Update_Address_ActionTriggered(IMainView *sender) = 0;
//import
    virtual void CimImport_ActionTriggered(IMainView *sender) = 0;
    virtual void PartnerImport_ActionTriggered(IMainView *sender) =0;
    virtual void TetelImport_ActionTriggered(IMainView *sender) = 0;
    virtual void CountryImport_ActionTriggered(IMainView *sender) = 0;
    virtual void ArticleImport_ActionTriggered(IMainView *sender) = 0;
    virtual void CountyImport_ActionTriggered(IMainView *sender) = 0;
//list
    virtual void AddressList_ActionTriggered(IMainView *sender) =0;
    virtual void PartnerList_ActionTriggered(IMainView *sender) =0;
//log
    virtual void ToClipBoard_ActionTriggered(IMainView *sender) = 0;    
    virtual void ToLogFile_ActionTriggered(IMainView *sender) = 0;
};

#endif // IMAINVIEW_H
