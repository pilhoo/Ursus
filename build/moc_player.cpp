/****************************************************************************
** Meta object code from reading C++ file 'player.h'
**
** Created: Sat May 15 19:51:54 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../player.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'player.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_UrsusPlayer[] = {

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
      13,   12,   12,   12, 0x05,
      32,   12,   12,   12, 0x05,
      49,   12,   12,   12, 0x05,

 // slots: signature, parameters, type, tag, flags
      70,   12,   12,   12, 0x0a,
      89,   77,   12,   12, 0x0a,
     116,   12,   12,   12, 0x0a,
     124,   12,   12,   12, 0x0a,
     131,   12,   12,   12, 0x0a,
     142,   12,   12,   12, 0x0a,
     156,  149,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_UrsusPlayer[] = {
    "UrsusPlayer\0\0needActualSource()\0"
    "needNextSource()\0needPreviousSource()\0"
    "play()\0mediaSource\0play(Phonon::MediaSource&)\0"
    "pause()\0stop()\0previous()\0next()\0"
    "source\0enqueue(Phonon::MediaSource&)\0"
};

const QMetaObject UrsusPlayer::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_UrsusPlayer,
      qt_meta_data_UrsusPlayer, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &UrsusPlayer::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *UrsusPlayer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *UrsusPlayer::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_UrsusPlayer))
        return static_cast<void*>(const_cast< UrsusPlayer*>(this));
    return QObject::qt_metacast(_clname);
}

int UrsusPlayer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: needActualSource(); break;
        case 1: needNextSource(); break;
        case 2: needPreviousSource(); break;
        case 3: play(); break;
        case 4: play((*reinterpret_cast< Phonon::MediaSource(*)>(_a[1]))); break;
        case 5: pause(); break;
        case 6: stop(); break;
        case 7: previous(); break;
        case 8: next(); break;
        case 9: enqueue((*reinterpret_cast< Phonon::MediaSource(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void UrsusPlayer::needActualSource()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void UrsusPlayer::needNextSource()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void UrsusPlayer::needPreviousSource()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}
QT_END_MOC_NAMESPACE
