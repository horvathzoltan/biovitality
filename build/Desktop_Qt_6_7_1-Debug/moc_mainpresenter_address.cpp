/****************************************************************************
** Meta object code from reading C++ file 'mainpresenter_address.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../mvp/presenters/mainpresenter_address.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainpresenter_address.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSMainPresenter_AddressENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSMainPresenter_AddressENDCLASS = QtMocHelpers::stringData(
    "MainPresenter_Address",
    "process_CreateAddress_Action",
    "",
    "IMainView*",
    "sender",
    "process_UpdateAddress_Action",
    "process_ListAddress_Action",
    "process_AcceptAddress_Action",
    "opId",
    "process_DoneAddress_Action",
    "r",
    "process_ImportAddress_Action"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSMainPresenter_AddressENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   50,    2, 0x08,    1 /* Private */,
       5,    1,   53,    2, 0x08,    3 /* Private */,
       6,    1,   56,    2, 0x08,    5 /* Private */,
       7,    1,   59,    2, 0x08,    7 /* Private */,
       9,    2,   62,    2, 0x08,    9 /* Private */,
      11,    1,   67,    2, 0x08,   12 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::QUuid,    8,
    QMetaType::Void, QMetaType::QUuid, QMetaType::Int,    8,   10,
    QMetaType::Void, 0x80000000 | 3,    4,

       0        // eod
};

Q_CONSTINIT const QMetaObject MainPresenter_Address::staticMetaObject = { {
    QMetaObject::SuperData::link<Presenter::staticMetaObject>(),
    qt_meta_stringdata_CLASSMainPresenter_AddressENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSMainPresenter_AddressENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSMainPresenter_AddressENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<MainPresenter_Address, std::true_type>,
        // method 'process_CreateAddress_Action'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<IMainView *, std::false_type>,
        // method 'process_UpdateAddress_Action'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<IMainView *, std::false_type>,
        // method 'process_ListAddress_Action'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<IMainView *, std::false_type>,
        // method 'process_AcceptAddress_Action'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QUuid, std::false_type>,
        // method 'process_DoneAddress_Action'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QUuid, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'process_ImportAddress_Action'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<IMainView *, std::false_type>
    >,
    nullptr
} };

void MainPresenter_Address::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainPresenter_Address *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->process_CreateAddress_Action((*reinterpret_cast< std::add_pointer_t<IMainView*>>(_a[1]))); break;
        case 1: _t->process_UpdateAddress_Action((*reinterpret_cast< std::add_pointer_t<IMainView*>>(_a[1]))); break;
        case 2: _t->process_ListAddress_Action((*reinterpret_cast< std::add_pointer_t<IMainView*>>(_a[1]))); break;
        case 3: _t->process_AcceptAddress_Action((*reinterpret_cast< std::add_pointer_t<QUuid>>(_a[1]))); break;
        case 4: _t->process_DoneAddress_Action((*reinterpret_cast< std::add_pointer_t<QUuid>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 5: _t->process_ImportAddress_Action((*reinterpret_cast< std::add_pointer_t<IMainView*>>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject *MainPresenter_Address::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainPresenter_Address::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSMainPresenter_AddressENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return Presenter::qt_metacast(_clname);
}

int MainPresenter_Address::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Presenter::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 6;
    }
    return _id;
}
QT_WARNING_POP
