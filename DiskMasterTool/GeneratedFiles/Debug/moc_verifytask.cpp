/****************************************************************************
** Meta object code from reading C++ file 'verifytask.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../verifytask.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'verifytask.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QuickVerifyTask_t {
    QByteArrayData data[1];
    char stringdata0[16];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QuickVerifyTask_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QuickVerifyTask_t qt_meta_stringdata_QuickVerifyTask = {
    {
QT_MOC_LITERAL(0, 0, 15) // "QuickVerifyTask"

    },
    "QuickVerifyTask"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QuickVerifyTask[] = {

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

void QuickVerifyTask::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject QuickVerifyTask::staticMetaObject = {
    { &AbstractTask::staticMetaObject, qt_meta_stringdata_QuickVerifyTask.data,
      qt_meta_data_QuickVerifyTask,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *QuickVerifyTask::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QuickVerifyTask::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_QuickVerifyTask.stringdata0))
        return static_cast<void*>(const_cast< QuickVerifyTask*>(this));
    if (!strcmp(_clname, "AbstractTaskObserver"))
        return static_cast< AbstractTaskObserver*>(const_cast< QuickVerifyTask*>(this));
    return AbstractTask::qt_metacast(_clname);
}

int QuickVerifyTask::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AbstractTask::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
struct qt_meta_stringdata_VerifyTabWidget_t {
    QByteArrayData data[17];
    char stringdata0[203];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VerifyTabWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VerifyTabWidget_t qt_meta_stringdata_VerifyTabWidget = {
    {
QT_MOC_LITERAL(0, 0, 15), // "VerifyTabWidget"
QT_MOC_LITERAL(1, 16, 14), // "device_changed"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 6), // "nIndex"
QT_MOC_LITERAL(4, 39, 17), // "StartDetectDevice"
QT_MOC_LITERAL(5, 57, 15), // "const DM::PORT*"
QT_MOC_LITERAL(6, 73, 4), // "port"
QT_MOC_LITERAL(7, 78, 11), // "current_lba"
QT_MOC_LITERAL(8, 90, 14), // "current_sector"
QT_MOC_LITERAL(9, 105, 13), // "task_finished"
QT_MOC_LITERAL(10, 119, 10), // "lastSector"
QT_MOC_LITERAL(11, 130, 15), // "thread_finished"
QT_MOC_LITERAL(12, 146, 12), // "task_breaked"
QT_MOC_LITERAL(13, 159, 15), // "detect_finished"
QT_MOC_LITERAL(14, 175, 10), // "task_error"
QT_MOC_LITERAL(15, 186, 9), // "BadSector"
QT_MOC_LITERAL(16, 196, 6) // "sector"

    },
    "VerifyTabWidget\0device_changed\0\0nIndex\0"
    "StartDetectDevice\0const DM::PORT*\0"
    "port\0current_lba\0current_sector\0"
    "task_finished\0lastSector\0thread_finished\0"
    "task_breaked\0detect_finished\0task_error\0"
    "BadSector\0sector"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VerifyTabWidget[] = {

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

void VerifyTabWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        VerifyTabWidget *_t = static_cast<VerifyTabWidget *>(_o);
        Q_UNUSED(_t)
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

const QMetaObject VerifyTabWidget::staticMetaObject = {
    { &BaseTabWidget::staticMetaObject, qt_meta_stringdata_VerifyTabWidget.data,
      qt_meta_data_VerifyTabWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *VerifyTabWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VerifyTabWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_VerifyTabWidget.stringdata0))
        return static_cast<void*>(const_cast< VerifyTabWidget*>(this));
    return BaseTabWidget::qt_metacast(_clname);
}

int VerifyTabWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
