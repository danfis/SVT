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

#include <Inventor/nodes/SoShapeHints.h>
#include "obj.hpp"

namespace SVT {

namespace Coin3d {

Obj::Obj(svt_obj_t *obj)
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

    SoShapeHints *facehints = new SoShapeHints;
    facehints->faceType = SoShapeHints::UNKNOWN_FACE_TYPE;
    sw_faces->addChild(facehints);
    sw_faces->addChild(style_faces);
    sw_faces->addChild(material_faces);
    sw_faces->addChild(faces);

    sw->addChild(sw_faces);


    /* Set up data from obj */
    const svt_point_t *opoints;
    const svt_edge_t *oedges;
    const svt_face_t *ofaces;
    const svt_polyface_t **pfaces;
    const char *oname;
    int *ilist;
    int len, i, start;
    int off;
    const int *ppoints;
    size_t slen;
    const float *color;
    float size;

    opoints = svtObjPoints(obj, &len);
    if (len > 0){
        coords->point.setValues(0, len, opoints);
        num_coords = len;
        num_points = len;
    }

    oedges = svtObjEdges(obj, &len);
    if (len > 0){
        ilist = new int[len * 3];
        for (int i=0; i < len; i++){
            ilist[i * 3] = oedges[i][0];
            ilist[i * 3 + 1] = oedges[i][1];
            ilist[i * 3 + 2] = -1;
        }

        edges->coordIndex.setValues(0, len * 3, ilist);
        num_edges = len;

        delete [] ilist;
    }

    ofaces = svtObjFaces(obj, &len);
    if (len > 0){
        ilist = new int[len * 4];
        for (int i=0; i < len; i++){
            ilist[i * 4] = ofaces[i][0];
            ilist[i * 4 + 1] = ofaces[i][1];
            ilist[i * 4 + 2] = ofaces[i][2];
            ilist[i * 4 + 3] = -1;
        }

        faces->coordIndex.setValues(0, len * 4, ilist);
        num_faces = len;

        delete [] ilist;
    }

    pfaces = svtObjPolyfaces(obj, &len);
    if (len > 0){
        start = num_faces + 4;
        for (i=0; i < len; i++){
            ppoints = svtPolyfacePoints(pfaces[i], &slen);
            faces->coordIndex.setValues(start, slen, ppoints);
            faces->coordIndex.set1Value(start + slen, -1);
            start += slen + 1;
            num_faces++;
        }
    }

    oname = svtObjName(obj);
    if (oname != NULL)
        _name = oname;

    color = svtObjPointColor(obj);
    if (color != NULL){
        _point_color_set = true;
        SbColor c(color[0], color[1], color[2]);
        material_points->diffuseColor.setValue(c);
    }

    color = svtObjEdgeColor(obj);
    if (color != NULL){
        _edge_color_set = true;
        SbColor c(color[0], color[1], color[2]);
        material_edges->diffuseColor.setValue(c);
    }

    color = svtObjFaceColor(obj);
    if (color != NULL){
        _face_color_set = true;
        SbColor c(color[0], color[1], color[2]);
        material_faces->diffuseColor.setValue(c);
    }

    size = svtObjPointSize(obj);
    if (size > 0.f){
        _point_size_set = true;
        style_points->pointSize.setValue(size);
    }
    size = svtObjEdgeWidth(obj);
    if (size > 0.f){
        _edge_width_set = true;
        style_edges->lineWidth.setValue(size);
    }

    off = svtObjPointsOff(obj);
    if (off >= 0){
        setPointsOn(!off);
        _points_off_set = true;
    }

    off = svtObjEdgesOff(obj);
    if (off >= 0){
        setEdgesOn(!off);
        _edges_off_set = true;
    }

    off = svtObjFacesOff(obj);
    if (off >= 0){
        setFacesOn(!off);
        _faces_off_set = true;
    }
}

Obj::~Obj()
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


void Obj::setAllOn(bool on)
{
    if (on){
        sw->whichChild = SO_SWITCH_ALL;
    }else{
        sw->whichChild = SO_SWITCH_NONE;
    }
}


void Obj::setPointsOn(bool on)
{
    if (on){
        sw_points->whichChild = SO_SWITCH_ALL;
    }else{
        sw_points->whichChild = SO_SWITCH_NONE;
    }
}

void Obj::setEdgesOn(bool on)
{
    if (on){
        sw_edges->whichChild = SO_SWITCH_ALL;
    }else{
        sw_edges->whichChild = SO_SWITCH_NONE;
    }
}

void Obj::setFacesOn(bool on)
{
    if (on){
        sw_faces->whichChild = SO_SWITCH_ALL;
    }else{
        sw_faces->whichChild = SO_SWITCH_NONE;
    }
}


void Obj::setPointSize(float size)
{
    style_points->pointSize.setValue(size);
}

void Obj::setEdgeWidth(float width)
{
    style_edges->lineWidth.setValue(width);
}


void Obj::setPointColor(float r, float g, float b)
{
    _point_color_set = true;
    SbColor c(r, g, b);
    material_points->diffuseColor.setValue(c);
}

void Obj::setEdgeColor(float r, float g, float b)
{
    _edge_color_set = true;
    SbColor c(r, g, b);
    material_edges->diffuseColor.setValue(c);
}

void Obj::setFaceColor(float r, float g, float b)
{
    _face_color_set = true;
    SbColor c(r, g, b);
    material_faces->diffuseColor.setValue(c);
}

} /* Coin3d */

} /* SVT */
