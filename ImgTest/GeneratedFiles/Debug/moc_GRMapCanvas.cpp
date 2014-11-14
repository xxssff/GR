/****************************************************************************
** Meta object code from reading C++ file 'GRMapCanvas.h'
**
** Created: Fri Nov 14 13:30:05 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../GRMapCanvas.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GRMapCanvas.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_GRMapCanvas[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      15,   13,   12,   12, 0x05,

 // slots: signature, parameters, type, tag, flags
      39,   12,   12,   12, 0x0a,
      49,   12,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_GRMapCanvas[] = {
    "GRMapCanvas\0\0p\0xyCoordinates(GRPoint&)\0"
    "render2()\0layerStateChange()\0"
};

void GRMapCanvas::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        GRMapCanvas *_t = static_cast<GRMapCanvas *>(_o);
        switch (_id) {
        case 0: _t->xyCoordinates((*reinterpret_cast< GRPoint(*)>(_a[1]))); break;
        case 1: _t->render2(); break;
        case 2: _t->layerStateChange(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData GRMapCanvas::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject GRMapCanvas::staticMetaObject = {
    { &QGraphicsView::staticMetaObject, qt_meta_stringdata_GRMapCanvas,
      qt_meta_data_GRMapCanvas, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &GRMapCanvas::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *GRMapCanvas::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *GRMapCanvas::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GRMapCanvas))
        return static_cast<void*>(const_cast< GRMapCanvas*>(this));
    return QGraphicsView::qt_metacast(_clname);
}

int GRMapCanvas::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void GRMapCanvas::xyCoordinates(GRPoint & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
