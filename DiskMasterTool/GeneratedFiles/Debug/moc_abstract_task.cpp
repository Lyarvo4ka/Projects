/****************************************************************************
** Meta object code from reading C++ file 'abstract_task.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../abstract_task.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'abstract_task.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_AbstractTask_t {
    QByteArrayData data[13];
    char stringdata[149];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_AbstractTask_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_AbstractTask_t qt_meta_stringdata_AbstractTask = {
    {
QT_MOC_LITERAL(0, 0, 12),
QT_MOC_LITERAL(1, 13, 10),
QT_MOC_LITERAL(2, 24, 0),
QT_MOC_LITERAL(3, 25, 15),
QT_MOC_LITERAL(4, 41, 12),
QT_MOC_LITERAL(5, 54, 12),
QT_MOC_LITERAL(6, 67, 10),
QT_MOC_LITERAL(7, 78, 10),
QT_MOC_LITERAL(8, 89, 11),
QT_MOC_LITERAL(9, 101, 10),
QT_MOC_LITERAL(10, 112, 13),
QT_MOC_LITERAL(11, 126, 10),
QT_MOC_LITERAL(12, 137, 10)
    },
    "AbstractTask\0new_device\0\0const DM::PORT*\0"
    "disk_removed\0not_detected\0error_code\0"
    "update_lba\0finish_task\0break_task\0"
    "finish_detect\0error_task\0bad_sector\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AbstractTask[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       9,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   59,    2, 0x06,
       4,    1,   62,    2, 0x06,
       5,    2,   65,    2, 0x06,
       7,    1,   70,    2, 0x06,
       8,    1,   73,    2, 0x06,
       9,    1,   76,    2, 0x06,
      10,    0,   79,    2, 0x06,
      11,    1,   80,    2, 0x06,
      12,    1,   83,    2, 0x06,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int,    2,    6,
    QMetaType::Void, QMetaType::LongLong,    2,
    QMetaType::Void, QMetaType::LongLong,    2,
    QMetaType::Void, QMetaType::LongLong,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::LongLong,    2,

       0        // eod
};

void AbstractTask::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        AbstractTask *_t = static_cast<AbstractTask *>(_o);
        switch (_id) {
        case 0: _t->new_device((*reinterpret_cast< const DM::PORT*(*)>(_a[1]))); break;
        case 1: _t->disk_removed((*reinterpret_cast< const DM::PORT*(*)>(_a[1]))); break;
        case 2: _t->not_detected((*reinterpret_cast< const DM::PORT*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->update_lba((*reinterpret_cast< const qlonglong(*)>(_a[1]))); break;
        case 4: _t->finish_task((*reinterpret_cast< const qlonglong(*)>(_a[1]))); break;
        case 5: _t->break_task((*reinterpret_cast< const qlonglong(*)>(_a[1]))); break;
        case 6: _t->finish_detect(); break;
        case 7: _t->error_task((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->bad_sector((*reinterpret_cast< const qlonglong(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (AbstractTask::*_t)(const DM::PORT * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AbstractTask::new_device)) {
                *result = 0;
            }
        }
        {
            typedef void (AbstractTask::*_t)(const DM::PORT * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AbstractTask::disk_removed)) {
                *result = 1;
            }
        }
        {
            typedef void (AbstractTask::*_t)(const DM::PORT * , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AbstractTask::not_detected)) {
                *result = 2;
            }
        }
        {
            typedef void (AbstractTask::*_t)(const qlonglong );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AbstractTask::update_lba)) {
                *result = 3;
            }
        }
        {
            typedef void (AbstractTask::*_t)(const qlonglong );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AbstractTask::finish_task)) {
                *result = 4;
            }
        }
        {
            typedef void (AbstractTask::*_t)(const qlonglong );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AbstractTask::break_task)) {
                *result = 5;
            }
        }
        {
            typedef void (AbstractTask::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AbstractTask::finish_detect)) {
                *result = 6;
            }
        }
        {
            typedef void (AbstractTask::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AbstractTask::error_task)) {
                *result = 7;
            }
        }
        {
            typedef void (AbstractTask::*_t)(const qlonglong );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AbstractTask::bad_sector)) {
                *result = 8;
            }
        }
    }
}

const QMetaObject AbstractTask::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_AbstractTask.data,
      qt_meta_data_AbstractTask,  qt_static_metacall, 0, 0}
};


const QMetaObject *AbstractTask::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AbstractTask::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_AbstractTask.stringdata))
        return static_cast<void*>(const_cast< AbstractTask*>(this));
    return QThread::qt_metacast(_clname);
}

int AbstractTask::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
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
void AbstractTask::new_device(const DM::PORT * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void AbstractTask::disk_removed(const DM::PORT * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void AbstractTask::not_detected(const DM::PORT * _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void AbstractTask::update_lba(const qlonglong _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void AbstractTask::finish_task(const qlonglong _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void AbstractTask::break_task(const qlonglong _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void AbstractTask::finish_detect()
{
    QMetaObject::activate(this, &staticMetaObject, 6, 0);
}

// SIGNAL 7
void AbstractTask::error_task(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void AbstractTask::bad_sector(const qlonglong _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}
QT_END_MOC_NAMESPACE
