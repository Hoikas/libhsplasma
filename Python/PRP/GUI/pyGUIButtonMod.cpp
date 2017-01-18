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

#include <PRP/GUI/pfGUIButtonMod.h>
#include "pyGUIButtonMod.h"
#include "PRP/GUI/pyGUIControlMod.h"
#include "PRP/KeyedObject/pyKey.h"

extern "C" {

PY_PLASMA_NEW(GUIButtonMod, pfGUIButtonMod)

PY_METHOD_VA(GUIButtonMod, addAnim,
    "Params: animation key\n"
    "Add an animation to the button mod")
{
    pyKey* key;
    if (!PyArg_ParseTuple(args, "O", &key)) {
        PyErr_SetString(PyExc_TypeError, "addAnim expects a plKey");
        return NULL;
    }
    if (!pyKey_Check((PyObject*)key)) {
        PyErr_SetString(PyExc_TypeError, "addAnim expects a plKey");
        return NULL;
    }
    self->fThis->addAnimationKey(*key->fThis);
    Py_RETURN_NONE;
}

PY_METHOD_VA(GUIButtonMod, delAnim,
    "Params: idx\n"
    "Remove an animation from the button mod")
{
    int idx;
    if (!PyArg_ParseTuple(args, "i", &idx)) {
        PyErr_SetString(PyExc_TypeError, "delAnim expects an int");
        return NULL;
    }
    self->fThis->delAnimationKey(idx);
    Py_RETURN_NONE;
}

PY_METHOD_NOARGS(GUIButtonMod, clearAnims,
    "Remove all animation keys from the button mod")
{
    self->fThis->clearAnimationKeys();
    Py_RETURN_NONE;
}

PY_METHOD_VA(GUIButtonMod, addMouseOver,
    "Params: animation key\n"
    "Add a mouse-over animation to the button mod")
{
    pyKey* key;
    if (!PyArg_ParseTuple(args, "O", &key)) {
        PyErr_SetString(PyExc_TypeError, "addMouseOver expects a plKey");
        return NULL;
    }
    if (!pyKey_Check((PyObject*)key)) {
        PyErr_SetString(PyExc_TypeError, "addMouseOver expects a plKey");
        return NULL;
    }
    self->fThis->addMouseOverKey(*key->fThis);
    Py_RETURN_NONE;
}

PY_METHOD_VA(GUIButtonMod, delMouseOver,
    "Params: idx\n"
    "Remove a mouse-over animation from the button mod")
{
    int idx;
    if (!PyArg_ParseTuple(args, "i", &idx)) {
        PyErr_SetString(PyExc_TypeError, "delMouseOver expects an int");
        return NULL;
    }
    self->fThis->delMouseOverKey(idx);
    Py_RETURN_NONE;
}

PY_METHOD_NOARGS(GUIButtonMod, clearMouseOvers,
    "Remove all mouse-over animation keys from the button mod")
{
    self->fThis->clearMouseOverKeys();
    Py_RETURN_NONE;
}

static PyMethodDef pyGUIButtonMod_Methods[] = {
    pyGUIButtonMod_addAnim_method,
    pyGUIButtonMod_delAnim_method,
    pyGUIButtonMod_clearAnims_method,
    pyGUIButtonMod_addMouseOver_method,
    pyGUIButtonMod_delMouseOver_method,
    pyGUIButtonMod_clearMouseOvers_method,
    PY_METHOD_TERMINATOR
};

PY_GETSET_GETTER_DECL(GUIButtonMod, animationKeys) {
    PyObject* list = PyTuple_New(self->fThis->getAnimationKeys().size());
    for (size_t i = 0; i<self->fThis->getAnimationKeys().size(); i++)
        PyTuple_SET_ITEM(list, i, pyPlasma_convert(self->fThis->getAnimationKeys()[i]));
    return list;
}
PY_PROPERTY_SETTER_MSG(GUIButtonMod, animationKeys, "To add animations, use addAnim()")
PY_PROPERTY_GETSET_DECL(GUIButtonMod, animationKeys)

PY_GETSET_GETTER_DECL(GUIButtonMod, mouseOverKeys) {
    PyObject* list = PyTuple_New(self->fThis->getMouseOverKeys().size());
    for (size_t i = 0; i<self->fThis->getMouseOverKeys().size(); i++)
        PyTuple_SET_ITEM(list, i, pyPlasma_convert(self->fThis->getMouseOverKeys()[i]));
    return list;
}
PY_PROPERTY_SETTER_MSG(GUIButtonMod, mouseOverKeys, "To add mouse-over animations, use addMouseOver()")
PY_PROPERTY_GETSET_DECL(GUIButtonMod, mouseOverKeys)

PY_PROPERTY(ST::string, GUIButtonMod, animName, getAnimationName, setAnimationName)
PY_PROPERTY(ST::string, GUIButtonMod, mouseOverAnimName, getMouseOverAnimName, setMouseOverAnimName)
PY_PROPERTY(plKey, GUIButtonMod, draggable, getDraggable, setDraggable)
PY_PROPERTY(int, GUIButtonMod, notifyType, getNotifyType, setNotifyType)

static PyGetSetDef pyGUIButtonMod_GetSet[] = {
    pyGUIButtonMod_animName_getset,
    pyGUIButtonMod_mouseOverAnimName_getset,
    pyGUIButtonMod_draggable_getset,
    pyGUIButtonMod_notifyType_getset,
    pyGUIButtonMod_animationKeys_getset,
    pyGUIButtonMod_mouseOverKeys_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(GUIButtonMod, pfGUIButtonMod, "pfGUIButtonMod wrapper");

PY_PLASMA_TYPE_INIT(GUIButtonMod) {
    pyGUIButtonMod_Type.tp_new = pyGUIButtonMod_new;
    pyGUIButtonMod_Type.tp_methods = pyGUIButtonMod_Methods;
    pyGUIButtonMod_Type.tp_getset = pyGUIButtonMod_GetSet;
    pyGUIButtonMod_Type.tp_base = &pyGUIControlMod_Type;
    if (PyType_Ready(&pyGUIButtonMod_Type) < 0)
        return NULL;

    /* Konstants */
    PY_TYPE_ADD_CONST(GUIButtonMod, "kNotifyOnUp", pfGUIButtonMod::kNotifyOnUp);
    PY_TYPE_ADD_CONST(GUIButtonMod, "kNotifyOnDown", pfGUIButtonMod::kNotifyOnDown);
    PY_TYPE_ADD_CONST(GUIButtonMod, "kNotifyOnUpAndDown", pfGUIButtonMod::kNotifyOnUpAndDown);

    Py_INCREF(&pyGUIButtonMod_Type);
    return (PyObject*)&pyGUIButtonMod_Type;
}

PY_PLASMA_IFC_METHODS(GUIButtonMod, pfGUIButtonMod)

}