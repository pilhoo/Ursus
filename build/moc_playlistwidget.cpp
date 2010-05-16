/****************************************************************************
** Meta object code from reading C++ file 'playlistwidget.h'
**
** Created: Sun May 16 10:23:00 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../playlistwidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'playlistwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_PlayListWidget[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
      26,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      16,   15,   15,   15, 0x05,
      32,   15,   15,   15, 0x05,

 // slots: signature, parameters, type, tag, flags
      65,   56,   15,   15, 0x0a,
      91,   86,   15,   15, 0x2a,
     126,  108,   15,   15, 0x0a,
     184,  170,   15,   15, 0x2a,
     237,  228,  224,   15, 0x0a,
     263,  258,  224,   15, 0x2a,
     280,   15,   15,   15, 0x0a,
     303,  297,   15,   15, 0x0a,
     339,   15,   15,   15, 0x0a,
     356,  297,   15,   15, 0x0a,
     387,   15,   15,   15, 0x0a,
     403,  228,  224,   15, 0x0a,
     433,  258,  224,   15, 0x2a,
     459,  228,  224,   15, 0x0a,
     489,  258,  224,   15, 0x2a,
     515,  258,   15,   15, 0x0a,
     541,  258,   15,   15, 0x0a,
     579,  567,   15,   15, 0x0a,
     613,  610,   15,   15, 0x0a,
     653,  647,   15,   15, 0x0a,
     679,   15,   15,   15, 0x0a,
     691,   15,   15,   15, 0x08,
     705,   15,   15,   15, 0x08,
     723,  719,   15,   15, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_PlayListWidget[] = {
    "PlayListWidget\0\0playListEmpty()\0"
    "playItem(PlayListItem*)\0file,pos\0"
    "addFile(QString,int)\0file\0addFile(QString)\0"
    "file,metaInfo,pos\0"
    "addFile(QString,QMap<QString,QString>&,int)\0"
    "file,metaInfo\0addFile(QString,QMap<QString,QString>&)\0"
    "int\0path,pos\0addDir(QString&,int)\0"
    "path\0addDir(QString&)\0removeSelected()\0"
    "item,\0doubleClicked(QTreeWidgetItem*,int)\0"
    "scrollToActive()\0deselect(QTreeWidgetItem*,int)\0"
    "clearPlayList()\0loadM3UPlayList(QString&,int)\0"
    "loadM3UPlayList(QString&)\0"
    "loadPLSPlayList(QString&,int)\0"
    "loadPLSPlayList(QString&)\0"
    "saveM3UPlayList(QString&)\0"
    "savePLSPlayList(QString&)\0nr,,newSize\0"
    "updateColumnWidth(int,int,int)\0,,\0"
    "updateColumnPosition(int,int,int)\0"
    "point\0headerContextMenu(QPoint)\0"
    "setScroll()\0hideSection()\0showSection()\0"
    "pos\0printPos(int)\0"
};

const QMetaObject PlayListWidget::staticMetaObject = {
    { &QTreeWidget::staticMetaObject, qt_meta_stringdata_PlayListWidget,
      qt_meta_data_PlayListWidget, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &PlayListWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *PlayListWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *PlayListWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PlayListWidget))
        return static_cast<void*>(const_cast< PlayListWidget*>(this));
    return QTreeWidget::qt_metacast(_clname);
}

int PlayListWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTreeWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: playListEmpty(); break;
        case 1: playItem((*reinterpret_cast< PlayListItem*(*)>(_a[1]))); break;
        case 2: addFile((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: addFile((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: addFile((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QMap<QString,QString>(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 5: addFile((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QMap<QString,QString>(*)>(_a[2]))); break;
        case 6: { int _r = addDir((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 7: { int _r = addDir((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 8: removeSelected(); break;
        case 9: doubleClicked((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 10: scrollToActive(); break;
        case 11: deselect((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 12: clearPlayList(); break;
        case 13: { int _r = loadM3UPlayList((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 14: { int _r = loadM3UPlayList((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 15: { int _r = loadPLSPlayList((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 16: { int _r = loadPLSPlayList((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 17: saveM3UPlayList((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 18: savePLSPlayList((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 19: updateColumnWidth((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 20: updateColumnPosition((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 21: headerContextMenu((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 22: setScroll(); break;
        case 23: hideSection(); break;
        case 24: showSection(); break;
        case 25: printPos((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 26;
    }
    return _id;
}

// SIGNAL 0
void PlayListWidget::playListEmpty()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void PlayListWidget::playItem(PlayListItem * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
