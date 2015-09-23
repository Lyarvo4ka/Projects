/****************************************************************************
** Meta object code from reading C++ file 'tabwidgets.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../tabwidgets.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tabwidgets.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_BaseTabWidget_t {
    QByteArrayData data[19];
    char stringdata0[236];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_BaseTabWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_BaseTabWidget_t qt_meta_stringdata_BaseTabWidget = {
    {
QT_MOC_LITERAL(0, 0, 13), // "BaseTabWidget"
QT_MOC_LITERAL(1, 14, 15), // "progressUpdated"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 10), // "closedTask"
QT_MOC_LITERAL(4, 42, 8), // "removeMe"
QT_MOC_LITERAL(5, 51, 8), // "QWidget*"
QT_MOC_LITERAL(6, 60, 10), // "changeItem"
QT_MOC_LITERAL(7, 71, 5), // "DWORD"
QT_MOC_LITERAL(8, 77, 15), // "change_progress"
QT_MOC_LITERAL(9, 93, 13), // "start_clicked"
QT_MOC_LITERAL(10, 107, 14), // "cancel_clicked"
QT_MOC_LITERAL(11, 122, 12), // "exit_clicked"
QT_MOC_LITERAL(12, 135, 14), // "DeviceDetected"
QT_MOC_LITERAL(13, 150, 15), // "const DM::PORT*"
QT_MOC_LITERAL(14, 166, 4), // "port"
QT_MOC_LITERAL(15, 171, 18), // "DeviceDisconencted"
QT_MOC_LITERAL(16, 190, 14), // "FinishDetected"
QT_MOC_LITERAL(17, 205, 17), // "DeviceNotDetected"
QT_MOC_LITERAL(18, 223, 12) // "error_number"

    },
    "BaseTabWidget\0progressUpdated\0\0"
    "closedTask\0removeMe\0QWidget*\0changeItem\0"
    "DWORD\0change_progress\0start_clicked\0"
    "cancel_clicked\0exit_clicked\0DeviceDetected\0"
    "const DM::PORT*\0port\0DeviceDisconencted\0"
    "FinishDetected\0DeviceNotDetected\0"
    "error_number"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_BaseTabWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   79,    2, 0x06 /* Public */,
       3,    0,   80,    2, 0x06 /* Public */,
       4,    1,   81,    2, 0x06 /* Public */,
       6,    3,   84,    2, 0x06 /* Public */,
       8,    2,   91,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    0,   96,    2, 0x09 /* Protected */,
      10,    0,   97,    2, 0x09 /* Protected */,
      11,    0,   98,    2, 0x09 /* Protected */,
      12,    1,   99,    2, 0x09 /* Protected */,
      15,    1,  102,    2, 0x09 /* Protected */,
      16,    0,  105,    2, 0x09 /* Protected */,
      17,    1,  106,    2, 0x09 /* Protected */,
      17,    2,  109,    2, 0x09 /* Protected */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5,    2,
    QMetaType::Void, 0x80000000 | 7, 0x80000000 | 7, 0x80000000 | 7,    2,    2,    2,
    QMetaType::Void, 0x80000000 | 7, QMetaType::Int,    2,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 13,   14,
    QMetaType::Void, 0x80000000 | 13,   14,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 13,   14,
    QMetaType::Void, 0x80000000 | 13, QMetaType::Int,   14,   18,

       0        // eod
};

void BaseTabWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        BaseTabWidget *_t = static_cast<BaseTabWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->progressUpdated(); break;
        case 1: _t->closedTask(); break;
        case 2: _t->removeMe((*reinterpret_cast< QWidget*(*)>(_a[1]))); break;
        case 3: _t->changeItem((*reinterpret_cast< DWORD(*)>(_a[1])),(*reinterpret_cast< DWORD(*)>(_a[2])),(*reinterpret_cast< DWORD(*)>(_a[3]))); break;
        case 4: _t->change_progress((*reinterpret_cast< DWORD(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 5: _t->start_clicked(); break;
        case 6: _t->cancel_clicked(); break;
        case 7: _t->exit_clicked(); break;
        case 8: _t->DeviceDetected((*reinterpret_cast< const DM::PORT*(*)>(_a[1]))); break;
        case 9: _t->DeviceDisconencted((*reinterpret_cast< const DM::PORT*(*)>(_a[1]))); break;
        case 10: _t->FinishDetected(); break;
        case 11: _t->DeviceNotDetected((*reinterpret_cast< const DM::PORT*(*)>(_a[1]))); break;
        case 12: _t->DeviceNotDetected((*reinterpret_cast< const DM::PORT*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QWidget* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (BaseTabWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&BaseTabWidget::progressUpdated)) {
                *result = 0;
            }
        }
        {
            typedef void (BaseTabWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&BaseTabWidget::closedTask)) {
                *result = 1;
            }
        }
        {
            typedef void (BaseTabWidget::*_t)(QWidget * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&BaseTabWidget::removeMe)) {
                *result = 2;
            }
        }
        {
            typedef void (BaseTabWidget::*_t)(DWORD , DWORD , DWORD );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&BaseTabWidget::changeItem)) {
                *result = 3;
            }
        }
        {
            typedef void (BaseTabWidget::*_t)(DWORD , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&BaseTabWidget::change_progress)) {
                *result = 4;
            }
        }
    }
}

const QMetaObject BaseTabWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_BaseTabWidget.data,
      qt_meta_data_BaseTabWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *BaseTabWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *BaseTabWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_BaseTabWidget.stringdata0))
        return static_cast<void*>(const_cast< BaseTabWidget*>(this));
    if (!strcmp(_clname, "AbstractTaskCreator"))
        return static_cast< AbstractTaskCreator*>(const_cast< BaseTabWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int BaseTabWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void BaseTabWidget::progressUpdated()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void BaseTabWidget::closedTask()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void BaseTabWidget::removeMe(QWidget * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void BaseTabWidget::changeItem(DWORD _t1, DWORD _t2, DWORD _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void BaseTabWidget::change_progress(DWORD _t1, int _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_END_MOC_NAMESPACE
