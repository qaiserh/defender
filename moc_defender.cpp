/****************************************************************************
** Meta object code from reading C++ file 'defender.h'
**
** Created: Mon Dec 17 05:03:31 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "defender.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'defender.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Defender[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      14,   10,    9,    9, 0x08,
      40,   10,    9,    9, 0x08,
      61,   10,    9,    9, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Defender[] = {
    "Defender\0\0str\0changeButtonText(QString)\0"
    "updateTimer(QString)\0updateScore(QString)\0"
};

void Defender::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Defender *_t = static_cast<Defender *>(_o);
        switch (_id) {
        case 0: _t->changeButtonText((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->updateTimer((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->updateScore((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Defender::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Defender::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Defender,
      qt_meta_data_Defender, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Defender::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Defender::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Defender::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Defender))
        return static_cast<void*>(const_cast< Defender*>(this));
    return QWidget::qt_metacast(_clname);
}

int Defender::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
