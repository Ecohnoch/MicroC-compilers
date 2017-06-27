/****************************************************************************
** Meta object code from reading C++ file 'transfer.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../myCompiler/transfer.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'transfer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_transfer_t {
    QByteArrayData data[9];
    char stringdata0[97];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_transfer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_transfer_t qt_meta_stringdata_transfer = {
    {
QT_MOC_LITERAL(0, 0, 8), // "transfer"
QT_MOC_LITERAL(1, 9, 12), // "doReadTokens"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 8), // "doParser"
QT_MOC_LITERAL(4, 32, 13), // "getSourcecode"
QT_MOC_LITERAL(5, 46, 10), // "sourcecode"
QT_MOC_LITERAL(6, 57, 13), // "getParserFlow"
QT_MOC_LITERAL(7, 71, 12), // "parserToJSON"
QT_MOC_LITERAL(8, 84, 12) // "tokensToJSON"

    },
    "transfer\0doReadTokens\0\0doParser\0"
    "getSourcecode\0sourcecode\0getParserFlow\0"
    "parserToJSON\0tokensToJSON"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_transfer[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x06 /* Public */,
       3,    0,   45,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   46,    2, 0x0a /* Public */,
       6,    0,   49,    2, 0x0a /* Public */,
       7,    0,   50,    2, 0x0a /* Public */,
       8,    0,   51,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void,
    QMetaType::QString,
    QMetaType::QString,

       0        // eod
};

void transfer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        transfer *_t = static_cast<transfer *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->doReadTokens(); break;
        case 1: _t->doParser(); break;
        case 2: _t->getSourcecode((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->getParserFlow(); break;
        case 4: { QString _r = _t->parserToJSON();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 5: { QString _r = _t->tokensToJSON();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (transfer::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&transfer::doReadTokens)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (transfer::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&transfer::doParser)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject transfer::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_transfer.data,
      qt_meta_data_transfer,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *transfer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *transfer::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_transfer.stringdata0))
        return static_cast<void*>(const_cast< transfer*>(this));
    return QObject::qt_metacast(_clname);
}

int transfer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void transfer::doReadTokens()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void transfer::doParser()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
