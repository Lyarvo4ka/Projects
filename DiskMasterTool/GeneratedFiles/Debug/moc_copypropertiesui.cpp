/****************************************************************************
** Meta object code from reading C++ file 'copypropertiesui.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../copypropertiesui.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'copypropertiesui.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_CopyPropertiesUi_t {
    QByteArrayData data[8];
    char stringdata[106];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CopyPropertiesUi_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CopyPropertiesUi_t qt_meta_stringdata_CopyPropertiesUi = {
    {
QT_MOC_LITERAL(0, 0, 16),
QT_MOC_LITERAL(1, 17, 15),
QT_MOC_LITERAL(2, 33, 0),
QT_MOC_LITERAL(3, 34, 10),
QT_MOC_LITERAL(4, 45, 16),
QT_MOC_LITERAL(5, 62, 13),
QT_MOC_LITERAL(6, 76, 17),
QT_MOC_LITERAL(7, 94, 11)
    },
    "CopyPropertiesUi\0JumpSizeChanged\0\0"
    "size_value\0DirectionChanged\0new_direction\0"
    "ReadUnReadChanged\0check_value"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CopyPropertiesUi[] = {

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
       1,    1,   29,    2, 0x09 /* Protected */,
       4,    1,   32,    2, 0x09 /* Protected */,
       6,    1,   35,    2, 0x09 /* Protected */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int,    7,

       0        // eod
};

void CopyPropertiesUi::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CopyPropertiesUi *_t = static_cast<CopyPropertiesUi *>(_o);
        switch (_id) {
        case 0: _t->JumpSizeChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->DirectionChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->ReadUnReadChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject CopyPropertiesUi::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_CopyPropertiesUi.data,
      qt_meta_data_CopyPropertiesUi,  qt_static_metacall, 0, 0}
};


const QMetaObject *CopyPropertiesUi::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CopyPropertiesUi::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CopyPropertiesUi.stringdata))
        return static_cast<void*>(const_cast< CopyPropertiesUi*>(this));
    return QWidget::qt_metacast(_clname);
}

int CopyPropertiesUi::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
