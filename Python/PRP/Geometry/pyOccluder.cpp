#include <Python.h>
#include <PRP/Geometry/plOccluder.h>
#include "pyOccluder.h"
#include "../Object/pyObjInterface.h"
#include "../Region/pyBounds.h"
#include "../KeyedObject/pyKey.h"
#include "../pyCreatable.h"

extern "C" {

static PyObject* pyOccluder_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyOccluder* self = (pyOccluder*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plOccluder();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pyOccluder_Convert(PyObject*, PyObject* args) {
    pyCreatable* cre;
    if (!PyArg_ParseTuple(args, "O", &cre)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a plCreatable");
        return NULL;
    }
    if (!pyCreatable_Check((PyObject*)cre)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a plCreatable");
        return NULL;
    }
    return pyOccluder_FromOccluder(plOccluder::Convert(cre->fThis));
}

static PyObject* pyOccluder_clearPolys(pyOccluder* self) {
    self->fThis->clearPolys();
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyOccluder_addPoly(pyOccluder* self, PyObject* args) {
    pyCullPoly* poly;
    if (!PyArg_ParseTuple(args, "O", &poly)) {
        PyErr_SetString(PyExc_TypeError, "addPoly expects a plCullPoly");
        return NULL;
    }
    if (!pyCullPoly_Check((PyObject*)poly)) {
        PyErr_SetString(PyExc_TypeError, "addPoly expects a plCullPoly");
        return NULL;
    }
    self->fThis->addPoly(*poly->fThis);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyOccluder_delPoly(pyOccluder* self, PyObject* args) {
    int idx;
    if (!PyArg_ParseTuple(args, "i", &idx)) {
        PyErr_SetString(PyExc_TypeError, "delPoly expects an int");
        return NULL;
    }
    self->fThis->delPoly(idx);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyOccluder_getPriority(pyOccluder* self, void*) {
    return PyFloat_FromDouble(self->fThis->getPriority());
}

static PyObject* pyOccluder_getBounds(pyOccluder* self, void*) {
    return pyBounds3Ext_FromBounds3Ext(self->fThis->getWorldBounds());
}

static PyObject* pyOccluder_getNode(pyOccluder* self, void*) {
    return pyKey_FromKey(self->fThis->getSceneNode());
}

static PyObject* pyOccluder_getPolys(pyOccluder* self, void*) {
    PyObject* list = PyList_New(self->fThis->getNumPolys());
    for (size_t i=0; i<self->fThis->getNumPolys(); i++)
        PyList_SET_ITEM(list, i, pyCullPoly_FromCullPoly(self->fThis->getPoly(i)));
    return list;
}

static int pyOccluder_setPriority(pyOccluder* self, PyObject* value, void*) {
    if (value == NULL || !PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "priority should be a float");
        return -1;
    }
    self->fThis->setPriority(PyFloat_AsDouble(value));
    return 0;
}

static int pyOccluder_setBounds(pyOccluder* self, PyObject* value, void*) {
    if (value == NULL || value == Py_None) {
        self->fThis->setWorldBounds(hsBounds3Ext());
        return 0;
    }
    if (!pyBounds3Ext_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "worldBounds should be an hsBounds3Ext");
        return -1;
    }
    self->fThis->setWorldBounds(*((pyBounds3Ext*)value)->fThis);
    return 0;
}

static int pyOccluder_setNode(pyOccluder* self, PyObject* value, void*) {
    if (value == NULL || value == Py_None) {
        self->fThis->setSceneNode(plKey());
        return 0;
    }
    if (!pyKey_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "sceneNode should be a plKey");
        return -1;
    }
    self->fThis->setSceneNode(*((pyKey*)value)->fThis);
    return 0;
}

static int pyOccluder_setPolys(pyOccluder* self, PyObject* value, void*) {
    PyErr_SetString(PyExc_RuntimeError, "to add polys, use addPoly()");
    return -1;
}

static PyMethodDef pyOccluder_Methods[] = {
    { "Convert", (PyCFunction)pyOccluder_Convert, METH_VARARGS | METH_STATIC,
      "Convert a plCreatable to a plOccluder" },
    { "clearPolys", (PyCFunction)pyOccluder_clearPolys, METH_NOARGS,
      "Remove all plCullPolys from the occluder" },
    { "addPoly", (PyCFunction)pyOccluder_addPoly, METH_VARARGS,
      "Params: poly\n"
      "Add a plCullPoly to the occluder" },
    { "delPoly", (PyCFunction)pyOccluder_delPoly, METH_VARARGS,
      "Params: idx\n"
      "Remove a plCullPoly from the occluder" },
    { NULL, NULL, 0, NULL }
};

static PyGetSetDef pyOccluder_GetSet[] = {
    { "priority", (getter)pyOccluder_getPriority, (setter)pyOccluder_setPriority, NULL, NULL },
    { "worldBounds", (getter)pyOccluder_getBounds, (setter)pyOccluder_setBounds, NULL, NULL },
    { "sceneNode", (getter)pyOccluder_getNode, (setter)pyOccluder_setNode, NULL, NULL },
    { "polys", (getter)pyOccluder_getPolys, (setter)pyOccluder_setPolys, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyOccluder_Type = {
    PyObject_HEAD_INIT(NULL)
    0,                                  /* ob_size */
    "PyPlasma.plOccluder",              /* tp_name */
    sizeof(pyOccluder),                 /* tp_basicsize */
    0,                                  /* tp_itemsize */

    NULL,                               /* tp_dealloc */
    NULL,                               /* tp_print */
    NULL,                               /* tp_getattr */
    NULL,                               /* tp_setattr */
    NULL,                               /* tp_compare */
    NULL,                               /* tp_repr */
    NULL,                               /* tp_as_number */
    NULL,                               /* tp_as_sequence */
    NULL,                               /* tp_as_mapping */
    NULL,                               /* tp_hash */
    NULL,                               /* tp_call */
    NULL,                               /* tp_str */
    NULL,                               /* tp_getattro */
    NULL,                               /* tp_setattro */
    NULL,                               /* tp_as_buffer */

    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE, /* tp_flags */
    "plOccluder wrapper",               /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyOccluder_Methods,                 /* tp_methods */
    NULL,                               /* tp_members */
    pyOccluder_GetSet,                  /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyOccluder_new,                     /* tp_new */
    NULL,                               /* tp_free */
    NULL,                               /* tp_is_gc */

    NULL,                               /* tp_bases */
    NULL,                               /* tp_mro */
    NULL,                               /* tp_cache */
    NULL,                               /* tp_subclasses */
    NULL,                               /* tp_weaklist */
};

PyObject* Init_pyOccluder_Type() {
    pyOccluder_Type.tp_base = &pyObjInterface_Type;
    if (PyType_Ready(&pyOccluder_Type) < 0)
        return NULL;

    Py_INCREF(&pyOccluder_Type);
    return (PyObject*)&pyOccluder_Type;
}

int pyOccluder_Check(PyObject* obj) {
    if (obj->ob_type == &pyOccluder_Type
        || PyType_IsSubtype(obj->ob_type, &pyOccluder_Type))
        return 1;
    return 0;
}

PyObject* pyOccluder_FromOccluder(class plOccluder* obj) {
    if (obj == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyOccluder* pobj = PyObject_New(pyOccluder, &pyOccluder_Type);
    pobj->fThis = obj;
    pobj->fPyOwned = false;
    return (PyObject*)pobj;
}

}