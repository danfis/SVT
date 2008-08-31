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

#ifndef COIN3D_OBJDATA_HPP_
#define COIN3D_OBJDATA_HPP_

#include <Inventor/nodes/SoCoordinate3.h>
#include <Inventor/nodes/SoSwitch.h>
#include <Inventor/nodes/SoPointSet.h>
#include <Inventor/nodes/SoIndexedLineSet.h>
#include <Inventor/nodes/SoIndexedFaceSet.h>
#include <Inventor/nodes/SoDrawStyle.h>
#include <Inventor/nodes/SoMaterial.h>
#include <string>

#include "../parser/parser.h"

namespace SVT {

namespace Coin3d {

/**
 * Class which describes visualisable object by Coin3d library.
 */
class ObjData {
    std::string _name; /*! name of object */

    SoCoordinate3 *coords; /*! coordinates */
    SoPointSet *points; /*! points (holds number of points formed by
                            coordinates) */
    SoIndexedLineSet *edges; /*! edges (indexed according to coordinates)*/
    SoIndexedFaceSet *faces; /*! faces (indexed according to coordinates)*/
    int num_coords, num_points, num_edges, num_faces;

    /*! Switches.
     *  sw holds switch of whole object and sw_... hold switches of each
     *  part of object.
     */
    SoSwitch *sw, *sw_points, *sw_edges, *sw_faces;

    /*! Styles of each part of object */
    SoDrawStyle *style_points, *style_edges, *style_faces;

    /*! Materials of each part of object */
    SoMaterial *material_points, *material_edges, *material_faces;

  public:
    /**
     * Constructor which only inicialize empty attrinutes
     */
    ObjData(svt_obj_t *obj);
    virtual ~ObjData();

    const std::string &name() const { return _name; }

    int numPoints() const { return points->numPoints.getValue(); }
    int numEdges() const { return edges->coordIndex.getNum() / 3; }
    int numFaces() const { return faces->coordIndex.getNum() / 4; }

    bool pointsOn() const
        { return sw_points->whichChild.getValue() == SO_SWITCH_ALL; }
    bool edgesOn() const
        { return sw_edges->whichChild.getValue() == SO_SWITCH_ALL; }
    bool facesOn() const
        { return sw_faces->whichChild.getValue() == SO_SWITCH_ALL; }
    bool allOn() const
        { return sw->whichChild.getValue() == SO_SWITCH_ALL; }

    bool pointsOff() const { return !pointsOn(); }
    bool edgesOff() const { return !edgesOn(); }
    bool facesOff() const { return !facesOn(); }
    bool allOff() const { return !allOn(); }

    float pointSize() const { return style_points->pointSize.getValue(); }
    float edgeWidth() const { return style_edges->lineWidth.getValue(); } 

    void pointColor(float *r, float *g, float *b) const
        { material_points->diffuseColor[0].getValue(*r, *g, *b); }
    float pointColorRed() const { return material_points->diffuseColor[0][0]; }
    float pointColorGreen() const { return material_points->diffuseColor[0][1]; }
    float pointColorBlue() const { return material_points->diffuseColor[0][2]; }

    void edgeColor(float *r, float *g, float *b) const
        { material_edges->diffuseColor[0].getValue(*r, *g, *b); }
    float edgeColorRed() const { return material_edges->diffuseColor[0][0]; }
    float edgeColorGreen() const { return material_edges->diffuseColor[0][1]; }
    float edgeColorBlue() const { return material_edges->diffuseColor[0][2]; }

    void faceColor(float *r, float *g, float *b) const
        { material_faces->diffuseColor[0].getValue(*r, *g, *b); }
    float faceColorRed() const { return material_faces->diffuseColor[0][0]; }
    float faceColorGreen() const { return material_faces->diffuseColor[0][1]; }
    float faceColorBlue() const { return material_faces->diffuseColor[0][2]; }

};

} /* Coin3d */

} /* SVT */
#endif
