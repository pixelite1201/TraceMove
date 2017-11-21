/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created: Sun Jun 28 11:49:27 2015
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      23,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x08,
      19,   11,   11,   11, 0x08,
      26,   11,   11,   11, 0x08,
      37,   11,   11,   11, 0x08,
      46,   11,   11,   11, 0x08,
      57,   11,   11,   11, 0x08,
      64,   11,   11,   11, 0x08,
      81,   11,   11,   11, 0x08,
      93,   11,   11,   11, 0x08,
     105,   11,   11,   11, 0x08,
     123,   11,   11,   11, 0x08,
     133,   11,   11,   11, 0x08,
     152,   11,   11,   11, 0x08,
     170,   11,   11,   11, 0x08,
     182,   11,   11,   11, 0x08,
     197,   11,   11,   11, 0x08,
     209,   11,   11,   11, 0x08,
     227,   11,   11,   11, 0x08,
     243,   11,   11,   11, 0x08,
     252,   11,   11,   11, 0x08,
     262,   11,   11,   11, 0x08,
     273,   11,   11,   11, 0x08,
     292,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0open()\0save()\0penColor()\0"
    "eraser()\0skeleton()\0play()\0redrawSkeleton()\0"
    "nextFrame()\0prevFrame()\0spinnerValue(int)\0"
    "rigging()\0retrieveSkeleton()\0"
    "changeRigPoints()\0modifyRig()\0"
    "updateShadow()\0shadowOFF()\0skeletonOFF(bool)\0"
    "sketchOFF(bool)\0playON()\0playOFF()\0"
    "penWidth()\0shadowVisibility()\0"
    "normalMode()\0"
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->open(); break;
        case 1: _t->save(); break;
        case 2: _t->penColor(); break;
        case 3: _t->eraser(); break;
        case 4: _t->skeleton(); break;
        case 5: _t->play(); break;
        case 6: _t->redrawSkeleton(); break;
        case 7: _t->nextFrame(); break;
        case 8: _t->prevFrame(); break;
        case 9: _t->spinnerValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->rigging(); break;
        case 11: _t->retrieveSkeleton(); break;
        case 12: _t->changeRigPoints(); break;
        case 13: _t->modifyRig(); break;
        case 14: _t->updateShadow(); break;
        case 15: _t->shadowOFF(); break;
        case 16: _t->skeletonOFF((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 17: _t->sketchOFF((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 18: _t->playON(); break;
        case 19: _t->playOFF(); break;
        case 20: _t->penWidth(); break;
        case 21: _t->shadowVisibility(); break;
        case 22: _t->normalMode(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MainWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 23)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 23;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
