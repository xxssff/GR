/****************************************************************************
** Meta object code from reading C++ file 'SvmClasssificationDialog.h'
**
** Created: Fri May 8 22:43:20 2015
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../SvmClasssificationDialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SvmClasssificationDialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SvmClasssificationDialog[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      26,   25,   25,   25, 0x0a,
      42,   25,   25,   25, 0x0a,
      60,   25,   25,   25, 0x0a,
      77,   25,   25,   25, 0x0a,
      87,   25,   25,   25, 0x0a,
      96,   25,   25,   25, 0x0a,
     117,   25,   25,   25, 0x0a,
     139,  135,   25,   25, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_SvmClasssificationDialog[] = {
    "SvmClasssificationDialog\0\0BrowseRoiFile()\0"
    "BrowseModelFile()\0BrowseDestFile()\0"
    "Execute()\0Cancel()\0SetSaveModelEnable()\0"
    "BrowseSaveModel()\0map\0SetMap(MapCanvas*)\0"
};

void SvmClasssificationDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        SvmClasssificationDialog *_t = static_cast<SvmClasssificationDialog *>(_o);
        switch (_id) {
        case 0: _t->BrowseRoiFile(); break;
        case 1: _t->BrowseModelFile(); break;
        case 2: _t->BrowseDestFile(); break;
        case 3: _t->Execute(); break;
        case 4: _t->Cancel(); break;
        case 5: _t->SetSaveModelEnable(); break;
        case 6: _t->BrowseSaveModel(); break;
        case 7: _t->SetMap((*reinterpret_cast< MapCanvas*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData SvmClasssificationDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject SvmClasssificationDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_SvmClasssificationDialog,
      qt_meta_data_SvmClasssificationDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SvmClasssificationDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SvmClasssificationDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SvmClasssificationDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SvmClasssificationDialog))
        return static_cast<void*>(const_cast< SvmClasssificationDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int SvmClasssificationDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
