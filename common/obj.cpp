/**
 * SVT
 * ----------
 * Copyright (c)2007,2008,2009 Daniel Fiser <danfis (at) danfis (dot) cz>
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

#include "obj.hpp"
#include "functions.hpp"

namespace SVT {

namespace Common {

void Obj::applySettings(const Settings &s)
{
    float r, g, b;

    setAllOn(!s.all_off);

    if (!pointsOffAlreadySet())
        setPointsOn(!s.points_off);
    if (!edgesOffAlreadySet())
        setEdgesOn(!s.edges_off);
    if (!facesOffAlreadySet())
        setFacesOn(!s.faces_off);

    if (!pointSizeAlreadySet()){
        setPointSize(s.point_size);
    }
    setEdgeWidth(s.edge_width);

    // colour elemets if requested
    if (s.colour_points){
        chooseRandomColor(&r, &g, &b);
        setPointColor(r, g, b);
    }else if (!pointColorAlreadySet()){
        r = s.point_color[0];
        g = s.point_color[1];
        b = s.point_color[2];
        setPointColor(r, g, b);
    }

    if (s.colour_edges){
        chooseRandomColor(&r, &g, &b);
        setEdgeColor(r, g, b);
    }else if (!edgeColorAlreadySet()){
        r = s.edge_color[0];
        g = s.edge_color[1];
        b = s.edge_color[2];
        setEdgeColor(r, g, b);
    }

    if (s.colour_faces){
        chooseRandomColor(&r, &g, &b);
        setFaceColor(r, g, b);
    }else if (!faceColorAlreadySet()){
        r = s.face_color[0];
        g = s.face_color[1];
        b = s.face_color[2];
        setFaceColor(r, g, b);
    }
}

}

}
