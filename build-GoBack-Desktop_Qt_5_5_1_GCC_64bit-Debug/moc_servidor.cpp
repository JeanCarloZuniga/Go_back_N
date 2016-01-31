/****************************************************************************
** Meta object code from reading C++ file 'servidor.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../servidor.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'servidor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Servidor_t {
    QByteArrayData data[8];
    char stringdata0[124];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Servidor_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Servidor_t qt_meta_stringdata_Servidor = {
    {
QT_MOC_LITERAL(0, 0, 8), // "Servidor"
QT_MOC_LITERAL(1, 9, 15), // "buscar_conexion"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 29), // "buscar_conexion_intermediario"
QT_MOC_LITERAL(4, 56, 7), // "recibir"
QT_MOC_LITERAL(5, 64, 21), // "recibir_intermediario"
QT_MOC_LITERAL(6, 86, 22), // "obtener_ultima_lectura"
QT_MOC_LITERAL(7, 109, 14) // "lecturas_vacia"

    },
    "Servidor\0buscar_conexion\0\0"
    "buscar_conexion_intermediario\0recibir\0"
    "recibir_intermediario\0obtener_ultima_lectura\0"
    "lecturas_vacia"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Servidor[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x0a /* Public */,
       3,    0,   45,    2, 0x0a /* Public */,
       4,    0,   46,    2, 0x0a /* Public */,
       5,    0,   47,    2, 0x0a /* Public */,
       6,    0,   48,    2, 0x0a /* Public */,
       7,    0,   49,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::QByteArray,
    QMetaType::Bool,

       0        // eod
};

void Servidor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Servidor *_t = static_cast<Servidor *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->buscar_conexion(); break;
        case 1: _t->buscar_conexion_intermediario(); break;
        case 2: _t->recibir(); break;
        case 3: _t->recibir_intermediario(); break;
        case 4: { QByteArray _r = _t->obtener_ultima_lectura();
            if (_a[0]) *reinterpret_cast< QByteArray*>(_a[0]) = _r; }  break;
        case 5: { bool _r = _t->lecturas_vacia();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObject Servidor::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_Servidor.data,
      qt_meta_data_Servidor,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Servidor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Servidor::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Servidor.stringdata0))
        return static_cast<void*>(const_cast< Servidor*>(this));
    return QThread::qt_metacast(_clname);
}

int Servidor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
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
QT_END_MOC_NAMESPACE
