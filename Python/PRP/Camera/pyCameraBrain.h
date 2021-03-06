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

#ifndef _PYCAMERABRAIN_H
#define _PYCAMERABRAIN_H

#include "PyPlasma.h"

PY_WRAP_PLASMA(CameraBrain, class plCameraBrain)
PY_WRAP_PLASMA(CameraBrain1, class plCameraBrain1)
PY_WRAP_PLASMA(CameraBrain1_Avatar, class plCameraBrain1_Avatar)
PY_WRAP_PLASMA(CameraBrain1_FirstPerson, class plCameraBrain1_FirstPerson)
PY_WRAP_PLASMA(CameraBrain1_Fixed, class plCameraBrain1_Fixed)
PY_WRAP_PLASMA(CameraBrain1_Circle, class plCameraBrain1_Circle)

#endif
