/****************************************************************************
** Meta object code from reading C++ file 'GRInterface.h'
**
** Created: Fri May 8 22:43:20 2015
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../GRInterface.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GRInterface.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_GRInterface[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x0a,
      24,   12,   12,   12, 0x0a,
      39,   12,   12,   12, 0x0a,
      61,   12,   57,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_GRInterface[] = {
    "GRInterface\0\0zoomFull()\0zoomPrevious()\0"
    "zoomActiveLayer()\0int\0getInt()\0"
};

void GRInterface::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        GRInterface *_t = static_cast<GRInterface *>(_o);
        switch (_id) {
        case 0: _t->zoomFull(); break;
        case 1: _t->zoomPrevious(); break;
        case 2: _t->zoomActiveLayer(); break;
        case 3: { int _r = _t->getInt();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObjectExtraData GRInterface::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject GRInterface::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_GRInterface,
      qt_meta_data_GRInterface, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &GRInterface::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *GRInterface::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *GRInterface::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GRInterface))
        return static_cast<void*>(const_cast< GRInterface*>(this));
    return QWidget::qt_metacast(_clname);
}

int GRInterface::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
