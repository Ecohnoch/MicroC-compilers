/****************************************************************************
** Meta object code from reading C++ file 'transfer.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../compilers/myCompiler/transfer.h"
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
    QByteArrayData data[21];
    char stringdata0[251];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_transfer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_transfer_t qt_meta_stringdata_transfer = {
    {
QT_MOC_LITERAL(0, 0, 8), // "transfer"
QT_MOC_LITERAL(1, 9, 8), // "doTokens"
QT_MOC_LITERAL(2, 18, 0), // ""
QT_MOC_LITERAL(3, 19, 8), // "doParser"
QT_MOC_LITERAL(4, 28, 13), // "doSimbolTable"
QT_MOC_LITERAL(5, 42, 10), // "doAnalyser"
QT_MOC_LITERAL(6, 53, 13), // "getSourcecode"
QT_MOC_LITERAL(7, 67, 10), // "sourcecode"
QT_MOC_LITERAL(8, 78, 9), // "getTokens"
QT_MOC_LITERAL(9, 88, 24), // "vector<Tokenizer::Token>"
QT_MOC_LITERAL(10, 113, 14), // "getAnalyzerAns"
QT_MOC_LITERAL(11, 128, 24), // "vector<Analyzer::Output>"
QT_MOC_LITERAL(12, 153, 13), // "getParserTree"
QT_MOC_LITERAL(13, 167, 17), // "Parser::TreeNode*"
QT_MOC_LITERAL(14, 185, 9), // "recursion"
QT_MOC_LITERAL(15, 195, 7), // "string&"
QT_MOC_LITERAL(16, 203, 1), // "s"
QT_MOC_LITERAL(17, 205, 12), // "parserToJSON"
QT_MOC_LITERAL(18, 218, 12), // "tokensToJSON"
QT_MOC_LITERAL(19, 231, 14), // "analyzerToJSON"
QT_MOC_LITERAL(20, 246, 4) // "test"

    },
    "transfer\0doTokens\0\0doParser\0doSimbolTable\0"
    "doAnalyser\0getSourcecode\0sourcecode\0"
    "getTokens\0vector<Tokenizer::Token>\0"
    "getAnalyzerAns\0vector<Analyzer::Output>\0"
    "getParserTree\0Parser::TreeNode*\0"
    "recursion\0string&\0s\0parserToJSON\0"
    "tokensToJSON\0analyzerToJSON\0test"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_transfer[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   79,    2, 0x06 /* Public */,
       3,    0,   80,    2, 0x06 /* Public */,
       4,    0,   81,    2, 0x06 /* Public */,
       5,    0,   82,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    1,   83,    2, 0x0a /* Public */,
       8,    1,   86,    2, 0x0a /* Public */,
      10,    1,   89,    2, 0x0a /* Public */,
      12,    1,   92,    2, 0x0a /* Public */,
      14,    2,   95,    2, 0x0a /* Public */,
      17,    1,  100,    2, 0x0a /* Public */,
      18,    1,  103,    2, 0x0a /* Public */,
      19,    1,  106,    2, 0x0a /* Public */,
      20,    0,  109,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    7,
    0x80000000 | 9, QMetaType::QString,    7,
    0x80000000 | 11, QMetaType::QString,    7,
    0x80000000 | 13, QMetaType::QString,    7,
    QMetaType::Void, 0x80000000 | 13, 0x80000000 | 15,    2,   16,
    QMetaType::QString, QMetaType::QString,    7,
    QMetaType::QString, QMetaType::QString,    7,
    QMetaType::QString, QMetaType::QString,    7,
    QMetaType::Void,

       0        // eod
};

void transfer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        transfer *_t = static_cast<transfer *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->doTokens(); break;
        case 1: _t->doParser(); break;
        case 2: _t->doSimbolTable(); break;
        case 3: _t->doAnalyser(); break;
        case 4: _t->getSourcecode((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: { vector<Tokenizer::Token> _r = _t->getTokens((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< vector<Tokenizer::Token>*>(_a[0]) = _r; }  break;
        case 6: { vector<Analyzer::Output> _r = _t->getAnalyzerAns((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< vector<Analyzer::Output>*>(_a[0]) = _r; }  break;
        case 7: { Parser::TreeNode* _r = _t->getParserTree((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< Parser::TreeNode**>(_a[0]) = _r; }  break;
        case 8: _t->recursion((*reinterpret_cast< Parser::TreeNode*(*)>(_a[1])),(*reinterpret_cast< string(*)>(_a[2]))); break;
        case 9: { QString _r = _t->parserToJSON((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 10: { QString _r = _t->tokensToJSON((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 11: { QString _r = _t->analyzerToJSON((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 12: _t->test(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (transfer::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&transfer::doTokens)) {
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
        {
            typedef void (transfer::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&transfer::doSimbolTable)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (transfer::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&transfer::doAnalyser)) {
                *result = 3;
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
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void transfer::doTokens()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void transfer::doParser()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void transfer::doSimbolTable()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}

// SIGNAL 3
void transfer::doAnalyser()
{
    QMetaObject::activate(this, &staticMetaObject, 3, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
