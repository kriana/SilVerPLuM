/****************************************************************************
** Meta object code from reading C++ file 'profilemanager.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/profilemanager.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'profilemanager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ProfileManager_t {
    QByteArrayData data[8];
    char stringdata0[93];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ProfileManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ProfileManager_t qt_meta_stringdata_ProfileManager = {
    {
QT_MOC_LITERAL(0, 0, 14), // "ProfileManager"
QT_MOC_LITERAL(1, 15, 7), // "updated"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 21), // "updatedProfileSetting"
QT_MOC_LITERAL(4, 46, 18), // "updatedProfileList"
QT_MOC_LITERAL(5, 65, 16), // "updatedSelection"
QT_MOC_LITERAL(6, 82, 8), // "Profile*"
QT_MOC_LITERAL(7, 91, 1) // "p"

    },
    "ProfileManager\0updated\0\0updatedProfileSetting\0"
    "updatedProfileList\0updatedSelection\0"
    "Profile*\0p"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ProfileManager[] = {

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
       1,    0,   34,    2, 0x06 /* Public */,
       3,    0,   35,    2, 0x06 /* Public */,
       4,    0,   36,    2, 0x06 /* Public */,
       5,    1,   37,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6,    7,

       0        // eod
};

void ProfileManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ProfileManager *_t = static_cast<ProfileManager *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->updated(); break;
        case 1: _t->updatedProfileSetting(); break;
        case 2: _t->updatedProfileList(); break;
        case 3: _t->updatedSelection((*reinterpret_cast< Profile*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< Profile* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ProfileManager::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ProfileManager::updated)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (ProfileManager::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ProfileManager::updatedProfileSetting)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (ProfileManager::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ProfileManager::updatedProfileList)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (ProfileManager::*_t)(Profile * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ProfileManager::updatedSelection)) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject ProfileManager::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ProfileManager.data,
      qt_meta_data_ProfileManager,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ProfileManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ProfileManager::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ProfileManager.stringdata0))
        return static_cast<void*>(const_cast< ProfileManager*>(this));
    return QObject::qt_metacast(_clname);
}

int ProfileManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void ProfileManager::updated()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void ProfileManager::updatedProfileSetting()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void ProfileManager::updatedProfileList()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}

// SIGNAL 3
void ProfileManager::updatedSelection(Profile * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE
