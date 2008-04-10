#ifndef _OBJDATA_HPP_
#define _OBJDATA_HPP_

#include <Inventor/nodes/SoCoordinate3.h>
#include <Inventor/nodes/SoPointSet.h>
#include <Inventor/nodes/SoIndexedLineSet.h>
#include <Inventor/nodes/SoIndexedFaceSet.h>

struct ObjData {
    SoCoordinate3 *coords;
    SoPointSet *points;
    SoIndexedLineSet *edges;
    SoIndexedFaceSet *faces;
    int num_coords, num_points, num_edges, num_faces;

    ObjData();
    virtual ~ObjData();

    void addVertex(float x, float y, float z);
    void addEdge(int from, int to);
    void addFace(int a, int b, int c);
};
#endif
