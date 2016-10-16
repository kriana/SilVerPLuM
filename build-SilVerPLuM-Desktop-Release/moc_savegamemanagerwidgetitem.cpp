/****************************************************************************
** Meta object code from reading C++ file 'savegamemanagerwidgetitem.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/savegamemanagerwidgetitem.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'savegamemanagerwidgetitem.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_SavegameManagerWidgetItem_t {
    QByteArrayData data[13];
    char stringdata0[180];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SavegameManagerWidgetItem_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SavegameManagerWidgetItem_t qt_meta_stringdata_SavegameManagerWidgetItem = {
    {
QT_MOC_LITERAL(0, 0, 25), // "SavegameManagerWidgetItem"
QT_MOC_LITERAL(1, 26, 10), // "updateData"
QT_MOC_LITERAL(2, 37, 0), // ""
QT_MOC_LITERAL(3, 38, 10), // "reloadList"
QT_MOC_LITERAL(4, 49, 15), // "showMoreToggled"
QT_MOC_LITERAL(5, 65, 6), // "toggle"
QT_MOC_LITERAL(6, 72, 14), // "savegameBackup"
QT_MOC_LITERAL(7, 87, 14), // "savegameDelete"
QT_MOC_LITERAL(8, 102, 18), // "savegameDeleteMain"
QT_MOC_LITERAL(9, 121, 14), // "savegameCopyTo"
QT_MOC_LITERAL(10, 136, 14), // "savegameSingle"
QT_MOC_LITERAL(11, 151, 13), // "savegamePrune"
QT_MOC_LITERAL(12, 165, 14) // "savegameExport"

    },
    "SavegameManagerWidgetItem\0updateData\0"
    "\0reloadList\0showMoreToggled\0toggle\0"
    "savegameBackup\0savegameDelete\0"
    "savegameDeleteMain\0savegameCopyTo\0"
    "savegameSingle\0savegamePrune\0"
    "savegameExport"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SavegameManagerWidgetItem[] = {

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
       1,    0,   64,    2, 0x0a /* Public */,
       3,    0,   65,    2, 0x0a /* Public */,
       4,    1,   66,    2, 0x08 /* Private */,
       6,    0,   69,    2, 0x08 /* Private */,
       7,    0,   70,    2, 0x08 /* Private */,
       8,    0,   71,    2, 0x08 /* Private */,
       9,    0,   72,    2, 0x08 /* Private */,
      10,    0,   73,    2, 0x08 /* Private */,
      11,    0,   74,    2, 0x08 /* Private */,
      12,    0,   75,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void SavegameManagerWidgetItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SavegameManagerWidgetItem *_t = static_cast<SavegameManagerWidgetItem *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->updateData(); break;
        case 1: _t->reloadList(); break;
        case 2: _t->showMoreToggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->savegameBackup(); break;
        case 4: _t->savegameDelete(); break;
        case 5: _t->savegameDeleteMain(); break;
        case 6: _t->savegameCopyTo(); break;
        case 7: _t->savegameSingle(); break;
        case 8: _t->savegamePrune(); break;
        case 9: _t->savegameExport(); break;
        default: ;
        }
    }
}

const QMetaObject SavegameManagerWidgetItem::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_SavegameManagerWidgetItem.data,
      qt_meta_data_SavegameManagerWidgetItem,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *SavegameManagerWidgetItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SavegameManagerWidgetItem::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_SavegameManagerWidgetItem.stringdata0))
        return static_cast<void*>(const_cast< SavegameManagerWidgetItem*>(this));
    return QWidget::qt_metacast(_clname);
}

int SavegameManagerWidgetItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
