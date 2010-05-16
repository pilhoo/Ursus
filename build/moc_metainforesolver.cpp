/****************************************************************************
** Meta object code from reading C++ file 'metainforesolver.h'
**
** Created: Sat May 15 19:51:55 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../metainforesolver.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'metainforesolver.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MetaInfoResolver[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      18,   17,   17,   17, 0x05,

 // slots: signature, parameters, type, tag, flags
      44,   39,   17,   17, 0x0a,
      77,   67,   17,   17, 0x0a,
     120,   17,   17,   17, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MetaInfoResolver[] = {
    "MetaInfoResolver\0\0readyToResolveNext()\0"
    "item\0Enqueue(PlayListItem*)\0newState,\0"
    "infoResolving(Phonon::State,Phonon::State)\0"
    "resolveNextItem()\0"
};

const QMetaObject MetaInfoResolver::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_MetaInfoResolver,
      qt_meta_data_MetaInfoResolver, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MetaInfoResolver::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MetaInfoResolver::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MetaInfoResolver::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MetaInfoResolver))
        return static_cast<void*>(const_cast< MetaInfoResolver*>(this));
    return QObject::qt_metacast(_clname);
}

int MetaInfoResolver::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: readyToResolveNext(); break;
        case 1: Enqueue((*reinterpret_cast< PlayListItem*(*)>(_a[1]))); break;
        case 2: infoResolving((*reinterpret_cast< Phonon::State(*)>(_a[1])),(*reinterpret_cast< Phonon::State(*)>(_a[2]))); break;
        case 3: resolveNextItem(); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void MetaInfoResolver::readyToResolveNext()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
