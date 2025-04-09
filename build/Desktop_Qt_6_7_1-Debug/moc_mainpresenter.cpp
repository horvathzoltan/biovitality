/****************************************************************************
** Meta object code from reading C++ file 'mainpresenter.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../mvp/presenters/mainpresenter.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainpresenter.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSMainPresenterENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSMainPresenterENDCLASS = QtMocHelpers::stringData(
    "MainPresenter",
    "processPushButtonAction",
    "",
    "IMainView*",
    "sender",
    "processDBTestAction",
    "process_Add_SoldItemAction",
    "process_Add_SoldItem_AcceptAction",
    "opId",
    "process_DoneAction",
    "r",
    "process_TetelImport_Action",
    "process_PartnerImport_Action",
    "process_CountryImport_Action",
    "process_CountyImport_Action",
    "process_ArticleImport_Action",
    "process_PartnerList_Action"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSMainPresenterENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   80,    2, 0x08,    1 /* Private */,
       5,    1,   83,    2, 0x08,    3 /* Private */,
       6,    1,   86,    2, 0x08,    5 /* Private */,
       7,    1,   89,    2, 0x08,    7 /* Private */,
       9,    2,   92,    2, 0x08,    9 /* Private */,
      11,    1,   97,    2, 0x08,   12 /* Private */,
      12,    1,  100,    2, 0x08,   14 /* Private */,
      13,    1,  103,    2, 0x08,   16 /* Private */,
      14,    1,  106,    2, 0x08,   18 /* Private */,
      15,    1,  109,    2, 0x08,   20 /* Private */,
      16,    1,  112,    2, 0x08,   22 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::QUuid,    8,
    QMetaType::Void, QMetaType::QUuid, QMetaType::Int,    8,   10,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,

       0        // eod
};

Q_CONSTINIT const QMetaObject MainPresenter::staticMetaObject = { {
    QMetaObject::SuperData::link<Presenter::staticMetaObject>(),
    qt_meta_stringdata_CLASSMainPresenterENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSMainPresenterENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSMainPresenterENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<MainPresenter, std::true_type>,
        // method 'processPushButtonAction'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<IMainView *, std::false_type>,
        // method 'processDBTestAction'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<IMainView *, std::false_type>,
        // method 'process_Add_SoldItemAction'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<IMainView *, std::false_type>,
        // method 'process_Add_SoldItem_AcceptAction'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QUuid, std::false_type>,
        // method 'process_DoneAction'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QUuid, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'process_TetelImport_Action'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<IMainView *, std::false_type>,
        // method 'process_PartnerImport_Action'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<IMainView *, std::false_type>,
        // method 'process_CountryImport_Action'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<IMainView *, std::false_type>,
        // method 'process_CountyImport_Action'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<IMainView *, std::false_type>,
        // method 'process_ArticleImport_Action'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<IMainView *, std::false_type>,
        // method 'process_PartnerList_Action'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<IMainView *, std::false_type>
    >,
    nullptr
} };

void MainPresenter::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainPresenter *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->processPushButtonAction((*reinterpret_cast< std::add_pointer_t<IMainView*>>(_a[1]))); break;
        case 1: _t->processDBTestAction((*reinterpret_cast< std::add_pointer_t<IMainView*>>(_a[1]))); break;
        case 2: _t->process_Add_SoldItemAction((*reinterpret_cast< std::add_pointer_t<IMainView*>>(_a[1]))); break;
        case 3: _t->process_Add_SoldItem_AcceptAction((*reinterpret_cast< std::add_pointer_t<QUuid>>(_a[1]))); break;
        case 4: _t->process_DoneAction((*reinterpret_cast< std::add_pointer_t<QUuid>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 5: _t->process_TetelImport_Action((*reinterpret_cast< std::add_pointer_t<IMainView*>>(_a[1]))); break;
        case 6: _t->process_PartnerImport_Action((*reinterpret_cast< std::add_pointer_t<IMainView*>>(_a[1]))); break;
        case 7: _t->process_CountryImport_Action((*reinterpret_cast< std::add_pointer_t<IMainView*>>(_a[1]))); break;
        case 8: _t->process_CountyImport_Action((*reinterpret_cast< std::add_pointer_t<IMainView*>>(_a[1]))); break;
        case 9: _t->process_ArticleImport_Action((*reinterpret_cast< std::add_pointer_t<IMainView*>>(_a[1]))); break;
        case 10: _t->process_PartnerList_Action((*reinterpret_cast< std::add_pointer_t<IMainView*>>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject *MainPresenter::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainPresenter::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSMainPresenterENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return Presenter::qt_metacast(_clname);
}

int MainPresenter::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Presenter::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 11;
    }
    return _id;
}
QT_WARNING_POP
