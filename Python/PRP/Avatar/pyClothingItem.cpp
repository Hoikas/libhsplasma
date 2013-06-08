/* This file is part of HSPlasma.
 *
 * HSPlasma is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * HSPlasma is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with HSPlasma.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <PyPlasma.h>
#include <PRP/Avatar/plClothingItem.h>
#include "pyClothingItem.h"
#include "../KeyedObject/pyKey.h"
#include "../KeyedObject/pyKeyedObject.h"
#include "../pyCreatable.h"
#include "Sys/pyColor.h"

extern "C" {

static PyObject* pyClothingItem_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyClothingItem* self = (pyClothingItem*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plClothingItem();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pyClothingItem_addElement(pyClothingItem* self, PyObject* args) {
    PyObject* element;
    if (!PyArg_ParseTuple(args, "O", &element) || !PyAnyStr_Check(element)) {
        PyErr_SetString(PyExc_TypeError, "addElement expects string");
        return NULL;
    }
    return PyInt_FromLong(self->fThis->addElement(PyStr_To_PlStr(element)));
}

static PyObject* pyClothingItem_clearElements(pyClothingItem* self) {
    self->fThis->clearElements();
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyClothingItem_delElement(pyClothingItem* self, PyObject* args) {
    int element;
    if (!PyArg_ParseTuple(args, "i", &element)) {
        PyErr_SetString(PyExc_TypeError, "delElement expects int");
        return NULL;
    }
    self->fThis->delElement(element);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyClothingItem_getAccessory(pyClothingItem* self, void*) {
    return pyKey_FromKey(self->fThis->getAccessory());
}

static PyObject* pyClothingItem_getCustomText(pyClothingItem* self, void*) {
    return PlStr_To_PyStr(self->fThis->getCustomText());
}

static PyObject* pyClothingItem_getDefaultTint1(pyClothingItem* self, void*) {
    return pyColorRGBA_FromColorRGBA(self->fThis->getDefaultTint1());
}

static PyObject* pyClothingItem_getDefaultTint2(pyClothingItem* self, void*) {
    return pyColorRGBA_FromColorRGBA(self->fThis->getDefaultTint2());
}

static PyObject* pyClothingItem_getDescription(pyClothingItem* self, void* closure) {
    return PlStr_To_PyStr(self->fThis->getDescription());
}

static PyObject* pyClothingItem_getElementTexture(pyClothingItem* self, PyObject* args) {
    int element, layer;
    if (!PyArg_ParseTuple(args, "ii", &element, &layer)) {
        PyErr_SetString(PyExc_TypeError, "getElementTexture expects int, int");
        return NULL;
    }

    return pyKey_FromKey(self->fThis->getElementTexture(element, layer));
}

static PyObject* pyClothingItem_getElements(pyClothingItem* self) {
    PyObject* set = PyTuple_New(self->fThis->getElementCount());
    for (int i = 0; i < self->fThis->getElementCount(); ++i)
        PyTuple_SET_ITEM(set, i, PlStr_To_PyStr(self->fThis->getElementName(i)));
    return set;
}

static PyObject* pyClothingItem_getGroup(pyClothingItem* self, void*) {
    return PyInt_FromLong(self->fThis->getGroup());
}

static PyObject* pyClothingItem_getItemName(pyClothingItem* self, void*) {
    return PlStr_To_PyStr(self->fThis->getItemName());
}

static PyObject* pyClothingItem_getIcon(pyClothingItem* self, void*) {
    return pyKey_FromKey(self->fThis->getIcon());
}

static PyObject* pyClothingItem_getMesh(pyClothingItem* self, PyObject* args) {
    int lod = plClothingItem::kLODHigh;
    if (!PyArg_ParseTuple(args, "i", &lod)) {
        PyErr_SetString(PyExc_TypeError, "getMesh expects int");
        return NULL;
    }

    return pyKey_FromKey(self->fThis->getMesh(lod));
}

static PyObject* pyClothingItem_getSortOrder(pyClothingItem* self, void*) {
    return PyInt_FromLong(self->fThis->getSortOrder());
}

static PyObject* pyClothingItem_getTileset(pyClothingItem* self, void*) {
    return PyInt_FromLong(self->fThis->getTileset());
}

static int pyClothingItem_setAccessory(pyClothingItem* self, PyObject* value, void*) {
    if (!pyKey_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "accessory must be a plKey");
        return -1;
    }
    self->fThis->setAccessory(*((pyKey*)value)->fThis);
    return 0;
}

static int pyClothingItem_setCustomText(pyClothingItem* self, PyObject* value, void*) {
    if (value == NULL) {
        self->fThis->setDescription("");
    } else {
        if (!PyAnyStr_Check(value)) {
            PyErr_SetString(PyExc_TypeError, "customText must be a string");
            return -1;
        }
        self->fThis->setCustomText(PyStr_To_PlStr(value));
    }
    return 0;
}

static int pyClothingItem_setDefaultTint1(pyClothingItem* self, PyObject* value, void*) {
    if (!pyColorRGBA_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "defaultTint1 must be an hsColorRGBA");
        return -1;
    }
    self->fThis->setDefaultTint1(*((pyColorRGBA*)value)->fThis);
    return 0;
}

static int pyClothingItem_setDefaultTint2(pyClothingItem* self, PyObject* value, void*) {
    if (!pyColorRGBA_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "defaultTint2 must be an hsColorRGBA");
        return -1;
    }
    self->fThis->setDefaultTint2(*((pyColorRGBA*)value)->fThis);
    return 0;
}

static int pyClothingItem_setDescription(pyClothingItem* self, PyObject* value, void* closure) {
    if (value == NULL) {
        self->fThis->setDescription("");
    } else {
        if (!PyAnyStr_Check(value)) {
            PyErr_SetString(PyExc_TypeError, "description must be a string");
            return -1;
        }
        self->fThis->setDescription(PyStr_To_PlStr(value));
    }
    return 0;
}

static PyObject* pyClothingItem_setElementTexture(pyClothingItem* self, PyObject* args) {
    int element, layer;
    pyKey* key;

    if (!PyArg_ParseTuple(args, "iiO", &element, &layer, &key)) {
        PyErr_SetString(PyExc_TypeError, "setElementTexture expects int, int plKey");
        return NULL;
    }
    if (!pyKey_Check((PyObject*)key)) {
        PyErr_SetString(PyExc_TypeError, "setElementTexture expects int, int plKey");
        return NULL;
    }

    self->fThis->setElementTexture(element, layer, *key->fThis);
    Py_INCREF(Py_None);
    return Py_None;
}

static int pyClothingItem_setGroup(pyClothingItem* self, PyObject* value, void*) {
    if (!PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "group must be an int");
        return -1;
    }
    self->fThis->setGroup(PyInt_AsLong(value));
    return 0;
}

static int pyClothingItem_setIcon(pyClothingItem* self, PyObject* value, void*) {
    if (!pyKey_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "icon must be a plKey");
        return -1;
    }
    self->fThis->setIcon(*((pyKey*)value)->fThis);
    return 0;
}

static int pyClothingItem_setItemName(pyClothingItem* self, PyObject* value, void*) {
    if (value == NULL) {
        self->fThis->setItemName("");
    } else {
        if (!PyAnyStr_Check(value)) {
            PyErr_SetString(PyExc_TypeError, "itemName must be a string");
            return -1;
        }
        self->fThis->setItemName(PyStr_To_PlStr(value));
    }
    return 0;
}

static PyObject* pyClothingItem_setMesh(pyClothingItem* self, PyObject* args) {
    int lod = plClothingItem::kLODHigh;
    pyKey* key;

    if (!PyArg_ParseTuple(args, "iO", &lod, &key)) {
        PyErr_SetString(PyExc_TypeError, "setMesh expects int, plKey");
        return NULL;
    }
    if (!pyKey_Check((PyObject*)key)) {
        PyErr_SetString(PyExc_TypeError, "setMesh expects int, plKey");
        return NULL;
    }

    self->fThis->setMesh(lod, *(key->fThis));
    Py_INCREF(Py_None);
    return Py_None;
}

static int pyClothingItem_setSortOrder(pyClothingItem* self, PyObject* value, void*) {
    if (!PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "sortOrder must be an int");
        return -1;
    }
    self->fThis->setSortOrder(PyInt_AsLong(value));
    return 0;
}

static int pyClothingItem_setTileset(pyClothingItem* self, PyObject* value, void*) {
    if (!PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "tileset must be an int");
        return -1;
    }
    self->fThis->setTileset(PyInt_AsLong(value));
    return 0;
}

PyMethodDef pyClothingItem_Methods[] = {
    { "addElement", (PyCFunction)pyClothingItem_addElement, METH_VARARGS,
      "Params: element\n"
      "Adds a named element to the clothing item" },
    { "clearElements", (PyCFunction)pyClothingItem_clearElements, METH_NOARGS,
      "Removes all elements from the clothing item" },
    { "delElement", (PyCFunction)pyClothingItem_delElement, METH_VARARGS,
      "Params: element\n"
      "Removes an element from the clothing item" },
    { "getElements", (PyCFunction)pyClothingItem_getElements, METH_NOARGS,
      "Gets a sequence of all elements in this clothing item" },
    { "getElementTexture", (PyCFunction)pyClothingItem_getElementTexture, METH_VARARGS,
      "Params: element, layer\n"
      "Gets the Key of the texture for the specified element on the given layer" },
    { "getMesh", (PyCFunction)pyClothingItem_getMesh, METH_VARARGS,
      "Params: lod\n"
      "Gets the Key of the mesh for the specified LOD" },
    { "setElementTexture", (PyCFunction)pyClothingItem_getElementTexture, METH_VARARGS,
      "Params: element, layer\n"
      "Sets the Key of the texture for the specified element on the given layer" },
    { "setMesh", (PyCFunction)pyClothingItem_setMesh, METH_VARARGS,
      "Params: lod, mesh\n"
      "Sets the Key of the mesh for the specified LOD" },
    { NULL, NULL, 0, NULL }
};

PyGetSetDef pyClothingItem_GetSet[] = {
    { _pycs("accessory"), (getter)pyClothingItem_getAccessory,
        (setter)pyClothingItem_setAccessory, NULL, NULL },
    { _pycs("customText"), (getter)pyClothingItem_getCustomText,
        (setter)pyClothingItem_setCustomText, NULL, NULL },
    { _pycs("defaultTint1"), (getter)pyClothingItem_getDefaultTint1,
        (setter)pyClothingItem_setDefaultTint1, NULL, NULL },
    { _pycs("defaultTint2"), (getter)pyClothingItem_getDefaultTint2,
        (setter)pyClothingItem_setDefaultTint2, NULL, NULL },
    { _pycs("description"), (getter)pyClothingItem_getDescription,
        (setter)pyClothingItem_setDescription, NULL, NULL },
    { _pycs("group"), (getter)pyClothingItem_getGroup,
        (setter)pyClothingItem_setGroup, NULL, NULL },
    { _pycs("icon"), (getter)pyClothingItem_getIcon,
        (setter)pyClothingItem_setIcon, NULL, NULL },
    { _pycs("itemName"), (getter)pyClothingItem_getItemName,
        (setter)pyClothingItem_setItemName, NULL, NULL },
    { _pycs("sortOrder"), (getter)pyClothingItem_getSortOrder,
        (setter)pyClothingItem_setSortOrder, NULL, NULL },
    { _pycs("tileset"), (getter)pyClothingItem_getTileset,
        (setter)pyClothingItem_setTileset, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyClothingItem_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyPlasma.plClothingItem",          /* tp_name */
    sizeof(pyClothingItem),             /* tp_basicsize */
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
    "plClothingItem wrapper",                 /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyClothingItem_Methods,             /* tp_methods */
    NULL,                               /* tp_members */
    pyClothingItem_GetSet,              /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyClothingItem_new,                 /* tp_new */
    NULL,                               /* tp_free */
    NULL,                               /* tp_is_gc */

    NULL,                               /* tp_bases */
    NULL,                               /* tp_mro */
    NULL,                               /* tp_cache */
    NULL,                               /* tp_subclasses */
    NULL,                               /* tp_weaklist */

    NULL,                               /* tp_del */
    TP_VERSION_TAG_INIT                 /* tp_version_tag */
};

PyObject* Init_pyClothingItem_Type() {
    pyClothingItem_Type.tp_base = &pyKeyedObject_Type;
    if (PyType_Ready(&pyClothingItem_Type) < 0)
        return NULL;

    PyDict_SetItemString(pyClothingItem_Type.tp_dict, "kLODHigh",
        PyInt_FromLong(plClothingItem::kLODHigh));
    PyDict_SetItemString(pyClothingItem_Type.tp_dict, "kLODMedium",
        PyInt_FromLong(plClothingItem::kLODMedium));
    PyDict_SetItemString(pyClothingItem_Type.tp_dict, "kLODLow",
        PyInt_FromLong(plClothingItem::kLODLow));

    Py_INCREF(&pyClothingItem_Type);
    return (PyObject*)&pyClothingItem_Type;
}

int pyClothingItem_Check(PyObject* obj) {
    if (obj->ob_type == &pyClothingItem_Type
        || PyType_IsSubtype(obj->ob_type, &pyClothingItem_Type))
        return 1;
    return 0;
}

PyObject* pyClothingItem_FromClothingItem(class plClothingItem* obj) {
    if (obj == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyClothingItem* node = PyObject_New(pyClothingItem, &pyClothingItem_Type);
    node->fThis = obj;
    node->fPyOwned = false;
    return (PyObject*)node;
}

}
