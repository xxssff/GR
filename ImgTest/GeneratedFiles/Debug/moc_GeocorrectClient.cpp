/****************************************************************************
** Meta object code from reading C++ file 'GeocorrectClient.h'
**
** Created: Thu Oct 23 13:37:23 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../GeocorrectClient.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GeocorrectClient.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_GeocorrectClient[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      45,   18,   17,   17, 0x0a,
     109,   85,   17,   17, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_GeocorrectClient[] = {
    "GeocorrectClient\0\0srcFile,refFile,resultFile\0"
    "handleFilePath(QString,QString,QString)\0"
    "srcImg,refImg,resultImg\0"
    "correct(GDALDataset*,GDALDataset*,GDALDataset*)\0"
};

void GeocorrectClient::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        GeocorrectClient *_t = static_cast<GeocorrectClient *>(_o);
        switch (_id) {
        case 0: _t->handleFilePath((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 1: _t->correct((*reinterpret_cast< GDALDataset*(*)>(_a[1])),(*reinterpret_cast< GDALDataset*(*)>(_a[2])),(*reinterpret_cast< GDALDataset*(*)>(_a[3]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData GeocorrectClient::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject GeocorrectClient::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_GeocorrectClient,
      qt_meta_data_GeocorrectClient, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &GeocorrectClient::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *GeocorrectClient::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *GeocorrectClient::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GeocorrectClient))
        return static_cast<void*>(const_cast< GeocorrectClient*>(this));
    return QObject::qt_metacast(_clname);
}

int GeocorrectClient::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
