#include <Python.h>
#include <PRP/Modifier/plPythonFileMod.h>
#include "pyPythonFileMod.h"
#include "pyModifier.h"
#include "../KeyedObject/pyKey.h"
#include "../pyCreatable.h"

extern "C" {

static PyObject* pyPythonFileMod_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyPythonFileMod* self = (pyPythonFileMod*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plPythonFileMod();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pyPythonFileMod_Convert(PyObject*, PyObject* args) {
    pyCreatable* cre;
    if (!PyArg_ParseTuple(args, "O", &cre)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a plCreatable");
        return NULL;
    }
    if (!pyCreatable_Check((PyObject*)cre)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a plCreatable");
        return NULL;
    }
    return pyPythonFileMod_FromPythonFileMod(plPythonFileMod::Convert(cre->fThis));
}

static PyObject* pyPythonFileMod_clearReceivers(pyPythonFileMod* self) {
    self->fThis->clearReceivers();
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyPythonFileMod_clearParameters(pyPythonFileMod* self) {
    self->fThis->clearParameters();
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyPythonFileMod_addReceiver(pyPythonFileMod* self, PyObject* args) {
    pyKey* key;
    if (!PyArg_ParseTuple(args, "O", &key)) {
        PyErr_SetString(PyExc_TypeError, "addReceiver expects a plKey");
        return NULL;
    }
    if (!pyKey_Check((PyObject*)key)) {
        PyErr_SetString(PyExc_TypeError, "addReceiver expects a plKey");
        return NULL;
    }
    self->fThis->addReceiver(*key->fThis);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyPythonFileMod_addParameter(pyPythonFileMod* self, PyObject* args) {
    pyPythonParameter* param;
    if (!PyArg_ParseTuple(args, "O", &param)) {
        PyErr_SetString(PyExc_TypeError, "addParameter expects a plPythonParameter");
        return NULL;
    }
    if (!pyPythonParameter_Check((PyObject*)param)) {
        PyErr_SetString(PyExc_TypeError, "addParameter expects a plPythonParameter");
        return NULL;
    }
    self->fThis->addParameter(*param->fThis);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyPythonFileMod_getFilename(pyPythonFileMod* self, void*) {
    return PyString_FromString(self->fThis->getFilename().cstr());
}

static PyObject* pyPythonFileMod_getReceivers(pyPythonFileMod* self, void*) {
    PyObject* list = PyList_New(self->fThis->getNumReceivers());
    for (size_t i=0; i<self->fThis->getNumReceivers(); i++)
        PyList_SET_ITEM(list, i, pyKey_FromKey(self->fThis->getReceiver(i)));
    return list;
}

static PyObject* pyPythonFileMod_getParameters(pyPythonFileMod* self, void*) {
    PyObject* list = PyList_New(self->fThis->getNumParameters());
    for (size_t i=0; i<self->fThis->getNumParameters(); i++)
        PyList_SET_ITEM(list, i, pyPythonParameter_FromPythonParameter(self->fThis->getParameter(i)));
    return list;
}

static int pyPythonFileMod_setFilename(pyPythonFileMod* self, PyObject* value, void*) {
    if (value == NULL) {
        self->fThis->setFilename("");
        return 0;
    }
    if (!PyString_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "filename should be a string");
        return -1;
    }
    self->fThis->setFilename(PyString_AsString(value));
    return 0;
}

static int pyPythonFileMod_setReceivers(pyPythonFileMod* self, PyObject* value, void*) {
    PyErr_SetString(PyExc_RuntimeError, "to add receivers, use addReceiver");
    return -1;
}

static int pyPythonFileMod_setParameters(pyPythonFileMod* self, PyObject* value, void*) {
    PyErr_SetString(PyExc_RuntimeError, "to add parameters, use addParameter");
    return -1;
}

static PyMethodDef pyPythonFileMod_Methods[] = {
    { "Convert", (PyCFunction)pyPythonFileMod_Convert, METH_VARARGS | METH_STATIC,
      "Convert a Creatable to a plPythonFileMod" },
    { "clearReceivers", (PyCFunction)pyPythonFileMod_clearReceivers, METH_NOARGS,
      "Remove all receivers from the Python File Mod" },
    { "clearParameters", (PyCFunction)pyPythonFileMod_clearParameters, METH_NOARGS,
      "Remove all parameters from the Python File Mod" },
    { "addReceiver", (PyCFunction)pyPythonFileMod_addReceiver, METH_VARARGS,
      "Params: key\n"
      "Add a receiver to the Python File Mod" },
    { "addParameter", (PyCFunction)pyPythonFileMod_addParameter, METH_VARARGS,
      "Params: parameter\n"
      "Add a parameter to the Python File Mod" },
    { NULL, NULL, 0, NULL }
};

static PyGetSetDef pyPythonFileMod_GetSet[] = {
    { "filename", (getter)pyPythonFileMod_getFilename, (setter)pyPythonFileMod_setFilename, NULL, NULL },
    { "receivers", (getter)pyPythonFileMod_getReceivers, (setter)pyPythonFileMod_setReceivers, NULL, NULL },
    { "parameters", (getter)pyPythonFileMod_getParameters, (setter)pyPythonFileMod_setParameters, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyPythonFileMod_Type = {
    PyObject_HEAD_INIT(NULL)
    0,                                  /* ob_size */
    "PyPlasma.plPythonFileMod",         /* tp_name */
    sizeof(pyPythonFileMod),            /* tp_basicsize */
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
    "plPythonFileMod wrapper",          /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyPythonFileMod_Methods,            /* tp_methods */
    NULL,                               /* tp_members */
    pyPythonFileMod_GetSet,             /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyPythonFileMod_new,                /* tp_new */
    NULL,                               /* tp_free */
    NULL,                               /* tp_is_gc */

    NULL,                               /* tp_bases */
    NULL,                               /* tp_mro */
    NULL,                               /* tp_cache */
    NULL,                               /* tp_subclasses */
    NULL,                               /* tp_weaklist */
};

PyObject* Init_pyPythonFileMod_Type() {
    pyPythonFileMod_Type.tp_base = &pyMultiModifier_Type;
    if (PyType_Ready(&pyPythonFileMod_Type) < 0)
        return NULL;

    Py_INCREF(&pyPythonFileMod_Type);
    return (PyObject*)&pyPythonFileMod_Type;
}

int pyPythonFileMod_Check(PyObject* obj) {
    if (obj->ob_type == &pyPythonFileMod_Type
        || PyType_IsSubtype(obj->ob_type, &pyPythonFileMod_Type))
        return 1;
    return 0;
}

PyObject* pyPythonFileMod_FromPythonFileMod(class plPythonFileMod* mod) {
    if (mod == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyPythonFileMod* pymod = PyObject_New(pyPythonFileMod, &pyPythonFileMod_Type);
    pymod->fThis = mod;
    pymod->fPyOwned = false;
    return (PyObject*)pymod;
}

}