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

#ifndef COIN3D_OBJDATA_MANAGER_HPP
#define COIN3D_OBJDATA_MANAGER_HPP

#include <Inventor/nodes/SoSwitch.h>
#include <list>

#include "objdata.hpp"

namespace SVT {

namespace Coin3d {

class ObjDataManager {
    std::list<ObjData *> _objs;

    SoSwitch *_root;

  public:
    ObjDataManager();
    ~ObjDataManager();

    SoGroup *root() { return _root; }

    void add(ObjData *obj)
        { _objs.push_back(obj); _root->addChild(obj->root()); }
    void remove(ObjData *obj)
        { _objs.remove(obj); _root->removeChild(obj->root()); }
    void clear();

    void setOn(bool on = true);

    void setPointsOn(bool on = true);
    void setEdgesOn(bool on = true);
    void setFacesOn(bool on = true);

    void setPointSize(float size);
    void setEdgeWidth(float width);

    void setPointColor(float r, float g, float b);
    void setPointColor(float rgb[3])
        { setPointColor(rgb[0], rgb[1], rgb[2]); }
    void setPointColorRed(float v);
    void setPointColorGreen(float v);
    void setPointColorBlue(float v);

    void setEdgeColor(float r, float g, float b);
    void setEdgeColor(float rgb[3])
        { setEdgeColor(rgb[0], rgb[1], rgb[2]); }
    void setEdgeColorRed(float v);
    void setEdgeColorGreen(float v);
    void setEdgeColorBlue(float v);

    void setFaceColor(float r, float g, float b);
    void setFaceColor(float rgb[3])
        { setFaceColor(rgb[0], rgb[1], rgb[2]); }
    void setFaceColorRed(float v);
    void setFaceColorGreen(float v);
    void setFaceColorBlue(float v);
};

} /* Coin3d */

} /* SVT */
#endif
