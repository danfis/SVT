#ifndef _OBJDATA_HPP_
#define _OBJDATA_HPP_

#include <Inventor/nodes/SoCoordinate3.h>
#include <Inventor/nodes/SoSwitch.h>
#include <Inventor/nodes/SoPointSet.h>
#include <Inventor/nodes/SoIndexedLineSet.h>
#include <Inventor/nodes/SoIndexedFaceSet.h>
#include <Inventor/nodes/SoDrawStyle.h>
#include <Inventor/nodes/SoMaterial.h>

struct ObjData {
    SoCoordinate3 *coords;
    SoPointSet *points;
    SoIndexedLineSet *edges;
    SoIndexedFaceSet *faces;
    SoSwitch *sw, *sw_points, *sw_edges, *sw_faces;
    SoDrawStyle *style_points, *style_edges, *style_faces;
    SoMaterial *material_points, *material_edges, *material_faces;
    int num_coords, num_points, num_edges, num_faces;

    ObjData();
    virtual ~ObjData();

    void addVertex(float x, float y, float z);
    void addEdge(int from, int to);
    void addFace(int a, int b, int c);
};
#endif
