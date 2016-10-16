/****************************************************************************
** Meta object code from reading C++ file 'logger.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/logger.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'logger.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Logger_t {
    QByteArrayData data[7];
    char stringdata0[50];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Logger_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Logger_t qt_meta_stringdata_Logger = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Logger"
QT_MOC_LITERAL(1, 7, 6), // "logged"
QT_MOC_LITERAL(2, 14, 0), // ""
QT_MOC_LITERAL(3, 15, 5), // "Entry"
QT_MOC_LITERAL(4, 21, 5), // "entry"
QT_MOC_LITERAL(5, 27, 14), // "loggedAsString"
QT_MOC_LITERAL(6, 42, 7) // "message"

    },
    "Logger\0logged\0\0Entry\0entry\0loggedAsString\0"
    "message"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Logger[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   24,    2, 0x06 /* Public */,
       5,    1,   27,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::QString,    6,

       0        // eod
};

void Logger::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Logger *_t = static_cast<Logger *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->logged((*reinterpret_cast< const Entry(*)>(_a[1]))); break;
        case 1: _t->loggedAsString((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Logger::*_t)(const Entry & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Logger::logged)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (Logger::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Logger::loggedAsString)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject Logger::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Logger.data,
      qt_meta_data_Logger,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Logger::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Logger::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Logger.stringdata0))
        return static_cast<void*>(const_cast< Logger*>(this));
    return QObject::qt_metacast(_clname);
}

int Logger::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void Logger::logged(const Entry & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Logger::loggedAsString(const QString & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
