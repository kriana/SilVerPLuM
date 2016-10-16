/****************************************************************************
** Meta object code from reading C++ file 'modimporter.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/modimporter.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'modimporter.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ModImporter_t {
    QByteArrayData data[7];
    char stringdata0[72];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ModImporter_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ModImporter_t qt_meta_stringdata_ModImporter = {
    {
QT_MOC_LITERAL(0, 0, 11), // "ModImporter"
QT_MOC_LITERAL(1, 12, 10), // "addContent"
QT_MOC_LITERAL(2, 23, 23), // "ModImporterContentItem*"
QT_MOC_LITERAL(3, 47, 0), // ""
QT_MOC_LITERAL(4, 48, 6), // "import"
QT_MOC_LITERAL(5, 55, 11), // "nameChanged"
QT_MOC_LITERAL(6, 67, 4) // "text"

    },
    "ModImporter\0addContent\0ModImporterContentItem*\0"
    "\0import\0nameChanged\0text"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ModImporter[] = {

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
       1,    0,   29,    3, 0x08 /* Private */,
       4,    0,   30,    3, 0x08 /* Private */,
       5,    1,   31,    3, 0x08 /* Private */,

 // slots: parameters
    0x80000000 | 2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    6,

       0        // eod
};

void ModImporter::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ModImporter *_t = static_cast<ModImporter *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: { ModImporterContentItem* _r = _t->addContent();
            if (_a[0]) *reinterpret_cast< ModImporterContentItem**>(_a[0]) = _r; }  break;
        case 1: _t->import(); break;
        case 2: _t->nameChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject ModImporter::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_ModImporter.data,
      qt_meta_data_ModImporter,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ModImporter::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ModImporter::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ModImporter.stringdata0))
        return static_cast<void*>(const_cast< ModImporter*>(this));
    return QDialog::qt_metacast(_clname);
}

int ModImporter::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
QT_END_MOC_NAMESPACE
