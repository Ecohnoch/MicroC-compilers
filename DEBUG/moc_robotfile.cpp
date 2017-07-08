/****************************************************************************
** Meta object code from reading C++ file 'robotfile.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../compilers/myCompiler/robotfile.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'robotfile.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_RobotFile_t {
    QByteArrayData data[8];
    char stringdata0[54];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_RobotFile_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_RobotFile_t qt_meta_stringdata_RobotFile = {
    {
QT_MOC_LITERAL(0, 0, 9), // "RobotFile"
QT_MOC_LITERAL(1, 10, 8), // "dataPath"
QT_MOC_LITERAL(2, 19, 0), // ""
QT_MOC_LITERAL(3, 20, 4), // "file"
QT_MOC_LITERAL(4, 25, 5), // "exist"
QT_MOC_LITERAL(5, 31, 4), // "path"
QT_MOC_LITERAL(6, 36, 12), // "resourcePath"
QT_MOC_LITERAL(7, 49, 4) // "read"

    },
    "RobotFile\0dataPath\0\0file\0exist\0path\0"
    "resourcePath\0read"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_RobotFile[] = {

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

 // methods: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x02 /* Public */,
       4,    1,   37,    2, 0x02 /* Public */,
       6,    1,   40,    2, 0x02 /* Public */,
       7,    1,   43,    2, 0x02 /* Public */,

 // methods: parameters
    QMetaType::QString, QMetaType::QString,    3,
    QMetaType::Bool, QMetaType::QString,    5,
    QMetaType::QString, QMetaType::QString,    3,
    QMetaType::QString, QMetaType::QString,    5,

       0        // eod
};

void RobotFile::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        RobotFile *_t = static_cast<RobotFile *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: { QString _r = _t->dataPath((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 1: { bool _r = _t->exist((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 2: { QString _r = _t->resourcePath((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 3: { QString _r = _t->read((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObject RobotFile::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_RobotFile.data,
      qt_meta_data_RobotFile,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *RobotFile::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *RobotFile::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_RobotFile.stringdata0))
        return static_cast<void*>(const_cast< RobotFile*>(this));
    return QObject::qt_metacast(_clname);
}

int RobotFile::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
