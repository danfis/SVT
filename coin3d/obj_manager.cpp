/**
 * SVT
 * ----------
 * Copyright (c)2007,2008 Daniel Fiser <danfis (at) danfis (dot) cz>
 *
 *
 * This file is part of SVT
 *
 * SVT is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * SVT is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with SVT. If not, see <http://www.gnu.org/licenses/>.
 */

#include "obj_manager.hpp"

#define forAll \
    std::list<Obj *>::iterator it, it_end; \
\
    it = _objs.begin(); \
    it_end = _objs.end(); \
    for (; it != it_end; ++it)

namespace SVT {

namespace Coin3d {

ObjManager::ObjManager()
{
    SoDB::init();
    _root = new SoSwitch;
    _root->ref();
    _root->whichChild = SO_SWITCH_ALL;
}

ObjManager::~ObjManager()
{
    clear();
    _root->unref();
}

void ObjManager::clear()
{
    forAll{
        delete *it;
    }
    _objs.clear();
    _root->removeAllChildren();
}

void ObjManager::setOn(bool on)
{
    if (on){
        _root->whichChild = SO_SWITCH_ALL;
    }else{
        _root->whichChild = SO_SWITCH_NONE;
    }
}

void ObjManager::setPointsOn(bool on)
{
    forAll{
        (*it)->setPointsOn(on);
    }
}

void ObjManager::setEdgesOn(bool on)
{
    forAll{
        (*it)->setEdgesOn(on);
    }
}

void ObjManager::setFacesOn(bool on)
{
    forAll{
        (*it)->setFacesOn(on);
    }
}

void ObjManager::setPointSize(float size)
{
    forAll{
        (*it)->setPointSize(size);
    }
}

void ObjManager::setEdgeWidth(float width)
{
    forAll{
        (*it)->setEdgeWidth(width);
    }
}

void ObjManager::setPointColor(float r, float g, float b)
{
    forAll{
        (*it)->setPointColor(r, g, b);
    }
}

void ObjManager::setPointColorRed(float v)
{
    forAll{
        (*it)->setPointColorRed(v);
    }
}

void ObjManager::setPointColorGreen(float v)
{
    forAll{
        (*it)->setPointColorGreen(v);
    }
}

void ObjManager::setPointColorBlue(float v)
{
    forAll{
        (*it)->setPointColorBlue(v);
    }
}

void ObjManager::setEdgeColor(float r, float g, float b)
{
    forAll{
        (*it)->setEdgeColor(r, g, b);
    }
}

void ObjManager::setEdgeColorRed(float v)
{
    forAll{
        (*it)->setEdgeColorRed(v);
    }
}

void ObjManager::setEdgeColorGreen(float v)
{
    forAll{
        (*it)->setEdgeColorGreen(v);
    }
}

void ObjManager::setEdgeColorBlue(float v)
{
    forAll{
        (*it)->setEdgeColorBlue(v);
    }
}

void ObjManager::setFaceColor(float r, float g, float b)
{
    forAll{
        (*it)->setFaceColor(r, g, b);
    }
}

void ObjManager::setFaceColorRed(float v)
{
    forAll{
        (*it)->setFaceColorRed(v);
    }
}

void ObjManager::setFaceColorGreen(float v)
{
    forAll{
        (*it)->setFaceColorGreen(v);
    }
}

void ObjManager::setFaceColorBlue(float v)
{
    forAll{
        (*it)->setFaceColorBlue(v);
    }
}

} /* Coin3d */

} /* SVT */
