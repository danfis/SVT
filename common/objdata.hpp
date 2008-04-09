#ifndef _OBJDATA_HPP_
#define _OBJDATA_HPP_

#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoSwitch.h>
#include <Inventor/nodes/SoTexture2.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/nodes/SoDrawStyle.h>
#include <Inventor/nodes/SoPointLight.h>
#include <Inventor/nodes/SoCoordinate3.h>
#include <Inventor/nodes/SoPointSet.h>
#include <Inventor/nodes/SoIndexedLineSet.h>
#include <Inventor/nodes/SoIndexedFaceSet.h>

class ObjData {
  private:
    SoSeparator *_root;

    SoMFVec3f _vertices;
    int _num_vertices;

    SoMFInt32 _edges;
    int _num_edges;

    SoMFInt32 _faces;
    int _num_faces;

    void _setCoords();
    void _setVertices();
    void _setEdges();
    void _setFaces();
  public:
    ObjData()
       : _root(0),
         _num_vertices(0),
         _num_edges(0),
         _num_faces(0){}
    virtual ~ObjData();

    void addVertex(float x, float y, float z);
    void addEdge(int from, int to);
    void addFace(int a, int b, int c);

    SoSeparator *root();
};
#endif
