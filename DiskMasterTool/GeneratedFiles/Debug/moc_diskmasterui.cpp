/****************************************************************************
** Meta object code from reading C++ file 'diskmasterui.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../diskmasterui.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'diskmasterui.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_DiskMasterUI_t {
    QByteArrayData data[6];
    char stringdata0[73];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DiskMasterUI_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DiskMasterUI_t qt_meta_stringdata_DiskMasterUI = {
    {
QT_MOC_LITERAL(0, 0, 12), // "DiskMasterUI"
QT_MOC_LITERAL(1, 13, 14), // "ItemIsSelected"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 17), // "const DMItemIdex*"
QT_MOC_LITERAL(4, 47, 17), // "EnableTaskActions"
QT_MOC_LITERAL(5, 65, 7) // "bEnable"

    },
    "DiskMasterUI\0ItemIsSelected\0\0"
    "const DMItemIdex*\0EnableTaskActions\0"
    "bEnable"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DiskMasterUI[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   24,    2, 0x09 /* Protected */,
       4,    1,   27,    2, 0x09 /* Protected */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, QMetaType::Bool,    5,

       0        // eod
};

void DiskMasterUI::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        DiskMasterUI *_t = static_cast<DiskMasterUI *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->ItemIsSelected((*reinterpret_cast< const DMItemIdex*(*)>(_a[1]))); break;
        case 1: _t->EnableTaskActions((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject DiskMasterUI::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_DiskMasterUI.data,
      qt_meta_data_DiskMasterUI,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *DiskMasterUI::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DiskMasterUI::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_DiskMasterUI.stringdata0))
        return static_cast<void*>(const_cast< DiskMasterUI*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int DiskMasterUI::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
