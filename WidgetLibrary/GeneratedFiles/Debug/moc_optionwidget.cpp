/****************************************************************************
** Meta object code from reading C++ file 'optionwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../include/WidgetLibrary/optionwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'optionwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_OptionWidget_t {
    QByteArrayData data[10];
    char stringdata[126];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_OptionWidget_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_OptionWidget_t qt_meta_stringdata_OptionWidget = {
    {
QT_MOC_LITERAL(0, 0, 12),
QT_MOC_LITERAL(1, 13, 12),
QT_MOC_LITERAL(2, 26, 0),
QT_MOC_LITERAL(3, 27, 14),
QT_MOC_LITERAL(4, 42, 14),
QT_MOC_LITERAL(5, 57, 16),
QT_MOC_LITERAL(6, 74, 6),
QT_MOC_LITERAL(7, 81, 18),
QT_MOC_LITERAL(8, 100, 5),
QT_MOC_LITERAL(9, 106, 18)
    },
    "OptionWidget\0ChirpChanged\0\0EndBeepChanged\0"
    "CRCBeepChanged\0on_chirp_changed\0bChirp\0"
    "on_EndBeep_changed\0bBeep\0on_CRCBeep_changed\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_OptionWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x06,
       3,    1,   47,    2, 0x06,
       4,    1,   50,    2, 0x06,

 // slots: name, argc, parameters, tag, flags
       5,    1,   53,    2, 0x08,
       7,    1,   56,    2, 0x08,
       9,    1,   59,    2, 0x08,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, QMetaType::Int,    8,

       0        // eod
};

void OptionWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        OptionWidget *_t = static_cast<OptionWidget *>(_o);
        switch (_id) {
        case 0: _t->ChirpChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->EndBeepChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->CRCBeepChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->on_chirp_changed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->on_EndBeep_changed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->on_CRCBeep_changed((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (OptionWidget::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&OptionWidget::ChirpChanged)) {
                *result = 0;
            }
        }
        {
            typedef void (OptionWidget::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&OptionWidget::EndBeepChanged)) {
                *result = 1;
            }
        }
        {
            typedef void (OptionWidget::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&OptionWidget::CRCBeepChanged)) {
                *result = 2;
            }
        }
    }
}

const QMetaObject OptionWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_OptionWidget.data,
      qt_meta_data_OptionWidget,  qt_static_metacall, 0, 0}
};


const QMetaObject *OptionWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *OptionWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_OptionWidget.stringdata))
        return static_cast<void*>(const_cast< OptionWidget*>(this));
    if (!strcmp(_clname, "IOptionsView"))
        return static_cast< IOptionsView*>(const_cast< OptionWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int OptionWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void OptionWidget::ChirpChanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void OptionWidget::EndBeepChanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void OptionWidget::CRCBeepChanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
