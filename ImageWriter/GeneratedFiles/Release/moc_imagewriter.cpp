/****************************************************************************
** Meta object code from reading C++ file 'imagewriter.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../imagewriter.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'imagewriter.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ImageWriter_t {
    QByteArrayData data[11];
    char stringdata[129];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_ImageWriter_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_ImageWriter_t qt_meta_stringdata_ImageWriter = {
    {
QT_MOC_LITERAL(0, 0, 11),
QT_MOC_LITERAL(1, 12, 14),
QT_MOC_LITERAL(2, 27, 0),
QT_MOC_LITERAL(3, 28, 13),
QT_MOC_LITERAL(4, 42, 18),
QT_MOC_LITERAL(5, 61, 11),
QT_MOC_LITERAL(6, 73, 10),
QT_MOC_LITERAL(7, 84, 13),
QT_MOC_LITERAL(8, 98, 10),
QT_MOC_LITERAL(9, 109, 11),
QT_MOC_LITERAL(10, 121, 6)
    },
    "ImageWriter\0FileOpenCliced\0\0HddOpenCliced\0"
    "StartButtonClicked\0OnErrorName\0"
    "error_text\0OnFinishError\0OnFinishOk\0"
    "OnUpdateLba\0sector\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ImageWriter[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x0a,
       3,    0,   50,    2, 0x0a,
       4,    0,   51,    2, 0x0a,
       5,    1,   52,    2, 0x0a,
       7,    1,   55,    2, 0x0a,
       8,    0,   58,    2, 0x0a,
       9,    1,   59,    2, 0x0a,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void,
    QMetaType::Void, QMetaType::LongLong,   10,

       0        // eod
};

void ImageWriter::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ImageWriter *_t = static_cast<ImageWriter *>(_o);
        switch (_id) {
        case 0: _t->FileOpenCliced(); break;
        case 1: _t->HddOpenCliced(); break;
        case 2: _t->StartButtonClicked(); break;
        case 3: _t->OnErrorName((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->OnFinishError((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->OnFinishOk(); break;
        case 6: _t->OnUpdateLba((*reinterpret_cast< qlonglong(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject ImageWriter::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_ImageWriter.data,
      qt_meta_data_ImageWriter,  qt_static_metacall, 0, 0}
};


const QMetaObject *ImageWriter::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ImageWriter::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ImageWriter.stringdata))
        return static_cast<void*>(const_cast< ImageWriter*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int ImageWriter::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}
struct qt_meta_stringdata_CopyThread_t {
    QByteArrayData data[6];
    char stringdata[58];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_CopyThread_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_CopyThread_t qt_meta_stringdata_CopyThread = {
    {
QT_MOC_LITERAL(0, 0, 10),
QT_MOC_LITERAL(1, 11, 10),
QT_MOC_LITERAL(2, 22, 0),
QT_MOC_LITERAL(3, 23, 12),
QT_MOC_LITERAL(4, 36, 9),
QT_MOC_LITERAL(5, 46, 10)
    },
    "CopyThread\0error_name\0\0finish_error\0"
    "finish_ok\0update_lba\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CopyThread[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06,
       3,    1,   37,    2, 0x06,
       4,    0,   40,    2, 0x06,
       5,    1,   41,    2, 0x06,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::LongLong,    2,

       0        // eod
};

void CopyThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CopyThread *_t = static_cast<CopyThread *>(_o);
        switch (_id) {
        case 0: _t->error_name((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->finish_error((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->finish_ok(); break;
        case 3: _t->update_lba((*reinterpret_cast< qlonglong(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (CopyThread::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CopyThread::error_name)) {
                *result = 0;
            }
        }
        {
            typedef void (CopyThread::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CopyThread::finish_error)) {
                *result = 1;
            }
        }
        {
            typedef void (CopyThread::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CopyThread::finish_ok)) {
                *result = 2;
            }
        }
        {
            typedef void (CopyThread::*_t)(qlonglong );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CopyThread::update_lba)) {
                *result = 3;
            }
        }
    }
}

const QMetaObject CopyThread::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_CopyThread.data,
      qt_meta_data_CopyThread,  qt_static_metacall, 0, 0}
};


const QMetaObject *CopyThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CopyThread::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CopyThread.stringdata))
        return static_cast<void*>(const_cast< CopyThread*>(this));
    return QThread::qt_metacast(_clname);
}

int CopyThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void CopyThread::error_name(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CopyThread::finish_error(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void CopyThread::finish_ok()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void CopyThread::update_lba(qlonglong _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE
