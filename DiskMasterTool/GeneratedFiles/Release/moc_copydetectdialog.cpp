/****************************************************************************
** Meta object code from reading C++ file 'copydetectdialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../copydetectdialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'copydetectdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_CopyProperiesUiDialog_t {
    QByteArrayData data[5];
    char stringdata[77];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_CopyProperiesUiDialog_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_CopyProperiesUiDialog_t qt_meta_stringdata_CopyProperiesUiDialog = {
    {
QT_MOC_LITERAL(0, 0, 21),
QT_MOC_LITERAL(1, 22, 15),
QT_MOC_LITERAL(2, 38, 0),
QT_MOC_LITERAL(3, 39, 20),
QT_MOC_LITERAL(4, 60, 15)
    },
    "CopyProperiesUiDialog\0FullCopyClicked\0"
    "\0PartitionCopyClicked\0UserCopyClicked\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CopyProperiesUiDialog[] = {

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
       1,    0,   29,    2, 0x08,
       3,    0,   30,    2, 0x08,
       4,    0,   31,    2, 0x08,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void CopyProperiesUiDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CopyProperiesUiDialog *_t = static_cast<CopyProperiesUiDialog *>(_o);
        switch (_id) {
        case 0: _t->FullCopyClicked(); break;
        case 1: _t->PartitionCopyClicked(); break;
        case 2: _t->UserCopyClicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject CopyProperiesUiDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_CopyProperiesUiDialog.data,
      qt_meta_data_CopyProperiesUiDialog,  qt_static_metacall, 0, 0}
};


const QMetaObject *CopyProperiesUiDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CopyProperiesUiDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CopyProperiesUiDialog.stringdata))
        return static_cast<void*>(const_cast< CopyProperiesUiDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int CopyProperiesUiDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
struct qt_meta_stringdata_AbstractDetectDialog_t {
    QByteArrayData data[3];
    char stringdata[30];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_AbstractDetectDialog_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_AbstractDetectDialog_t qt_meta_stringdata_AbstractDetectDialog = {
    {
QT_MOC_LITERAL(0, 0, 20),
QT_MOC_LITERAL(1, 21, 6),
QT_MOC_LITERAL(2, 28, 0)
    },
    "AbstractDetectDialog\0accept\0\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AbstractDetectDialog[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   19,    2, 0x0a,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void AbstractDetectDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        AbstractDetectDialog *_t = static_cast<AbstractDetectDialog *>(_o);
        switch (_id) {
        case 0: _t->accept(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject AbstractDetectDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_AbstractDetectDialog.data,
      qt_meta_data_AbstractDetectDialog,  qt_static_metacall, 0, 0}
};


const QMetaObject *AbstractDetectDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AbstractDetectDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_AbstractDetectDialog.stringdata))
        return static_cast<void*>(const_cast< AbstractDetectDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int AbstractDetectDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}
struct qt_meta_stringdata_CopyDetectDialog_t {
    QByteArrayData data[6];
    char stringdata[91];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_CopyDetectDialog_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_CopyDetectDialog_t qt_meta_stringdata_CopyDetectDialog = {
    {
QT_MOC_LITERAL(0, 0, 16),
QT_MOC_LITERAL(1, 17, 18),
QT_MOC_LITERAL(2, 36, 0),
QT_MOC_LITERAL(3, 37, 15),
QT_MOC_LITERAL(4, 53, 20),
QT_MOC_LITERAL(5, 74, 15)
    },
    "CopyDetectDialog\0copySettingClicked\0"
    "\0fullCopyClicked\0partitionCopyClicked\0"
    "userCopyClicked\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CopyDetectDialog[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x0a,
       3,    0,   35,    2, 0x08,
       4,    0,   36,    2, 0x08,
       5,    0,   37,    2, 0x08,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void CopyDetectDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CopyDetectDialog *_t = static_cast<CopyDetectDialog *>(_o);
        switch (_id) {
        case 0: _t->copySettingClicked(); break;
        case 1: _t->fullCopyClicked(); break;
        case 2: _t->partitionCopyClicked(); break;
        case 3: _t->userCopyClicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject CopyDetectDialog::staticMetaObject = {
    { &AbstractDetectDialog::staticMetaObject, qt_meta_stringdata_CopyDetectDialog.data,
      qt_meta_data_CopyDetectDialog,  qt_static_metacall, 0, 0}
};


const QMetaObject *CopyDetectDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CopyDetectDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CopyDetectDialog.stringdata))
        return static_cast<void*>(const_cast< CopyDetectDialog*>(this));
    return AbstractDetectDialog::qt_metacast(_clname);
}

int CopyDetectDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AbstractDetectDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}
struct qt_meta_stringdata_VerifyDetectDialog_t {
    QByteArrayData data[1];
    char stringdata[20];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_VerifyDetectDialog_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_VerifyDetectDialog_t qt_meta_stringdata_VerifyDetectDialog = {
    {
QT_MOC_LITERAL(0, 0, 18)
    },
    "VerifyDetectDialog\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VerifyDetectDialog[] = {

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

void VerifyDetectDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject VerifyDetectDialog::staticMetaObject = {
    { &AbstractDetectDialog::staticMetaObject, qt_meta_stringdata_VerifyDetectDialog.data,
      qt_meta_data_VerifyDetectDialog,  qt_static_metacall, 0, 0}
};


const QMetaObject *VerifyDetectDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VerifyDetectDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_VerifyDetectDialog.stringdata))
        return static_cast<void*>(const_cast< VerifyDetectDialog*>(this));
    return AbstractDetectDialog::qt_metacast(_clname);
}

int VerifyDetectDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AbstractDetectDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
struct qt_meta_stringdata_EraseDetectDialog_t {
    QByteArrayData data[1];
    char stringdata[19];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_EraseDetectDialog_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_EraseDetectDialog_t qt_meta_stringdata_EraseDetectDialog = {
    {
QT_MOC_LITERAL(0, 0, 17)
    },
    "EraseDetectDialog\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_EraseDetectDialog[] = {

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

void EraseDetectDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject EraseDetectDialog::staticMetaObject = {
    { &AbstractDetectDialog::staticMetaObject, qt_meta_stringdata_EraseDetectDialog.data,
      qt_meta_data_EraseDetectDialog,  qt_static_metacall, 0, 0}
};


const QMetaObject *EraseDetectDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *EraseDetectDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_EraseDetectDialog.stringdata))
        return static_cast<void*>(const_cast< EraseDetectDialog*>(this));
    return AbstractDetectDialog::qt_metacast(_clname);
}

int EraseDetectDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AbstractDetectDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
