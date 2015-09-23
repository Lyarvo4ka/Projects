/****************************************************************************
** Meta object code from reading C++ file 'optionsmanager.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../optionsmanager.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'optionsmanager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_DevicePresenter_t {
    QByteArrayData data[7];
    char stringdata0[81];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DevicePresenter_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DevicePresenter_t qt_meta_stringdata_DevicePresenter = {
    {
QT_MOC_LITERAL(0, 0, 15), // "DevicePresenter"
QT_MOC_LITERAL(1, 16, 13), // "Chirp_changed"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 6), // "iChirp"
QT_MOC_LITERAL(4, 38, 15), // "EndBeep_changed"
QT_MOC_LITERAL(5, 54, 10), // "iBeepValue"
QT_MOC_LITERAL(6, 65, 15) // "CRCBeep_changed"

    },
    "DevicePresenter\0Chirp_changed\0\0iChirp\0"
    "EndBeep_changed\0iBeepValue\0CRCBeep_changed"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DevicePresenter[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x08 /* Private */,
       4,    1,   32,    2, 0x08 /* Private */,
       6,    1,   35,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int,    5,

       0        // eod
};

void DevicePresenter::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        DevicePresenter *_t = static_cast<DevicePresenter *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->Chirp_changed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->EndBeep_changed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->CRCBeep_changed((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject DevicePresenter::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_DevicePresenter.data,
      qt_meta_data_DevicePresenter,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *DevicePresenter::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DevicePresenter::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_DevicePresenter.stringdata0))
        return static_cast<void*>(const_cast< DevicePresenter*>(this));
    return QObject::qt_metacast(_clname);
}

int DevicePresenter::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
