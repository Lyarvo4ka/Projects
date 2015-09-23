/****************************************************************************
** Meta object code from reading C++ file 'copytask.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../copytask.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'copytask.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_QuickCopyTask_t {
    QByteArrayData data[1];
    char stringdata0[14];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QuickCopyTask_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QuickCopyTask_t qt_meta_stringdata_QuickCopyTask = {
    {
QT_MOC_LITERAL(0, 0, 13) // "QuickCopyTask"

    },
    "QuickCopyTask"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QuickCopyTask[] = {

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

void QuickCopyTask::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject QuickCopyTask::staticMetaObject = {
    { &AbstractTask::staticMetaObject, qt_meta_stringdata_QuickCopyTask.data,
      qt_meta_data_QuickCopyTask,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *QuickCopyTask::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QuickCopyTask::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_QuickCopyTask.stringdata0))
        return static_cast<void*>(const_cast< QuickCopyTask*>(this));
    if (!strcmp(_clname, "AbstractTaskObserver"))
        return static_cast< AbstractTaskObserver*>(const_cast< QuickCopyTask*>(this));
    return AbstractTask::qt_metacast(_clname);
}

int QuickCopyTask::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AbstractTask::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
struct qt_meta_stringdata_SmartCopyTask_t {
    QByteArrayData data[1];
    char stringdata0[14];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SmartCopyTask_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SmartCopyTask_t qt_meta_stringdata_SmartCopyTask = {
    {
QT_MOC_LITERAL(0, 0, 13) // "SmartCopyTask"

    },
    "SmartCopyTask"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SmartCopyTask[] = {

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

void SmartCopyTask::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject SmartCopyTask::staticMetaObject = {
    { &QuickCopyTask::staticMetaObject, qt_meta_stringdata_SmartCopyTask.data,
      qt_meta_data_SmartCopyTask,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *SmartCopyTask::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SmartCopyTask::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_SmartCopyTask.stringdata0))
        return static_cast<void*>(const_cast< SmartCopyTask*>(this));
    return QuickCopyTask::qt_metacast(_clname);
}

int SmartCopyTask::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QuickCopyTask::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
struct qt_meta_stringdata_CopyTabWidget_t {
    QByteArrayData data[22];
    char stringdata0[288];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CopyTabWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CopyTabWidget_t qt_meta_stringdata_CopyTabWidget = {
    {
QT_MOC_LITERAL(0, 0, 13), // "CopyTabWidget"
QT_MOC_LITERAL(1, 14, 14), // "source_changed"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 14), // "target_changed"
QT_MOC_LITERAL(4, 45, 13), // "pause_clicked"
QT_MOC_LITERAL(5, 59, 17), // "StartDetectDevice"
QT_MOC_LITERAL(6, 77, 18), // "StartDetectDevices"
QT_MOC_LITERAL(7, 96, 15), // "const DM::PORT*"
QT_MOC_LITERAL(8, 112, 11), // "source_port"
QT_MOC_LITERAL(9, 124, 11), // "target_port"
QT_MOC_LITERAL(10, 136, 15), // "cancelDetection"
QT_MOC_LITERAL(11, 152, 6), // "result"
QT_MOC_LITERAL(12, 159, 17), // "DeviceNotDetected"
QT_MOC_LITERAL(13, 177, 11), // "current_lba"
QT_MOC_LITERAL(14, 189, 13), // "task_finished"
QT_MOC_LITERAL(15, 203, 15), // "thread_finished"
QT_MOC_LITERAL(16, 219, 12), // "task_breaked"
QT_MOC_LITERAL(17, 232, 15), // "detect_finished"
QT_MOC_LITERAL(18, 248, 10), // "task_error"
QT_MOC_LITERAL(19, 259, 9), // "BadSector"
QT_MOC_LITERAL(20, 269, 6), // "sector"
QT_MOC_LITERAL(21, 276, 11) // "onTimeTimer"

    },
    "CopyTabWidget\0source_changed\0\0"
    "target_changed\0pause_clicked\0"
    "StartDetectDevice\0StartDetectDevices\0"
    "const DM::PORT*\0source_port\0target_port\0"
    "cancelDetection\0result\0DeviceNotDetected\0"
    "current_lba\0task_finished\0thread_finished\0"
    "task_breaked\0detect_finished\0task_error\0"
    "BadSector\0sector\0onTimeTimer"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CopyTabWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   89,    2, 0x0a /* Public */,
       3,    1,   92,    2, 0x0a /* Public */,
       4,    0,   95,    2, 0x0a /* Public */,
       5,    0,   96,    2, 0x0a /* Public */,
       6,    2,   97,    2, 0x0a /* Public */,
      10,    1,  102,    2, 0x0a /* Public */,
      12,    2,  105,    2, 0x0a /* Public */,
      13,    1,  110,    2, 0x0a /* Public */,
      14,    1,  113,    2, 0x0a /* Public */,
      15,    0,  116,    2, 0x0a /* Public */,
      16,    1,  117,    2, 0x0a /* Public */,
      17,    0,  120,    2, 0x0a /* Public */,
      18,    1,  121,    2, 0x0a /* Public */,
      19,    1,  124,    2, 0x0a /* Public */,
      21,    0,  127,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 7, 0x80000000 | 7,    8,    9,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void, 0x80000000 | 7, QMetaType::Int,    2,    2,
    QMetaType::Void, QMetaType::LongLong,    2,
    QMetaType::Void, QMetaType::LongLong,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::LongLong,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::LongLong,   20,
    QMetaType::Void,

       0        // eod
};

void CopyTabWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CopyTabWidget *_t = static_cast<CopyTabWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->source_changed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->target_changed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->pause_clicked(); break;
        case 3: _t->StartDetectDevice(); break;
        case 4: _t->StartDetectDevices((*reinterpret_cast< const DM::PORT*(*)>(_a[1])),(*reinterpret_cast< const DM::PORT*(*)>(_a[2]))); break;
        case 5: _t->cancelDetection((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->DeviceNotDetected((*reinterpret_cast< const DM::PORT*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 7: _t->current_lba((*reinterpret_cast< const qlonglong(*)>(_a[1]))); break;
        case 8: _t->task_finished((*reinterpret_cast< const qlonglong(*)>(_a[1]))); break;
        case 9: _t->thread_finished(); break;
        case 10: _t->task_breaked((*reinterpret_cast< const qlonglong(*)>(_a[1]))); break;
        case 11: _t->detect_finished(); break;
        case 12: _t->task_error((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: _t->BadSector((*reinterpret_cast< const qlonglong(*)>(_a[1]))); break;
        case 14: _t->onTimeTimer(); break;
        default: ;
        }
    }
}

const QMetaObject CopyTabWidget::staticMetaObject = {
    { &BaseTabWidget::staticMetaObject, qt_meta_stringdata_CopyTabWidget.data,
      qt_meta_data_CopyTabWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CopyTabWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CopyTabWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CopyTabWidget.stringdata0))
        return static_cast<void*>(const_cast< CopyTabWidget*>(this));
    return BaseTabWidget::qt_metacast(_clname);
}

int CopyTabWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BaseTabWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 15;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
