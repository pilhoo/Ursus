/****************************************************************************
** Meta object code from reading C++ file 'playlisttabbar.h'
**
** Created: Sat May 15 19:51:55 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../playlisttabbar.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'playlisttabbar.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_PlayListTabBar[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      16,   15,   15,   15, 0x05,
      30,   15,   15,   15, 0x05,
      51,   15,   15,   15, 0x05,

 // slots: signature, parameters, type, tag, flags
      72,   15,   15,   15, 0x08,
      87,   15,   15,   15, 0x08,
     102,   15,   15,   15, 0x08,
     118,   15,   15,   15, 0x08,
     140,  134,   15,   15, 0x08,
     160,   15,   15,   15, 0x08,
     178,   15,   15,   15, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_PlayListTabBar[] = {
    "PlayListTabBar\0\0newPlayList()\0"
    "closePlayListNr(int)\0clearPlayListNr(int)\0"
    "openPlayList()\0savePlayList()\0"
    "clearPlayList()\0closePlayList()\0point\0"
    "contextMenu(QPoint)\0setPlayListName()\0"
    "renamePlayList()\0"
};

const QMetaObject PlayListTabBar::staticMetaObject = {
    { &QTabBar::staticMetaObject, qt_meta_stringdata_PlayListTabBar,
      qt_meta_data_PlayListTabBar, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &PlayListTabBar::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *PlayListTabBar::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *PlayListTabBar::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PlayListTabBar))
        return static_cast<void*>(const_cast< PlayListTabBar*>(this));
    return QTabBar::qt_metacast(_clname);
}

int PlayListTabBar::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTabBar::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: newPlayList(); break;
        case 1: closePlayListNr((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: clearPlayListNr((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: openPlayList(); break;
        case 4: savePlayList(); break;
        case 5: clearPlayList(); break;
        case 6: closePlayList(); break;
        case 7: contextMenu((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 8: setPlayListName(); break;
        case 9: renamePlayList(); break;
        default: ;
        }
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void PlayListTabBar::newPlayList()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void PlayListTabBar::closePlayListNr(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void PlayListTabBar::clearPlayListNr(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
