/****************************************************************************
** Meta object code from reading C++ file 'sectormodel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../include/WidgetLibrary/sectormodel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sectormodel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_AbsractSectorModel_t {
    QByteArrayData data[4];
    char stringdata[50];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_AbsractSectorModel_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_AbsractSectorModel_t qt_meta_stringdata_AbsractSectorModel = {
    {
QT_MOC_LITERAL(0, 0, 18),
QT_MOC_LITERAL(1, 19, 13),
QT_MOC_LITERAL(2, 33, 0),
QT_MOC_LITERAL(3, 34, 14)
    },
    "AbsractSectorModel\0Block_Updated\0\0"
    "Sector_Updated\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AbsractSectorModel[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   24,    2, 0x06,
       3,    1,   27,    2, 0x06,

 // signals: parameters
    QMetaType::Void, QMetaType::LongLong,    2,
    QMetaType::Void, QMetaType::LongLong,    2,

       0        // eod
};

void AbsractSectorModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        AbsractSectorModel *_t = static_cast<AbsractSectorModel *>(_o);
        switch (_id) {
        case 0: _t->Block_Updated((*reinterpret_cast< qlonglong(*)>(_a[1]))); break;
        case 1: _t->Sector_Updated((*reinterpret_cast< qlonglong(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (AbsractSectorModel::*_t)(qlonglong );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AbsractSectorModel::Block_Updated)) {
                *result = 0;
            }
        }
        {
            typedef void (AbsractSectorModel::*_t)(qlonglong );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AbsractSectorModel::Sector_Updated)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject AbsractSectorModel::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_AbsractSectorModel.data,
      qt_meta_data_AbsractSectorModel,  qt_static_metacall, 0, 0}
};


const QMetaObject *AbsractSectorModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AbsractSectorModel::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_AbsractSectorModel.stringdata))
        return static_cast<void*>(const_cast< AbsractSectorModel*>(this));
    return QObject::qt_metacast(_clname);
}

int AbsractSectorModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void AbsractSectorModel::Block_Updated(qlonglong _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void AbsractSectorModel::Sector_Updated(qlonglong _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
struct qt_meta_stringdata_SectorModel_t {
    QByteArrayData data[1];
    char stringdata[13];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_SectorModel_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_SectorModel_t qt_meta_stringdata_SectorModel = {
    {
QT_MOC_LITERAL(0, 0, 11)
    },
    "SectorModel\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SectorModel[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void SectorModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject SectorModel::staticMetaObject = {
    { &AbsractSectorModel::staticMetaObject, qt_meta_stringdata_SectorModel.data,
      qt_meta_data_SectorModel,  qt_static_metacall, 0, 0}
};


const QMetaObject *SectorModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SectorModel::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SectorModel.stringdata))
        return static_cast<void*>(const_cast< SectorModel*>(this));
    return AbsractSectorModel::qt_metacast(_clname);
}

int SectorModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AbsractSectorModel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
