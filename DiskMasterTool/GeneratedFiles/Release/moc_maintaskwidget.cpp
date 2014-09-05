/****************************************************************************
** Meta object code from reading C++ file 'maintaskwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../maintaskwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'maintaskwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_SectorModifyDialog_t {
    QByteArrayData data[5];
    char stringdata[68];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_SectorModifyDialog_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_SectorModifyDialog_t qt_meta_stringdata_SectorModifyDialog = {
    {
QT_MOC_LITERAL(0, 0, 18),
QT_MOC_LITERAL(1, 19, 15),
QT_MOC_LITERAL(2, 35, 0),
QT_MOC_LITERAL(3, 36, 14),
QT_MOC_LITERAL(4, 51, 15)
    },
    "SectorModifyDialog\0ModifySignature\0\0"
    "WriteSignature\0VerifySignature\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SectorModifyDialog[] = {

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
       1,    0,   29,    2, 0x0a,
       3,    0,   30,    2, 0x0a,
       4,    0,   31,    2, 0x0a,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void SectorModifyDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SectorModifyDialog *_t = static_cast<SectorModifyDialog *>(_o);
        switch (_id) {
        case 0: _t->ModifySignature(); break;
        case 1: _t->WriteSignature(); break;
        case 2: _t->VerifySignature(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject SectorModifyDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_SectorModifyDialog.data,
      qt_meta_data_SectorModifyDialog,  qt_static_metacall, 0, 0}
};


const QMetaObject *SectorModifyDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SectorModifyDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SectorModifyDialog.stringdata))
        return static_cast<void*>(const_cast< SectorModifyDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int SectorModifyDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
struct qt_meta_stringdata_MainTaskWidget_t {
    QByteArrayData data[31];
    char stringdata[446];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_MainTaskWidget_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_MainTaskWidget_t qt_meta_stringdata_MainTaskWidget = {
    {
QT_MOC_LITERAL(0, 0, 14),
QT_MOC_LITERAL(1, 15, 17),
QT_MOC_LITERAL(2, 33, 0),
QT_MOC_LITERAL(3, 34, 17),
QT_MOC_LITERAL(4, 52, 8),
QT_MOC_LITERAL(5, 61, 16),
QT_MOC_LITERAL(6, 78, 11),
QT_MOC_LITERAL(7, 90, 16),
QT_MOC_LITERAL(8, 107, 12),
QT_MOC_LITERAL(9, 120, 12),
QT_MOC_LITERAL(10, 133, 13),
QT_MOC_LITERAL(11, 147, 19),
QT_MOC_LITERAL(12, 167, 11),
QT_MOC_LITERAL(13, 179, 20),
QT_MOC_LITERAL(14, 200, 17),
QT_MOC_LITERAL(15, 218, 19),
QT_MOC_LITERAL(16, 238, 18),
QT_MOC_LITERAL(17, 257, 12),
QT_MOC_LITERAL(18, 270, 14),
QT_MOC_LITERAL(19, 285, 13),
QT_MOC_LITERAL(20, 299, 14),
QT_MOC_LITERAL(21, 314, 15),
QT_MOC_LITERAL(22, 330, 14),
QT_MOC_LITERAL(23, 345, 8),
QT_MOC_LITERAL(24, 354, 10),
QT_MOC_LITERAL(25, 365, 15),
QT_MOC_LITERAL(26, 381, 6),
QT_MOC_LITERAL(27, 388, 12),
QT_MOC_LITERAL(28, 401, 11),
QT_MOC_LITERAL(29, 413, 14),
QT_MOC_LITERAL(30, 428, 16)
    },
    "MainTaskWidget\0ShowCurrentWidget\0\0"
    "const DMItemIdex*\0LoadTask\0CreateTaskWidget\0"
    "PortNumbers\0DeviceDisappered\0SelectedItem\0"
    "ItemSelected\0AddDiskMaster\0"
    "DM::DiskController*\0disk_master\0"
    "RemoveDiskMasterItem\0CopyButtonClicked\0"
    "VerifyButtonClicked\0EraseButtonClicked\0"
    "ModifySector\0ElementClicked\0clicked_index\0"
    "Double_Clicked\0ElementSelected\0"
    "QItemSelection\0selected\0deselected\0"
    "setButtonEnable\0enable\0changeEnable\0"
    "model_index\0UpdateTreeView\0LoadTask_ckicked\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainTaskWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      20,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,  114,    2, 0x06,
       4,    2,  119,    2, 0x06,
       5,    3,  124,    2, 0x06,
       7,    1,  131,    2, 0x06,
       8,    0,  134,    2, 0x06,
       9,    1,  135,    2, 0x06,

 // slots: name, argc, parameters, tag, flags
      10,    1,  138,    2, 0x08,
      13,    1,  141,    2, 0x08,
      14,    0,  144,    2, 0x08,
      15,    0,  145,    2, 0x08,
      16,    0,  146,    2, 0x08,
      17,    0,  147,    2, 0x08,
      18,    1,  148,    2, 0x08,
      20,    1,  151,    2, 0x08,
      21,    2,  154,    2, 0x08,
      25,    1,  159,    2, 0x08,
      25,    0,  162,    2, 0x28,
      27,    1,  163,    2, 0x08,
      29,    0,  166,    2, 0x08,
      30,    0,  167,    2, 0x08,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int,    2,    2,
    QMetaType::Void, 0x80000000 | 3, QMetaType::QString,    2,    2,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int, 0x80000000 | 6,    2,    2,    2,
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 3,    2,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 11,   12,
    QMetaType::Void, 0x80000000 | 11,   12,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QModelIndex,   19,
    QMetaType::Void, QMetaType::QModelIndex,   19,
    QMetaType::Void, 0x80000000 | 22, 0x80000000 | 22,   23,   24,
    QMetaType::Void, QMetaType::Bool,   26,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QModelIndex,   28,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainTaskWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainTaskWidget *_t = static_cast<MainTaskWidget *>(_o);
        switch (_id) {
        case 0: _t->ShowCurrentWidget((*reinterpret_cast< const DMItemIdex*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->LoadTask((*reinterpret_cast< const DMItemIdex*(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 2: _t->CreateTaskWidget((*reinterpret_cast< const DMItemIdex*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< PortNumbers(*)>(_a[3]))); break;
        case 3: _t->DeviceDisappered((*reinterpret_cast< const DMItemIdex*(*)>(_a[1]))); break;
        case 4: _t->SelectedItem(); break;
        case 5: _t->ItemSelected((*reinterpret_cast< const DMItemIdex*(*)>(_a[1]))); break;
        case 6: _t->AddDiskMaster((*reinterpret_cast< DM::DiskController*(*)>(_a[1]))); break;
        case 7: _t->RemoveDiskMasterItem((*reinterpret_cast< DM::DiskController*(*)>(_a[1]))); break;
        case 8: _t->CopyButtonClicked(); break;
        case 9: _t->VerifyButtonClicked(); break;
        case 10: _t->EraseButtonClicked(); break;
        case 11: _t->ModifySector(); break;
        case 12: _t->ElementClicked((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 13: _t->Double_Clicked((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 14: _t->ElementSelected((*reinterpret_cast< const QItemSelection(*)>(_a[1])),(*reinterpret_cast< const QItemSelection(*)>(_a[2]))); break;
        case 15: _t->setButtonEnable((*reinterpret_cast< const bool(*)>(_a[1]))); break;
        case 16: _t->setButtonEnable(); break;
        case 17: _t->changeEnable((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 18: _t->UpdateTreeView(); break;
        case 19: _t->LoadTask_ckicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (MainTaskWidget::*_t)(const DMItemIdex * , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainTaskWidget::ShowCurrentWidget)) {
                *result = 0;
            }
        }
        {
            typedef void (MainTaskWidget::*_t)(const DMItemIdex * , const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainTaskWidget::LoadTask)) {
                *result = 1;
            }
        }
        {
            typedef void (MainTaskWidget::*_t)(const DMItemIdex * , int , PortNumbers );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainTaskWidget::CreateTaskWidget)) {
                *result = 2;
            }
        }
        {
            typedef void (MainTaskWidget::*_t)(const DMItemIdex * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainTaskWidget::DeviceDisappered)) {
                *result = 3;
            }
        }
        {
            typedef void (MainTaskWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainTaskWidget::SelectedItem)) {
                *result = 4;
            }
        }
        {
            typedef void (MainTaskWidget::*_t)(const DMItemIdex * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainTaskWidget::ItemSelected)) {
                *result = 5;
            }
        }
    }
}

const QMetaObject MainTaskWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_MainTaskWidget.data,
      qt_meta_data_MainTaskWidget,  qt_static_metacall, 0, 0}
};


const QMetaObject *MainTaskWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainTaskWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainTaskWidget.stringdata))
        return static_cast<void*>(const_cast< MainTaskWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int MainTaskWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 20)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 20;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 20)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 20;
    }
    return _id;
}

// SIGNAL 0
void MainTaskWidget::ShowCurrentWidget(const DMItemIdex * _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MainTaskWidget::LoadTask(const DMItemIdex * _t1, const QString & _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void MainTaskWidget::CreateTaskWidget(const DMItemIdex * _t1, int _t2, PortNumbers _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void MainTaskWidget::DeviceDisappered(const DMItemIdex * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void MainTaskWidget::SelectedItem()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}

// SIGNAL 5
void MainTaskWidget::ItemSelected(const DMItemIdex * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_END_MOC_NAMESPACE
