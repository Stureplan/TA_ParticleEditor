/****************************************************************************
** Meta object code from reading C++ file 'maincontainer.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../maincontainer.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'maincontainer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainContainer_t {
    QByteArrayData data[15];
    char stringdata0[162];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainContainer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainContainer_t qt_meta_stringdata_MainContainer = {
    {
QT_MOC_LITERAL(0, 0, 13), // "MainContainer"
QT_MOC_LITERAL(1, 14, 11), // "setLifetime"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 16), // "setEmissionDelay"
QT_MOC_LITERAL(4, 44, 12), // "setVelocityX"
QT_MOC_LITERAL(5, 57, 12), // "setVelocityY"
QT_MOC_LITERAL(6, 70, 12), // "setVelocityZ"
QT_MOC_LITERAL(7, 83, 15), // "setMaxParticles"
QT_MOC_LITERAL(8, 99, 10), // "setGravity"
QT_MOC_LITERAL(9, 110, 6), // "browse"
QT_MOC_LITERAL(10, 117, 4), // "save"
QT_MOC_LITERAL(11, 122, 7), // "colorIn"
QT_MOC_LITERAL(12, 130, 8), // "colorOut"
QT_MOC_LITERAL(13, 139, 16), // "scaleModeChanged"
QT_MOC_LITERAL(14, 156, 5) // "index"

    },
    "MainContainer\0setLifetime\0\0setEmissionDelay\0"
    "setVelocityX\0setVelocityY\0setVelocityZ\0"
    "setMaxParticles\0setGravity\0browse\0"
    "save\0colorIn\0colorOut\0scaleModeChanged\0"
    "index"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainContainer[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   74,    2, 0x0a /* Public */,
       3,    0,   75,    2, 0x0a /* Public */,
       4,    0,   76,    2, 0x0a /* Public */,
       5,    0,   77,    2, 0x0a /* Public */,
       6,    0,   78,    2, 0x0a /* Public */,
       7,    0,   79,    2, 0x0a /* Public */,
       8,    0,   80,    2, 0x0a /* Public */,
       9,    0,   81,    2, 0x0a /* Public */,
      10,    0,   82,    2, 0x0a /* Public */,
      11,    0,   83,    2, 0x0a /* Public */,
      12,    0,   84,    2, 0x0a /* Public */,
      13,    1,   85,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   14,

       0        // eod
};

void MainContainer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainContainer *_t = static_cast<MainContainer *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->setLifetime(); break;
        case 1: _t->setEmissionDelay(); break;
        case 2: _t->setVelocityX(); break;
        case 3: _t->setVelocityY(); break;
        case 4: _t->setVelocityZ(); break;
        case 5: _t->setMaxParticles(); break;
        case 6: _t->setGravity(); break;
        case 7: _t->browse(); break;
        case 8: _t->save(); break;
        case 9: _t->colorIn(); break;
        case 10: _t->colorOut(); break;
        case 11: _t->scaleModeChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject MainContainer::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_MainContainer.data,
      qt_meta_data_MainContainer,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *MainContainer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainContainer::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainContainer.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int MainContainer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
