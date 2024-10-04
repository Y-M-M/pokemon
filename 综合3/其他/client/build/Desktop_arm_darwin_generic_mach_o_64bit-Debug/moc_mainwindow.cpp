/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../mainwindow.h"
#include <QtNetwork/QSslPreSharedKeyAuthenticator>
#include <QtNetwork/QSslError>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSMainWindowENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSMainWindowENDCLASS = QtMocHelpers::stringData(
    "MainWindow",
    "sentSelect",
    "",
    "QList<UDPPokemon*>",
    "pkmList",
    "uint*",
    "pkmIndex",
    "readPendingDatagrams",
    "recvSelectResult",
    "index",
    "Loginout_clicked",
    "Online_clicked",
    "Allusers_clicked",
    "Users_changed",
    "currentRow",
    "Upgrade_botton_clicked",
    "Duel_botton_clicked",
    "CbxUser_Changed",
    "Combox_Changed",
    "BtnConfirm_clicked",
    "BtnRate_clicked",
    "BtnBadge_clicked",
    "checked"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSMainWindowENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    2,   98,    2, 0x06,    1 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       7,    0,  103,    2, 0x08,    4 /* Private */,
       8,    1,  104,    2, 0x08,    5 /* Private */,
      10,    0,  107,    2, 0x08,    7 /* Private */,
      11,    0,  108,    2, 0x08,    8 /* Private */,
      12,    0,  109,    2, 0x08,    9 /* Private */,
      13,    1,  110,    2, 0x08,   10 /* Private */,
      15,    0,  113,    2, 0x08,   12 /* Private */,
      16,    0,  114,    2, 0x08,   13 /* Private */,
      17,    1,  115,    2, 0x08,   14 /* Private */,
      18,    1,  118,    2, 0x08,   16 /* Private */,
      19,    0,  121,    2, 0x08,   18 /* Private */,
      20,    0,  122,    2, 0x08,   19 /* Private */,
      21,    1,  123,    2, 0x08,   20 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 5,    4,    6,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::UInt,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   14,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   22,

       0        // eod
};

Q_CONSTINIT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_CLASSMainWindowENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSMainWindowENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSMainWindowENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<MainWindow, std::true_type>,
        // method 'sentSelect'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QList<UDPPokemon*>, std::false_type>,
        QtPrivate::TypeAndForceComplete<uint *, std::false_type>,
        // method 'readPendingDatagrams'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'recvSelectResult'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<uint, std::false_type>,
        // method 'Loginout_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'Online_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'Allusers_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'Users_changed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'Upgrade_botton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'Duel_botton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'CbxUser_Changed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'Combox_Changed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'BtnConfirm_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'BtnRate_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'BtnBadge_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>
    >,
    nullptr
} };

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->sentSelect((*reinterpret_cast< std::add_pointer_t<QList<UDPPokemon*>>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<uint*>>(_a[2]))); break;
        case 1: _t->readPendingDatagrams(); break;
        case 2: _t->recvSelectResult((*reinterpret_cast< std::add_pointer_t<uint>>(_a[1]))); break;
        case 3: _t->Loginout_clicked(); break;
        case 4: _t->Online_clicked(); break;
        case 5: _t->Allusers_clicked(); break;
        case 6: _t->Users_changed((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 7: _t->Upgrade_botton_clicked(); break;
        case 8: _t->Duel_botton_clicked(); break;
        case 9: _t->CbxUser_Changed((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 10: _t->Combox_Changed((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 11: _t->BtnConfirm_clicked(); break;
        case 12: _t->BtnRate_clicked(); break;
        case 13: _t->BtnBadge_clicked((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MainWindow::*)(QList<UDPPokemon*> , uint * );
            if (_t _q_method = &MainWindow::sentSelect; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSMainWindowENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 14;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::sentSelect(QList<UDPPokemon*> _t1, uint * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
