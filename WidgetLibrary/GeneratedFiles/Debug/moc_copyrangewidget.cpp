/****************************************************************************
** Meta object code from reading C++ file 'copyrangewidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../include/WidgetLibrary/copyrangewidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'copyrangewidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_CopyRangeData_t {
    QByteArrayData data[11];
    char stringdata[162];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_CopyRangeData_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_CopyRangeData_t qt_meta_stringdata_CopyRangeData = {
    {
QT_MOC_LITERAL(0, 0, 13),
QT_MOC_LITERAL(1, 14, 19),
QT_MOC_LITERAL(2, 34, 0),
QT_MOC_LITERAL(3, 35, 19),
QT_MOC_LITERAL(4, 55, 18),
QT_MOC_LITERAL(5, 74, 15),
QT_MOC_LITERAL(6, 90, 12),
QT_MOC_LITERAL(7, 103, 15),
QT_MOC_LITERAL(8, 119, 13),
QT_MOC_LITERAL(9, 133, 14),
QT_MOC_LITERAL(10, 148, 12)
    },
    "CopyRangeData\0sourceOffsetChanged\0\0"
    "targetOffsetChanged\0sectorCountChanged\0"
    "setSourceOffset\0souce_offset\0"
    "setTargetOffset\0target_offset\0"
    "setSectorCount\0sector_count\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CopyRangeData[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   59,    2, 0x06,
       3,    1,   62,    2, 0x06,
       4,    1,   65,    2, 0x06,

 // slots: name, argc, parameters, tag, flags
       5,    1,   68,    2, 0x0a,
       7,    1,   71,    2, 0x0a,
       9,    1,   74,    2, 0x0a,
       5,    1,   77,    2, 0x0a,
       7,    1,   80,    2, 0x0a,
       9,    1,   83,    2, 0x0a,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::LongLong,    6,
    QMetaType::Void, QMetaType::LongLong,    8,
    QMetaType::Void, QMetaType::LongLong,   10,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void, QMetaType::QString,   10,

       0        // eod
};

void CopyRangeData::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CopyRangeData *_t = static_cast<CopyRangeData *>(_o);
        switch (_id) {
        case 0: _t->sourceOffsetChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->targetOffsetChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->sectorCountChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->setSourceOffset((*reinterpret_cast< qlonglong(*)>(_a[1]))); break;
        case 4: _t->setTargetOffset((*reinterpret_cast< qlonglong(*)>(_a[1]))); break;
        case 5: _t->setSectorCount((*reinterpret_cast< qlonglong(*)>(_a[1]))); break;
        case 6: _t->setSourceOffset((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: _t->setTargetOffset((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 8: _t->setSectorCount((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (CopyRangeData::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CopyRangeData::sourceOffsetChanged)) {
                *result = 0;
            }
        }
        {
            typedef void (CopyRangeData::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CopyRangeData::targetOffsetChanged)) {
                *result = 1;
            }
        }
        {
            typedef void (CopyRangeData::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CopyRangeData::sectorCountChanged)) {
                *result = 2;
            }
        }
    }
}

const QMetaObject CopyRangeData::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_CopyRangeData.data,
      qt_meta_data_CopyRangeData,  qt_static_metacall, 0, 0}
};


const QMetaObject *CopyRangeData::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CopyRangeData::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CopyRangeData.stringdata))
        return static_cast<void*>(const_cast< CopyRangeData*>(this));
    return QObject::qt_metacast(_clname);
}

int CopyRangeData::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void CopyRangeData::sourceOffsetChanged(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CopyRangeData::targetOffsetChanged(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void CopyRangeData::sectorCountChanged(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
struct qt_meta_stringdata_QLongLongValidator_t {
    QByteArrayData data[3];
    char stringdata[31];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_QLongLongValidator_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_QLongLongValidator_t qt_meta_stringdata_QLongLongValidator = {
    {
QT_MOC_LITERAL(0, 0, 18),
QT_MOC_LITERAL(1, 19, 6),
QT_MOC_LITERAL(2, 26, 3)
    },
    "QLongLongValidator\0bottom\0top\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QLongLongValidator[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       2,   14, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // properties: name, type, flags
       1, QMetaType::LongLong, 0x00095103,
       2, QMetaType::LongLong, 0x00095103,

       0        // eod
};

void QLongLongValidator::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject QLongLongValidator::staticMetaObject = {
    { &QValidator::staticMetaObject, qt_meta_stringdata_QLongLongValidator.data,
      qt_meta_data_QLongLongValidator,  qt_static_metacall, 0, 0}
};


const QMetaObject *QLongLongValidator::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QLongLongValidator::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QLongLongValidator.stringdata))
        return static_cast<void*>(const_cast< QLongLongValidator*>(this));
    return QValidator::qt_metacast(_clname);
}

int QLongLongValidator::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QValidator::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    
#ifndef QT_NO_PROPERTIES
     if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< qlonglong*>(_v) = bottom(); break;
        case 1: *reinterpret_cast< qlonglong*>(_v) = top(); break;
        }
        _id -= 2;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setBottom(*reinterpret_cast< qlonglong*>(_v)); break;
        case 1: setTop(*reinterpret_cast< qlonglong*>(_v)); break;
        }
        _id -= 2;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 2;
    } else if (_c == QMetaObject::RegisterPropertyMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}
struct qt_meta_stringdata_CopyRangeWidget_t {
    QByteArrayData data[1];
    char stringdata[17];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_CopyRangeWidget_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_CopyRangeWidget_t qt_meta_stringdata_CopyRangeWidget = {
    {
QT_MOC_LITERAL(0, 0, 15)
    },
    "CopyRangeWidget\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CopyRangeWidget[] = {

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

void CopyRangeWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject CopyRangeWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_CopyRangeWidget.data,
      qt_meta_data_CopyRangeWidget,  qt_static_metacall, 0, 0}
};


const QMetaObject *CopyRangeWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CopyRangeWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CopyRangeWidget.stringdata))
        return static_cast<void*>(const_cast< CopyRangeWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int CopyRangeWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
