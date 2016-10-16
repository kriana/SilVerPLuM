/****************************************************************************
** Meta object code from reading C++ file 'profile.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/profile.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'profile.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Profile_t {
    QByteArrayData data[7];
    char stringdata0[80];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Profile_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Profile_t qt_meta_stringdata_Profile = {
    {
QT_MOC_LITERAL(0, 0, 7), // "Profile"
QT_MOC_LITERAL(1, 8, 7), // "updated"
QT_MOC_LITERAL(2, 16, 0), // ""
QT_MOC_LITERAL(3, 17, 15), // "updatedSettings"
QT_MOC_LITERAL(4, 33, 11), // "updatedMods"
QT_MOC_LITERAL(5, 45, 16), // "updatedSavegames"
QT_MOC_LITERAL(6, 62, 17) // "repairDirectories"

    },
    "Profile\0updated\0\0updatedSettings\0"
    "updatedMods\0updatedSavegames\0"
    "repairDirectories"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Profile[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x06 /* Public */,
       3,    0,   40,    2, 0x06 /* Public */,
       4,    0,   41,    2, 0x06 /* Public */,
       5,    0,   42,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   43,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void Profile::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Profile *_t = static_cast<Profile *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->updated(); break;
        case 1: _t->updatedSettings(); break;
        case 2: _t->updatedMods(); break;
        case 3: _t->updatedSavegames(); break;
        case 4: _t->repairDirectories(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Profile::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Profile::updated)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (Profile::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Profile::updatedSettings)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (Profile::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Profile::updatedMods)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (Profile::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Profile::updatedSavegames)) {
                *result = 3;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject Profile::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Profile.data,
      qt_meta_data_Profile,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Profile::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Profile::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Profile.stringdata0))
        return static_cast<void*>(const_cast< Profile*>(this));
    return QObject::qt_metacast(_clname);
}

int Profile::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void Profile::updated()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void Profile::updatedSettings()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void Profile::updatedMods()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}

// SIGNAL 3
void Profile::updatedSavegames()
{
    QMetaObject::activate(this, &staticMetaObject, 3, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
