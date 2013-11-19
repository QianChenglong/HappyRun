/****************************************************************************
** Meta object code from reading C++ file 'PathsPage.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "PathsPage.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'PathsPage.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_PathsPage[] = {

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
      11,   10,   10,   10, 0x0a,
      18,   10,   10,   10, 0x0a,
      24,   10,   10,   10, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_PathsPage[] = {
    "PathsPage\0\0save()\0add()\0remove()\0"
};

void PathsPage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        PathsPage *_t = static_cast<PathsPage *>(_o);
        switch (_id) {
        case 0: _t->save(); break;
        case 1: _t->add(); break;
        case 2: _t->remove(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData PathsPage::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject PathsPage::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_PathsPage,
      qt_meta_data_PathsPage, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &PathsPage::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *PathsPage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *PathsPage::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PathsPage))
        return static_cast<void*>(const_cast< PathsPage*>(this));
    return QWidget::qt_metacast(_clname);
}

int PathsPage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
