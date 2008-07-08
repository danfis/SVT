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

#include "objdata.hpp"
#include "msg.hpp"

ObjData::ObjData()
    : num_coords(0), num_points(0), num_edges(0), num_faces(0)
{
    coords = new SoCoordinate3;
    coords->ref();
    coords->point.deleteValues(0);
    points = new SoPointSet;
    points->ref();
    edges = new SoIndexedLineSet;
    edges->ref();
    edges->coordIndex.deleteValues(0);
    faces = new SoIndexedFaceSet;
    faces->ref();
    faces->coordIndex.deleteValues(0);

    // style
    style_points = new SoDrawStyle;
    style_points->ref();
    //style_points->pointSize = 3;

    style_edges = new SoDrawStyle;
    style_edges->ref();
    style_edges->style = SoDrawStyle::LINES;
    //style_edges->lineWidth = 1;

    style_faces = new SoDrawStyle;
    style_faces->ref();
    style_faces->style = SoDrawStyle::FILLED;

    // material
    material_points = new SoMaterial;
    material_points->ref();
    /*
    material_points->ambientColor.setValue(0, 0, 0);
    material_points->diffuseColor.setValue(1, 1, 1);
    material_points->specularColor.setValue(0, 0, 0);
    material_points->emissiveColor.setValue(0, 0, 0);
    material_points->shininess = 0.2;
    material_points->transparency = 0;
    */

    material_edges = new SoMaterial;
    material_edges->ref();
    /*
    material_edges->ambientColor.setValue(0, 0, 0);
    material_edges->diffuseColor.setValue(0.18, 0.22, 0.6);
    material_edges->specularColor.setValue(0, 0, 0);
    material_edges->emissiveColor.setValue(0, 0, 0);
    material_edges->shininess = 0.01;
    material_edges->transparency = 0.5;
    */

    material_faces = new SoMaterial;
    material_faces->ref();
    /*
    material_faces->diffuseColor.setValue(0.75, 1, 0.41);
    material_faces->transparency = 0;
    */

    sw = new SoSwitch;
    sw->ref();
    sw->whichChild = SO_SWITCH_ALL;

    // coordinates
    sw->addChild(coords);

    // points:
    sw_points = new SoSwitch;
    sw_points->ref();
    sw_points->whichChild = SO_SWITCH_ALL;

    sw_points->addChild(style_points);
    sw_points->addChild(material_points);
    sw_points->addChild(points);

    sw->addChild(sw_points);

    // edges:
    sw_edges = new SoSwitch;
    sw_edges->ref();
    sw_edges->whichChild = SO_SWITCH_ALL;

    sw_edges->addChild(style_edges);
    sw_edges->addChild(material_edges);
    sw_edges->addChild(edges);

    sw->addChild(sw_edges);

    // faces:
    sw_faces = new SoSwitch;
    sw_faces->ref();
    sw_faces->whichChild = SO_SWITCH_ALL;

    sw_faces->addChild(style_faces);
    sw_faces->addChild(material_faces);
    sw_faces->addChild(faces);

    sw->addChild(sw_faces);
}

ObjData::~ObjData()
{
    if (coords != 0)
        coords->unref();
    if (points != 0)
        points->unref();
    if (edges != 0)
        edges->unref();
    if (faces != 0)
        faces->unref();

    if (style_points != 0)
        style_points->unref();
    if (style_edges != 0)
        style_edges->unref();
    if (style_faces != 0)
        style_faces->unref();

    if (material_points != 0)
        material_points->unref();
    if (material_edges != 0)
        material_edges->unref();
    if (material_faces != 0)
        material_faces->unref();

    if (sw != 0)
        sw->unref();
    if (sw_points != 0)
        sw_points->unref();
    if (sw_edges != 0)
        sw_edges->unref();
    if (sw_faces != 0)
        sw_faces->unref();
}

void ObjData::addVertex(float x, float y, float z)
{
    coords->point.insertSpace(num_coords, 1);
    coords->point.set1Value(num_coords, x, y, z);
    num_coords++;
    num_points++;

    points->numPoints = num_points;
}

void ObjData::addEdge(int from, int to)
{
    edges->coordIndex.insertSpace(num_edges * 3, 3);
    edges->coordIndex.set1Value(num_edges * 3, from);
    edges->coordIndex.set1Value(num_edges * 3 + 1, to);
    edges->coordIndex.set1Value(num_edges * 3 + 2, -1);
    num_edges++;
}

void ObjData::addFace(int a, int b, int c)
{
    faces->coordIndex.insertSpace(num_faces * 4, 4);
    faces->coordIndex.set1Value(num_faces * 4, a);
    faces->coordIndex.set1Value(num_faces * 4 + 1, b);
    faces->coordIndex.set1Value(num_faces * 4 + 2, c);
    faces->coordIndex.set1Value(num_faces * 4 + 3, -1);
    num_faces++;
}

