QT       += core gui charts network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# gcc -v --help 2> /dev/null | sed -n '/^ *-std=\([^<][^ ]\+\).*/ {s//\1/p}'
CONFIG += c++20

DEFINES += TARGI=$$TARGET
message( "TARGET = "$$TARGET )

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    #actions.cpp \
    bi/helpers/csvhelper.cpp \
    bi/helpers/sqlmetahelper.cpp \
    bi/models/address.cpp \
    bi/models/article.cpp \
    bi/models/county.cpp \
    bi/models/solditem.cpp \
    bi/repositories/sqlexcelrepository.cpp \
    bi/repositories/sqlrepository.cpp \
    buildnumber.cpp \
    views/dataform.cpp \
    views/datarowwidget.cpp \
    globals.cpp \
    helpers/filehelper.cpp \
    helpers/filenamehelper.cpp \
    helpers/logger.cpp \
    helpers/networkhelper.cpp \
    helpers/processhelper.cpp \
    helpers/signalhelper.cpp \
    helpers/sqlhelper.cpp \
    helpers/stringhelper.cpp \
    helpers/translator.cpp \
    main.cpp \
    presenters/mainpresenter.cpp \
    views/mainwindow.cpp \
    bi/operations.cpp \
    presenters/presenter.cpp \
    #repositories/solditemrepository.cpp \
    presenters/logpresenter.cpp \
    settings.cpp
    #model.cpp \
     #updates.cpp

HEADERS += \
    #actions.h \
    views/IView.h \
    Singleton.h \
    bi/helpers/csvhelper.h \
    bi/helpers/sqlmetahelper.h \
    bi/meta/meta.h \
    bi/models/address.h \
    bi/models/article.h \
    bi/models/county.h \
    bi/models/solditem.h \
    bi/repositories/sqlexcelrepository.h \
    bi/repositories/sqlrepository.h \
    buildnumber.h \
    views/dataform.h \
    views/datarowwidget.h \
    global.h \
    globals.h \
    helpers/filehelper.h \
    helpers/filenamehelper.h \
    helpers/logger.h \
    helpers/networkhelper.h \
    helpers/processhelper.h \
    helpers/signalhelper.h \
    helpers/sqlhelper.h \
    helpers/stringhelper.h \
    helpers/stringify.h \
    helpers/translator.h \
    interfaces/imainview.h \
    interfaces/ilogview.h \
    presenters/mainpresenter.h \
    views/mainviewmodel.h \
    views/mainwindow.h \
    bi/operations.h \
    presenters/presenter.h \
    #repositories/solditemrepository.h \
    presenters/logpresenter.h \
    settings.h
    #model.h \
     #updates.h

FORMS += \
    views/dataform.ui \
    views/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    testdata/BillingoZolinak.csv \
    testdata/Billingo_2024-07-03_CSV.csv \
    testdata/Cikktorzs_Zolinak.csv \
    testdata/Cimtorzs_Zolinak.csv \
    testdata/Megyek_Zolinak.csv \
    testdata/Partnertorzs_Zolinak.csv \
    testdata/teszt1.csv \
    testdata/teszt2.csv

