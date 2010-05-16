/****************************************************************************
** Meta object code from reading C++ file 'playlisttabs.h'
**
** Created: Sat May 15 19:51:54 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../playlisttabs.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'playlisttabs.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_PlayListTabs[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
      25,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: signature, parameters, type, tag, flags
      20,   14,   13,   13, 0x05,
      52,   13,   13,   13, 0x05,
      77,   13,   13,   13, 0x05,
     110,   13,   13,   13, 0x05,
     138,   13,   13,   13, 0x05,
     171,   13,   13,   13, 0x05,

 // slots: signature, parameters, type, tag, flags
     194,   13,   13,   13, 0x0a,
     210,   13,   13,   13, 0x0a,
     226,   13,   13,   13, 0x0a,
     240,   13,   13,   13, 0x0a,
     259,   13,   13,   13, 0x0a,
     278,   13,   13,   13, 0x0a,
     306,  300,   13,   13, 0x0a,
     325,   13,   13,   13, 0x0a,
     347,  300,   13,   13, 0x0a,
     366,   13,   13,   13, 0x0a,
     377,   13,   13,   13, 0x0a,
     394,   13,   13,   13, 0x0a,
     419,  409,   13,   13, 0x0a,
     457,   13,   13,   13, 0x0a,
     481,  476,   13,   13, 0x0a,
     505,   13,   13,   13, 0x0a,
     521,   13,   13,   13, 0x0a,
     541,   13,   13,   13, 0x0a,
     562,  559,   13,   13, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_PlayListTabs[] = {
    "PlayListTabs\0\0shown\0visibleChanged(PlayListWidget*)\0"
    "enableRemoveAction(bool)\0"
    "playSource(Phonon::MediaSource&)\0"
    "trackStringChanged(QString)\0"
    "giveSource(Phonon::MediaSource&)\0"
    "activeItemExists(bool)\0loadPlayLists()\0"
    "savePlayLists()\0newPlayList()\0"
    "openPlayListFile()\0savePlayListFile()\0"
    "clearActivePlayList()\0index\0"
    "clearPlayList(int)\0closeActivePlayList()\0"
    "closePlayList(int)\0addFiles()\0"
    "removeSelected()\0jumpToActive()\0"
    "newState,\0setState(Phonon::State,Phonon::State)\0"
    "selectionChanged()\0item\0playItem(PlayListItem*)\0"
    "getNextSource()\0getPreviousSource()\0"
    "getActualSource()\0nr\0tabChanged(int)\0"
};

const QMetaObject PlayListTabs::staticMetaObject = {
    { &QTabWidget::staticMetaObject, qt_meta_stringdata_PlayListTabs,
      qt_meta_data_PlayListTabs, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &PlayListTabs::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *PlayListTabs::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *PlayListTabs::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PlayListTabs))
        return static_cast<void*>(const_cast< PlayListTabs*>(this));
    return QTabWidget::qt_metacast(_clname);
}

int PlayListTabs::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTabWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: visibleChanged((*reinterpret_cast< PlayListWidget*(*)>(_a[1]))); break;
        case 1: enableRemoveAction((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: playSource((*reinterpret_cast< Phonon::MediaSource(*)>(_a[1]))); break;
        case 3: trackStringChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: giveSource((*reinterpret_cast< Phonon::MediaSource(*)>(_a[1]))); break;
        case 5: activeItemExists((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: loadPlayLists(); break;
        case 7: savePlayLists(); break;
        case 8: newPlayList(); break;
        case 9: openPlayListFile(); break;
        case 10: savePlayListFile(); break;
        case 11: clearActivePlayList(); break;
        case 12: clearPlayList((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: closeActivePlayList(); break;
        case 14: closePlayList((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 15: addFiles(); break;
        case 16: removeSelected(); break;
        case 17: jumpToActive(); break;
        case 18: setState((*reinterpret_cast< Phonon::State(*)>(_a[1])),(*reinterpret_cast< Phonon::State(*)>(_a[2]))); break;
        case 19: selectionChanged(); break;
        case 20: playItem((*reinterpret_cast< PlayListItem*(*)>(_a[1]))); break;
        case 21: getNextSource(); break;
        case 22: getPreviousSource(); break;
        case 23: getActualSource(); break;
        case 24: tabChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 25;
    }
    return _id;
}

// SIGNAL 0
void PlayListTabs::visibleChanged(PlayListWidget * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void PlayListTabs::enableRemoveAction(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void PlayListTabs::playSource(Phonon::MediaSource & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void PlayListTabs::trackStringChanged(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void PlayListTabs::giveSource(Phonon::MediaSource & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void PlayListTabs::activeItemExists(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_END_MOC_NAMESPACE
