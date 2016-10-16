/****************************************************************************
** Meta object code from reading C++ file 'modmanagerwidgetitem.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/modmanagerwidgetitem.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'modmanagerwidgetitem.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ModManagerWidgetItem_t {
    QByteArrayData data[15];
    char stringdata0[209];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ModManagerWidgetItem_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ModManagerWidgetItem_t qt_meta_stringdata_ModManagerWidgetItem = {
    {
QT_MOC_LITERAL(0, 0, 20), // "ModManagerWidgetItem"
QT_MOC_LITERAL(1, 21, 15), // "showMoreToggled"
QT_MOC_LITERAL(2, 37, 0), // ""
QT_MOC_LITERAL(3, 38, 6), // "toggle"
QT_MOC_LITERAL(4, 45, 22), // "contentEnabledDisabled"
QT_MOC_LITERAL(5, 68, 9), // "contentid"
QT_MOC_LITERAL(6, 78, 7), // "enabled"
QT_MOC_LITERAL(7, 86, 13), // "enableClicked"
QT_MOC_LITERAL(8, 100, 14), // "disableClicked"
QT_MOC_LITERAL(9, 115, 13), // "moveUpClicked"
QT_MOC_LITERAL(10, 129, 15), // "moveDownClicked"
QT_MOC_LITERAL(11, 145, 13), // "deleteClicked"
QT_MOC_LITERAL(12, 159, 20), // "copyToProfileClicked"
QT_MOC_LITERAL(13, 180, 14), // "reprimeClicked"
QT_MOC_LITERAL(14, 195, 13) // "exportClicked"

    },
    "ModManagerWidgetItem\0showMoreToggled\0"
    "\0toggle\0contentEnabledDisabled\0contentid\0"
    "enabled\0enableClicked\0disableClicked\0"
    "moveUpClicked\0moveDownClicked\0"
    "deleteClicked\0copyToProfileClicked\0"
    "reprimeClicked\0exportClicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ModManagerWidgetItem[] = {

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
       1,    1,   64,    2, 0x08 /* Private */,
       4,    2,   67,    2, 0x08 /* Private */,
       7,    0,   72,    2, 0x08 /* Private */,
       8,    0,   73,    2, 0x08 /* Private */,
       9,    0,   74,    2, 0x08 /* Private */,
      10,    0,   75,    2, 0x08 /* Private */,
      11,    0,   76,    2, 0x08 /* Private */,
      12,    0,   77,    2, 0x08 /* Private */,
      13,    0,   78,    2, 0x08 /* Private */,
      14,    0,   79,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool,    5,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ModManagerWidgetItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ModManagerWidgetItem *_t = static_cast<ModManagerWidgetItem *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->showMoreToggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->contentEnabledDisabled((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 2: _t->enableClicked(); break;
        case 3: _t->disableClicked(); break;
        case 4: _t->moveUpClicked(); break;
        case 5: _t->moveDownClicked(); break;
        case 6: _t->deleteClicked(); break;
        case 7: _t->copyToProfileClicked(); break;
        case 8: _t->reprimeClicked(); break;
        case 9: _t->exportClicked(); break;
        default: ;
        }
    }
}

const QMetaObject ModManagerWidgetItem::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ModManagerWidgetItem.data,
      qt_meta_data_ModManagerWidgetItem,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ModManagerWidgetItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ModManagerWidgetItem::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ModManagerWidgetItem.stringdata0))
        return static_cast<void*>(const_cast< ModManagerWidgetItem*>(this));
    return QWidget::qt_metacast(_clname);
}

int ModManagerWidgetItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
