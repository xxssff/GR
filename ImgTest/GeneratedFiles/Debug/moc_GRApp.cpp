/****************************************************************************
** Meta object code from reading C++ file 'GRApp.h'
**
** Created: Mon Oct 20 16:43:54 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../GRApp.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GRApp.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_GRApp[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      20,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      13,    7,    6,    6, 0x08,
      52,   43,    6,    6, 0x08,
      84,    6,    6,    6, 0x08,
     102,   43,    6,    6, 0x08,
     139,    6,    6,    6, 0x08,
     153,    6,    6,    6, 0x08,
     173,    6,    6,    6, 0x08,
     195,    6,    6,    6, 0x08,
     227,    6,    6,    6, 0x08,
     245,    6,    6,    6, 0x08,
     266,    6,    6,    6, 0x08,
     277,    6,    6,    6, 0x08,
     290,    6,    6,    6, 0x08,
     301,    6,    6,    6, 0x08,
     311,    6,    6,    6, 0x08,
     318,    6,    6,    6, 0x08,
     335,    6,    6,    6, 0x08,
     353,    6,    6,    6, 0x08,
     378,    6,    6,    6, 0x08,
     398,  396,    6,    6, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_GRApp[] = {
    "GRApp\0\0point\0showMouseCoordinate(GRPoint&)\0"
    "viewItem\0layerProperties(QListViewItem*)\0"
    "layerProperties()\0"
    "rightClickLegendMenu(QListViewItem*)\0"
    "removeLayer()\0zoomToLayerExtent()\0"
    "testPluginFunctions()\0"
    "actionPluginManager_activated()\0"
    "saveWindowState()\0restoreWindowState()\0"
    "fileSave()\0fileSaveAs()\0fileOpen()\0"
    "fileNew()\0exit()\0checkGrVersion()\0"
    "socketConnected()\0socketConnectionClosed()\0"
    "socketReadyRead()\0e\0socketError(int)\0"
};

void GRApp::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        GRApp *_t = static_cast<GRApp *>(_o);
        switch (_id) {
        case 0: _t->showMouseCoordinate((*reinterpret_cast< GRPoint(*)>(_a[1]))); break;
        case 1: _t->layerProperties((*reinterpret_cast< QListViewItem*(*)>(_a[1]))); break;
        case 2: _t->layerProperties(); break;
        case 3: _t->rightClickLegendMenu((*reinterpret_cast< QListViewItem*(*)>(_a[1]))); break;
        case 4: _t->removeLayer(); break;
        case 5: _t->zoomToLayerExtent(); break;
        case 6: _t->testPluginFunctions(); break;
        case 7: _t->actionPluginManager_activated(); break;
        case 8: _t->saveWindowState(); break;
        case 9: _t->restoreWindowState(); break;
        case 10: _t->fileSave(); break;
        case 11: _t->fileSaveAs(); break;
        case 12: _t->fileOpen(); break;
        case 13: _t->fileNew(); break;
        case 14: _t->exit(); break;
        case 15: _t->checkGrVersion(); break;
        case 16: _t->socketConnected(); break;
        case 17: _t->socketConnectionClosed(); break;
        case 18: _t->socketReadyRead(); break;
        case 19: _t->socketError((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData GRApp::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject GRApp::staticMetaObject = {
    { &GRAppBase::staticMetaObject, qt_meta_stringdata_GRApp,
      qt_meta_data_GRApp, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &GRApp::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *GRApp::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *GRApp::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GRApp))
        return static_cast<void*>(const_cast< GRApp*>(this));
    return GRAppBase::qt_metacast(_clname);
}

int GRApp::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = GRAppBase::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 20)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 20;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
