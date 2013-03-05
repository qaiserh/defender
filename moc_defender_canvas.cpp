/****************************************************************************
** Meta object code from reading C++ file 'defender_canvas.h'
**
** Created: Mon Dec 17 05:58:07 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "defender_canvas.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'defender_canvas.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DefenderCanvas[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      20,   16,   15,   15, 0x05,
      47,   16,   15,   15, 0x05,
      73,   16,   15,   15, 0x05,

 // slots: signature, parameters, type, tag, flags
      99,   15,   15,   15, 0x0a,
     113,   15,   15,   15, 0x0a,
     125,   15,   15,   15, 0x0a,
     136,   15,   15,   15, 0x0a,
     147,   15,   15,   15, 0x0a,
     161,   15,   15,   15, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_DefenderCanvas[] = {
    "DefenderCanvas\0\0str\0needsButtonChange(QString)\0"
    "needsTimerUpdate(QString)\0"
    "needsScoreUpdate(QString)\0buttonPress()\0"
    "resetGame()\0showTime()\0showHelp()\0"
    "updateScore()\0timerTicked()\0"
};

void DefenderCanvas::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        DefenderCanvas *_t = static_cast<DefenderCanvas *>(_o);
        switch (_id) {
        case 0: _t->needsButtonChange((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->needsTimerUpdate((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->needsScoreUpdate((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->buttonPress(); break;
        case 4: _t->resetGame(); break;
        case 5: _t->showTime(); break;
        case 6: _t->showHelp(); break;
        case 7: _t->updateScore(); break;
        case 8: _t->timerTicked(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData DefenderCanvas::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject DefenderCanvas::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_DefenderCanvas,
      qt_meta_data_DefenderCanvas, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DefenderCanvas::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DefenderCanvas::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DefenderCanvas::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DefenderCanvas))
        return static_cast<void*>(const_cast< DefenderCanvas*>(this));
    return QWidget::qt_metacast(_clname);
}

int DefenderCanvas::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void DefenderCanvas::needsButtonChange(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void DefenderCanvas::needsTimerUpdate(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void DefenderCanvas::needsScoreUpdate(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
