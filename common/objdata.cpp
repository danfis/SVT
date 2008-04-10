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

/*
void ObjData::_setCoords()
{
    if (_num_vertices > 0){
        SoSeparator *sep = new SoSeparator;

        SoCoordinate3 *coords = new SoCoordinate3;
        coords->point = _vertices;
        _root->addChild(coords);

        _root->addChild(sep);
    }
}

void ObjData::_setVertices()
{
    if (_num_vertices > 0){
        //SoSeparator *sep = new SoSeparator;
        SoSwitch *sep = new SoSwitch;
        sep->whichChild = SO_SWITCH_ALL;

        SoDrawStyle *draw_style = new SoDrawStyle;
        draw_style->pointSize = 3;
        sep->addChild(draw_style);

        SoPointSet *points = new SoPointSet;
        points->startIndex = 0;
        points->numPoints = _num_vertices;
        sep->addChild(points);

        _node_vertices = sep;
        _node_vertices->ref();
        _root->addChild(sep);
    }
}

void ObjData::_setEdges()
{
    if (_num_vertices > 0 && _num_edges > 0){
        //SoSeparator *sep = new SoSeparator;
        SoSwitch *sep = new SoSwitch;
        sep->whichChild = SO_SWITCH_ALL;

        SoDrawStyle *draw_style = new SoDrawStyle;
        draw_style->style = SoDrawStyle::LINES;
        draw_style->lineWidth = 1;
        sep->addChild(draw_style);

        SoMaterial *line_material = new SoMaterial;
        line_material->ambientColor.setValue(0, 0, 0);
        line_material->diffuseColor.setValue(0.18, 0.22, 0.6);
        line_material->specularColor.setValue(0, 0, 0);
        line_material->emissiveColor.setValue(0, 0, 0);
        line_material->shininess = 0.01;
        line_material->transparency = 0.5;
        sep->addChild(line_material);

        SoIndexedLineSet *lines = new SoIndexedLineSet;
        lines->coordIndex = _edges;
        sep->addChild(lines);

        _node_edges = sep;
        _node_edges->ref();
        _root->addChild(sep);
    }
}

void ObjData::_setFaces()
{
    if (_num_vertices > 0 && _num_faces > 0){
        // texture
        SoSwitch *sep = new SoSwitch;
        sep->whichChild = SO_SWITCH_ALL;

        SoDrawStyle *draw_style = new SoDrawStyle;
        draw_style->style = SoDrawStyle::FILLED;
        sep->addChild(draw_style);

        SoTexture2 *texture = new SoTexture2;
        texture->filename = "texture.jpg"; // TODO: parametrize this
        texture->model = SoTexture2::MODULATE;
        sep->addChild(texture);

        SoIndexedFaceSet *face = new SoIndexedFaceSet;
        face->coordIndex = _faces;
        sep->addChild(face);

        // non-texure
        SoSwitch *sep2 = new SoSwitch;
        sep2->whichChild = SO_SWITCH_ALL;

        SoDrawStyle *style2 = new SoDrawStyle;
        style2->style = SoDrawStyle::FILLED;
        sep2->addChild(style2);

        SoMaterial *material2 = new SoMaterial;
        material2->diffuseColor.setValue(0.75, 1, 0.41);
        material2->transparency = 0;
        sep2->addChild(material2);

        sep2->addChild(face);

        _node_faces = sep;
        _node_faces->ref();
        _node_faces2 = sep2;
        _node_faces2->ref();
        _root->addChild(sep);
        _root->addChild(sep2);
    }
}

SoNode *ObjData::root()
{
    if (_root == 0){
        _root = new SoSwitch;
        _root->ref();
        _root->whichChild = SO_SWITCH_ALL;

        _setCoords();
        _setVertices();
        _setEdges();
        _setFaces();
    }

    return _root;
}

static void ObjDataButtonCallback(bool pressed, GSRM::Viewer *, void *cl);
void ObjData::addButtons(GSRM::Viewer &viewer)
{
    viewer.addToggleButton(ObjDataButtonCallback, _root);
    viewer.addToggleButton(ObjDataButtonCallback, _node_vertices);
    viewer.addToggleButton(ObjDataButtonCallback, _node_edges);
    viewer.addToggleButton(ObjDataButtonCallback, _node_faces);
    viewer.addToggleButton(ObjDataButtonCallback, _node_faces2);
}
static void ObjDataButtonCallback(bool pressed, GSRM::Viewer *viewer, void *cl)
{
    SoSwitch *sw = (SoSwitch *)cl;

    SoDB::writelock();
    viewer->lock();
    if (pressed){
        sw->whichChild = SO_SWITCH_NONE;
    }else{
        sw->whichChild = SO_SWITCH_ALL;
    }
    viewer->unlock();
    SoDB::writeunlock();
}
*/
