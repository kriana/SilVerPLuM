/****************************************************************************
** Meta object code from reading C++ file 'globalsettingsdialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/globalsettingsdialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'globalsettingsdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_GlobalSettingsDialog_t {
    QByteArrayData data[9];
    char stringdata0[120];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GlobalSettingsDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GlobalSettingsDialog_t qt_meta_stringdata_GlobalSettingsDialog = {
    {
QT_MOC_LITERAL(0, 0, 20), // "GlobalSettingsDialog"
QT_MOC_LITERAL(1, 21, 7), // "discart"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 4), // "save"
QT_MOC_LITERAL(4, 35, 13), // "saveOrDiscart"
QT_MOC_LITERAL(5, 49, 16), // "QAbstractButton*"
QT_MOC_LITERAL(6, 66, 6), // "button"
QT_MOC_LITERAL(7, 73, 15), // "addProgramEntry"
QT_MOC_LITERAL(8, 89, 30) // "ExternalProgramSettingsWidget*"

    },
    "GlobalSettingsDialog\0discart\0\0save\0"
    "saveOrDiscart\0QAbstractButton*\0button\0"
    "addProgramEntry\0ExternalProgramSettingsWidget*"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GlobalSettingsDialog[] = {

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
       1,    0,   34,    2, 0x0a /* Public */,
       3,    0,   35,    2, 0x0a /* Public */,
       4,    1,   36,    2, 0x0a /* Public */,
       7,    0,   39,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5,    6,
    0x80000000 | 8,

       0        // eod
};

void GlobalSettingsDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        GlobalSettingsDialog *_t = static_cast<GlobalSettingsDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->discart(); break;
        case 1: _t->save(); break;
        case 2: _t->saveOrDiscart((*reinterpret_cast< QAbstractButton*(*)>(_a[1]))); break;
        case 3: { ExternalProgramSettingsWidget* _r = _t->addProgramEntry();
            if (_a[0]) *reinterpret_cast< ExternalProgramSettingsWidget**>(_a[0]) = _r; }  break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractButton* >(); break;
            }
            break;
        }
    }
}

const QMetaObject GlobalSettingsDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_GlobalSettingsDialog.data,
      qt_meta_data_GlobalSettingsDialog,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *GlobalSettingsDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GlobalSettingsDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_GlobalSettingsDialog.stringdata0))
        return static_cast<void*>(const_cast< GlobalSettingsDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int GlobalSettingsDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
