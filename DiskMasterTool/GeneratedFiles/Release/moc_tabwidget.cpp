/****************************************************************************
** Meta object code from reading C++ file 'tabwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../tabwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tabwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_TabWidget_t {
    QByteArrayData data[29];
    char stringdata[317];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_TabWidget_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_TabWidget_t qt_meta_stringdata_TabWidget = {
    {
QT_MOC_LITERAL(0, 0, 9),
QT_MOC_LITERAL(1, 10, 15),
QT_MOC_LITERAL(2, 26, 0),
QT_MOC_LITERAL(3, 27, 15),
QT_MOC_LITERAL(4, 43, 16),
QT_MOC_LITERAL(5, 60, 13),
QT_MOC_LITERAL(6, 74, 17),
QT_MOC_LITERAL(7, 92, 8),
QT_MOC_LITERAL(8, 101, 10),
QT_MOC_LITERAL(9, 112, 9),
QT_MOC_LITERAL(10, 122, 9),
QT_MOC_LITERAL(11, 132, 8),
QT_MOC_LITERAL(12, 141, 6),
QT_MOC_LITERAL(13, 148, 10),
QT_MOC_LITERAL(14, 159, 14),
QT_MOC_LITERAL(15, 174, 10),
QT_MOC_LITERAL(16, 185, 8),
QT_MOC_LITERAL(17, 194, 10),
QT_MOC_LITERAL(18, 205, 6),
QT_MOC_LITERAL(19, 212, 9),
QT_MOC_LITERAL(20, 222, 10),
QT_MOC_LITERAL(21, 233, 19),
QT_MOC_LITERAL(22, 253, 16),
QT_MOC_LITERAL(23, 270, 5),
QT_MOC_LITERAL(24, 276, 2),
QT_MOC_LITERAL(25, 279, 5),
QT_MOC_LITERAL(26, 285, 6),
QT_MOC_LITERAL(27, 292, 14),
QT_MOC_LITERAL(28, 307, 8)
    },
    "TabWidget\0setEnabledTasks\0\0setEnabledStart\0"
    "setEnabledCancel\0ShowTabWidget\0"
    "const DMItemIdex*\0dm_index\0itemStatus\0"
    "task_load\0RemoveTab\0QWidget*\0widget\0"
    "RemoveTabs\0CloseTabWidget\0iTabNumber\0"
    "CloseTab\0TabChanged\0nIndex\0startTask\0"
    "cancelTask\0Preferences_clicked\0"
    "ChangeItemStatus\0DWORD\0id\0state\0status\0"
    "ChangeProgress\0position\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TabWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   89,    2, 0x06,
       3,    1,   92,    2, 0x06,
       4,    1,   95,    2, 0x06,

 // slots: name, argc, parameters, tag, flags
       5,    2,   98,    2, 0x0a,
       9,    2,  103,    2, 0x0a,
      10,    1,  108,    2, 0x0a,
      13,    1,  111,    2, 0x0a,
      14,    1,  114,    2, 0x0a,
      16,    1,  117,    2, 0x0a,
      17,    1,  120,    2, 0x0a,
      19,    0,  123,    2, 0x0a,
      20,    0,  124,    2, 0x0a,
      21,    0,  125,    2, 0x0a,
      22,    3,  126,    2, 0x0a,
      27,    2,  133,    2, 0x0a,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 6, QMetaType::Int,    7,    8,
    QMetaType::Void, 0x80000000 | 6, QMetaType::QString,    2,    2,
    QMetaType::Void, 0x80000000 | 11,   12,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, QMetaType::Int,   15,
    QMetaType::Void, 0x80000000 | 11,    2,
    QMetaType::Void, QMetaType::Int,   18,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 23, 0x80000000 | 23, 0x80000000 | 23,   24,   25,   26,
    QMetaType::Void, 0x80000000 | 23, QMetaType::Int,   24,   28,

       0        // eod
};

void TabWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TabWidget *_t = static_cast<TabWidget *>(_o);
        switch (_id) {
        case 0: _t->setEnabledTasks((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->setEnabledStart((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->setEnabledCancel((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->ShowTabWidget((*reinterpret_cast< const DMItemIdex*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: _t->task_load((*reinterpret_cast< const DMItemIdex*(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 5: _t->RemoveTab((*reinterpret_cast< QWidget*(*)>(_a[1]))); break;
        case 6: _t->RemoveTabs((*reinterpret_cast< const DMItemIdex*(*)>(_a[1]))); break;
        case 7: _t->CloseTabWidget((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->CloseTab((*reinterpret_cast< QWidget*(*)>(_a[1]))); break;
        case 9: _t->TabChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->startTask(); break;
        case 11: _t->cancelTask(); break;
        case 12: _t->Preferences_clicked(); break;
        case 13: _t->ChangeItemStatus((*reinterpret_cast< DWORD(*)>(_a[1])),(*reinterpret_cast< DWORD(*)>(_a[2])),(*reinterpret_cast< DWORD(*)>(_a[3]))); break;
        case 14: _t->ChangeProgress((*reinterpret_cast< DWORD(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QWidget* >(); break;
            }
            break;
        case 8:
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
            typedef void (TabWidget::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TabWidget::setEnabledTasks)) {
                *result = 0;
            }
        }
        {
            typedef void (TabWidget::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TabWidget::setEnabledStart)) {
                *result = 1;
            }
        }
        {
            typedef void (TabWidget::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TabWidget::setEnabledCancel)) {
                *result = 2;
            }
        }
    }
}

const QMetaObject TabWidget::staticMetaObject = {
    { &QTabWidget::staticMetaObject, qt_meta_stringdata_TabWidget.data,
      qt_meta_data_TabWidget,  qt_static_metacall, 0, 0}
};


const QMetaObject *TabWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TabWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TabWidget.stringdata))
        return static_cast<void*>(const_cast< TabWidget*>(this));
    return QTabWidget::qt_metacast(_clname);
}

int TabWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTabWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    }
    return _id;
}

// SIGNAL 0
void TabWidget::setEnabledTasks(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void TabWidget::setEnabledStart(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void TabWidget::setEnabledCancel(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
