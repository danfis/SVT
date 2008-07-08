/**
 * Coin3dTools
 * ------------
 * Copyright (c)2007 Daniel Fiser <danfis (at) danfis (dot) cz>
 *
 *
 * This file is part of Coin3dTools
 *
 * Coin3dTools is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Coin3dTools is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Coin3dTools.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _OBJDATA_HPP_
#define _OBJDATA_HPP_

#include <Inventor/nodes/SoCoordinate3.h>
#include <Inventor/nodes/SoSwitch.h>
#include <Inventor/nodes/SoPointSet.h>
#include <Inventor/nodes/SoIndexedLineSet.h>
#include <Inventor/nodes/SoIndexedFaceSet.h>
#include <Inventor/nodes/SoDrawStyle.h>
#include <Inventor/nodes/SoMaterial.h>
#include <string>

/**
 * Class which describes visualisable object by Coin3d library.
 * All attributes are public, becuase this should be only object which
 * holds data and do with them not much things.
 */
struct ObjData {
    std::string name; /*! name of object */

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

    /**
     * Constructor which only inicialize empty attrinutes
     */
    ObjData();
    virtual ~ObjData();

    /**
     * Set up name of object.
     */
    void setName(const char *str) { name = str; }

    /**
     * Add one coordinate to object and also incerement number of points
     */
    void addVertex(float x, float y, float z);

    void addEdge(int from, int to);
    void addFace(int a, int b, int c);

    int numPoints() const { return points->numPoints.getValue(); }
    int numEdges() const { return edges->coordIndex.getNum() / 3; }
    int numFaces() const { return faces->coordIndex.getNum() / 4; }
};
#endif
