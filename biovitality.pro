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
    meta/csvhelper.cpp \
    meta/sqlmetahelper.cpp \
    mvp/models/address.cpp \
    mvp/models/article.cpp \
    mvp/models/country.cpp \
    mvp/models/county.cpp \
    mvp/models/invoicehead.cpp \
    mvp/models/invoiceitem.cpp \
    mvp/models/invoiceitems.cpp \
    mvp/models/partner.cpp \
    mvp/models/solditem.cpp \
    repositories/sqlexcelrepository.cpp \
    repositories/sqlrepository.cpp \
    infrastructure/buildnumber.cpp \
    mvp/views/dataform.cpp \
    mvp/views/datarowwidget.cpp \
    infrastructure/globals.cpp \
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
    mvp/presenters/mainpresenter.cpp \
    mvp/views/mainwindow.cpp \
    bi/operations.cpp \
    mvp/presenters/presenter.cpp \
    #repositories/solditemrepository.cpp \
    mvp/presenters/logpresenter.cpp \
    infrastructure/settings.cpp
    #model.cpp \
    #updates.cpp

HEADERS += \
    #actions.h \
    helpers/nameof.h \
    mvp/models/country.h \
    mvp/models/invoicehead.h \
    mvp/models/invoiceitem.h \
    mvp/models/invoiceitems.h \
    mvp/models/modelinterfaces.h \
    mvp/models/partner.h \
    mvp/viewinterfaces/iview.h \
    patterns/singleton.h \
    meta/csvhelper.h \
    meta/sqlmetahelper.h \
    meta/meta.h \
    mvp/models/address.h \
    mvp/models/article.h \
    mvp/models/county.h \
    mvp/models/solditem.h \
    repositories/sqlexcelrepository.h \
    repositories/sqlrepository.h \
    infrastructure/buildnumber.h \
    mvp/views/dataform.h \
    mvp/views/datarowwidget.h \
    infrastructure/global.h \
    infrastructure/globals.h \
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
    mvp/viewinterfaces/imainview.h \
    mvp/viewinterfaces/ilogview.h \
    mvp/presenters/mainpresenter.h \
    mvp/viewmodels/mainviewmodel.h \
    mvp/views/mainwindow.h \
    bi/operations.h \
    mvp/presenters/presenter.h \
    #repositories/solditemrepository.h \
    mvp/presenters/logpresenter.h \
    infrastructure/settings.h
    #model.h \
    #updates.h

FORMS += \
    mvp/views/dataform.ui \
    mvp/views/mainwindow.ui

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
    testdata/countries.csv \
    testdata/teszt1.csv \
    testdata/teszt2.csv \
    testdata/todo.txt

