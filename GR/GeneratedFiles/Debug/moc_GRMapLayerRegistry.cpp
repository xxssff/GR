/****************************************************************************
** Meta object code from reading C++ file 'GRMapLayerRegistry.h'
**
** Created: Fri May 8 22:43:19 2015
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../GRMapLayerRegistry.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GRMapLayerRegistry.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_GRMapLayerRegistry[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: signature, parameters, type, tag, flags
      32,   20,   19,   19, 0x05,
      76,   65,   19,   19, 0x05,
     104,   19,   19,   19, 0x05,
     129,  116,   19,   19, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_GRMapLayerRegistry[] = {
    "GRMapLayerRegistry\0\0theLayerIds\0"
    "layersWillBeRemoved(QStringList)\0"
    "theLayerId\0layerWillBeRemoved(QString)\0"
    "removeAll()\0theMapLayers\0"
    "layersAdded(QList<GRMapLayer*>)\0"
};

void GRMapLayerRegistry::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        GRMapLayerRegistry *_t = static_cast<GRMapLayerRegistry *>(_o);
        switch (_id) {
        case 0: _t->layersWillBeRemoved((*reinterpret_cast< QStringList(*)>(_a[1]))); break;
        case 1: _t->layerWillBeRemoved((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->removeAll(); break;
        case 3: _t->layersAdded((*reinterpret_cast< QList<GRMapLayer*>(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData GRMapLayerRegistry::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject GRMapLayerRegistry::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_GRMapLayerRegistry,
      qt_meta_data_GRMapLayerRegistry, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &GRMapLayerRegistry::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *GRMapLayerRegistry::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *GRMapLayerRegistry::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GRMapLayerRegistry))
        return static_cast<void*>(const_cast< GRMapLayerRegistry*>(this));
    return QObject::qt_metacast(_clname);
}

int GRMapLayerRegistry::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void GRMapLayerRegistry::layersWillBeRemoved(QStringList _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void GRMapLayerRegistry::layerWillBeRemoved(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void GRMapLayerRegistry::removeAll()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void GRMapLayerRegistry::layersAdded(QList<GRMapLayer*> _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE
