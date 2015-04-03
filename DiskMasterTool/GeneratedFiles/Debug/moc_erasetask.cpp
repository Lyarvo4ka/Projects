/****************************************************************************
** Meta object code from reading C++ file 'erasetask.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../erasetask.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'erasetask.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_QuickEraseTask_t {
    QByteArrayData data[1];
    char stringdata[15];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QuickEraseTask_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QuickEraseTask_t qt_meta_stringdata_QuickEraseTask = {
    {
QT_MOC_LITERAL(0, 0, 14)
    },
    "QuickEraseTask"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QuickEraseTask[] = {

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

void QuickEraseTask::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject QuickEraseTask::staticMetaObject = {
    { &QuickVerifyTask::staticMetaObject, qt_meta_stringdata_QuickEraseTask.data,
      qt_meta_data_QuickEraseTask,  qt_static_metacall, 0, 0}
};


const QMetaObject *QuickEraseTask::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QuickEraseTask::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QuickEraseTask.stringdata))
        return static_cast<void*>(const_cast< QuickEraseTask*>(this));
    return QuickVerifyTask::qt_metacast(_clname);
}

int QuickEraseTask::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QuickVerifyTask::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
struct qt_meta_stringdata_EraseTabWidget_t {
    QByteArrayData data[17];
    char stringdata[202];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_EraseTabWidget_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_EraseTabWidget_t qt_meta_stringdata_EraseTabWidget = {
    {
QT_MOC_LITERAL(0, 0, 14),
QT_MOC_LITERAL(1, 15, 14),
QT_MOC_LITERAL(2, 30, 0),
QT_MOC_LITERAL(3, 31, 6),
QT_MOC_LITERAL(4, 38, 17),
QT_MOC_LITERAL(5, 56, 15),
QT_MOC_LITERAL(6, 72, 4),
QT_MOC_LITERAL(7, 77, 11),
QT_MOC_LITERAL(8, 89, 14),
QT_MOC_LITERAL(9, 104, 13),
QT_MOC_LITERAL(10, 118, 10),
QT_MOC_LITERAL(11, 129, 15),
QT_MOC_LITERAL(12, 145, 12),
QT_MOC_LITERAL(13, 158, 15),
QT_MOC_LITERAL(14, 174, 10),
QT_MOC_LITERAL(15, 185, 9),
QT_MOC_LITERAL(16, 195, 6)
    },
    "EraseTabWidget\0device_changed\0\0nIndex\0"
    "StartDetectDevice\0const DM::PORT*\0"
    "port\0current_lba\0current_sector\0"
    "task_finished\0lastSector\0thread_finished\0"
    "task_breaked\0detect_finished\0task_error\0"
    "BadSector\0sector"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_EraseTabWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   64,    2, 0x0a /* Public */,
       4,    1,   67,    2, 0x0a /* Public */,
       4,    0,   70,    2, 0x0a /* Public */,
       7,    1,   71,    2, 0x0a /* Public */,
       9,    1,   74,    2, 0x0a /* Public */,
      11,    0,   77,    2, 0x0a /* Public */,
      12,    1,   78,    2, 0x0a /* Public */,
      13,    0,   81,    2, 0x0a /* Public */,
      14,    1,   82,    2, 0x0a /* Public */,
      15,    1,   85,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void,
    QMetaType::Void, QMetaType::LongLong,    8,
    QMetaType::Void, QMetaType::LongLong,   10,
    QMetaType::Void,
    QMetaType::Void, QMetaType::LongLong,   10,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::LongLong,   16,

       0        // eod
};

void EraseTabWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        EraseTabWidget *_t = static_cast<EraseTabWidget *>(_o);
        switch (_id) {
        case 0: _t->device_changed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->StartDetectDevice((*reinterpret_cast< const DM::PORT*(*)>(_a[1]))); break;
        case 2: _t->StartDetectDevice(); break;
        case 3: _t->current_lba((*reinterpret_cast< const qlonglong(*)>(_a[1]))); break;
        case 4: _t->task_finished((*reinterpret_cast< const qlonglong(*)>(_a[1]))); break;
        case 5: _t->thread_finished(); break;
        case 6: _t->task_breaked((*reinterpret_cast< const qlonglong(*)>(_a[1]))); break;
        case 7: _t->detect_finished(); break;
        case 8: _t->task_error((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->BadSector((*reinterpret_cast< const qlonglong(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject EraseTabWidget::staticMetaObject = {
    { &BaseTabWidget::staticMetaObject, qt_meta_stringdata_EraseTabWidget.data,
      qt_meta_data_EraseTabWidget,  qt_static_metacall, 0, 0}
};


const QMetaObject *EraseTabWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *EraseTabWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_EraseTabWidget.stringdata))
        return static_cast<void*>(const_cast< EraseTabWidget*>(this));
    return BaseTabWidget::qt_metacast(_clname);
}

int EraseTabWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BaseTabWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
