/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[27];
    char stringdata0[342];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 11), // "playClicked"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 22), // "playSubActionTriggered"
QT_MOC_LITERAL(4, 47, 30), // "showPasswordGeneratorTriggered"
QT_MOC_LITERAL(5, 78, 18), // "cmbSelectedProfile"
QT_MOC_LITERAL(6, 97, 5), // "index"
QT_MOC_LITERAL(7, 103, 15), // "profileSelected"
QT_MOC_LITERAL(8, 119, 8), // "Profile*"
QT_MOC_LITERAL(9, 128, 1), // "p"
QT_MOC_LITERAL(10, 130, 15), // "profilesUpdated"
QT_MOC_LITERAL(11, 146, 18), // "updateLauncherInfo"
QT_MOC_LITERAL(12, 165, 11), // "gameRunning"
QT_MOC_LITERAL(13, 177, 7), // "running"
QT_MOC_LITERAL(14, 185, 7), // "gameLog"
QT_MOC_LITERAL(15, 193, 13), // "Logger::Entry"
QT_MOC_LITERAL(16, 207, 5), // "entry"
QT_MOC_LITERAL(17, 213, 12), // "gameProgress"
QT_MOC_LITERAL(18, 226, 7), // "enabled"
QT_MOC_LITERAL(19, 234, 4), // "_min"
QT_MOC_LITERAL(20, 239, 4), // "_max"
QT_MOC_LITERAL(21, 244, 6), // "_value"
QT_MOC_LITERAL(22, 251, 15), // "stopGameClicked"
QT_MOC_LITERAL(23, 267, 15), // "closeLogClicked"
QT_MOC_LITERAL(24, 283, 23), // "openApplicationSettings"
QT_MOC_LITERAL(25, 307, 14), // "openProfileLog"
QT_MOC_LITERAL(26, 322, 19) // "profilesInitialized"

    },
    "MainWindow\0playClicked\0\0playSubActionTriggered\0"
    "showPasswordGeneratorTriggered\0"
    "cmbSelectedProfile\0index\0profileSelected\0"
    "Profile*\0p\0profilesUpdated\0"
    "updateLauncherInfo\0gameRunning\0running\0"
    "gameLog\0Logger::Entry\0entry\0gameProgress\0"
    "enabled\0_min\0_max\0_value\0stopGameClicked\0"
    "closeLogClicked\0openApplicationSettings\0"
    "openProfileLog\0profilesInitialized"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   89,    2, 0x08 /* Private */,
       3,    0,   90,    2, 0x08 /* Private */,
       4,    0,   91,    2, 0x08 /* Private */,
       5,    1,   92,    2, 0x08 /* Private */,
       7,    1,   95,    2, 0x08 /* Private */,
      10,    0,   98,    2, 0x08 /* Private */,
      11,    0,   99,    2, 0x08 /* Private */,
      12,    1,  100,    2, 0x08 /* Private */,
      14,    1,  103,    2, 0x08 /* Private */,
      17,    4,  106,    2, 0x08 /* Private */,
      22,    0,  115,    2, 0x08 /* Private */,
      23,    0,  116,    2, 0x08 /* Private */,
      24,    0,  117,    2, 0x08 /* Private */,
      25,    0,  118,    2, 0x08 /* Private */,
      26,    0,  119,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   13,
    QMetaType::Void, 0x80000000 | 15,   16,
    QMetaType::Void, QMetaType::Bool, QMetaType::Int, QMetaType::Int, QMetaType::Int,   18,   19,   20,   21,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->playClicked(); break;
        case 1: _t->playSubActionTriggered(); break;
        case 2: _t->showPasswordGeneratorTriggered(); break;
        case 3: _t->cmbSelectedProfile((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->profileSelected((*reinterpret_cast< Profile*(*)>(_a[1]))); break;
        case 5: _t->profilesUpdated(); break;
        case 6: _t->updateLauncherInfo(); break;
        case 7: _t->gameRunning((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->gameLog((*reinterpret_cast< const Logger::Entry(*)>(_a[1]))); break;
        case 9: _t->gameProgress((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 10: _t->stopGameClicked(); break;
        case 11: _t->closeLogClicked(); break;
        case 12: _t->openApplicationSettings(); break;
        case 13: _t->openProfileLog(); break;
        case 14: _t->profilesInitialized(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< Profile* >(); break;
            }
            break;
        case 8:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< Logger::Entry >(); break;
            }
            break;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
