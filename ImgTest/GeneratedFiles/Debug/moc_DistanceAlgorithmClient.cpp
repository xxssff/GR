/****************************************************************************
** Meta object code from reading C++ file 'DistanceAlgorithmClient.h'
**
** Created: Sat Jul 19 15:19:30 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../DistanceAlgorithmClient.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'DistanceAlgorithmClient.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DistanceAlgorithmClient[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      35,   25,   24,   24, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_DistanceAlgorithmClient[] = {
    "DistanceAlgorithmClient\0\0poDataset\0"
    "RunDisAlg(GDALDataset*)\0"
};

void DistanceAlgorithmClient::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        DistanceAlgorithmClient *_t = static_cast<DistanceAlgorithmClient *>(_o);
        switch (_id) {
        case 0: _t->RunDisAlg((*reinterpret_cast< GDALDataset*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData DistanceAlgorithmClient::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject DistanceAlgorithmClient::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_DistanceAlgorithmClient,
      qt_meta_data_DistanceAlgorithmClient, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DistanceAlgorithmClient::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DistanceAlgorithmClient::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DistanceAlgorithmClient::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DistanceAlgorithmClient))
        return static_cast<void*>(const_cast< DistanceAlgorithmClient*>(this));
    return QObject::qt_metacast(_clname);
}

int DistanceAlgorithmClient::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
