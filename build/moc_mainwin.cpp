/****************************************************************************
** Meta object code from reading C++ file 'mainwin.h'
**
** Created: Sat May 15 19:51:55 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../mainwin.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwin.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_UrsusMainWin[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      19,   14,   13,   13, 0x0a,
      42,   32,   13,   13, 0x0a,
      91,   84,   13,   13, 0x0a,
     120,  116,   13,   13, 0x0a,
     141,   13,   13,   13, 0x0a,
     160,  148,   13,   13, 0x0a,
     184,   13,   13,   13, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_UrsusMainWin[] = {
    "UrsusMainWin\0\0time\0tick(qint64)\0"
    "newState,\0stateChanged(Phonon::State,Phonon::State)\0"
    "enable\0enableRemoveAction(bool)\0vol\0"
    "volumeChanged(qreal)\0mute()\0trackString\0"
    "setTrackString(QString)\0setActionsEnabled(bool)\0"
};

const QMetaObject UrsusMainWin::staticMetaObject = {
    { &KXmlGuiWindow::staticMetaObject, qt_meta_stringdata_UrsusMainWin,
      qt_meta_data_UrsusMainWin, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &UrsusMainWin::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *UrsusMainWin::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *UrsusMainWin::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_UrsusMainWin))
        return static_cast<void*>(const_cast< UrsusMainWin*>(this));
    return KXmlGuiWindow::qt_metacast(_clname);
}

int UrsusMainWin::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = KXmlGuiWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: tick((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        case 1: stateChanged((*reinterpret_cast< Phonon::State(*)>(_a[1])),(*reinterpret_cast< Phonon::State(*)>(_a[2]))); break;
        case 2: enableRemoveAction((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: volumeChanged((*reinterpret_cast< qreal(*)>(_a[1]))); break;
        case 4: mute(); break;
        case 5: setTrackString((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: setActionsEnabled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 7;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
