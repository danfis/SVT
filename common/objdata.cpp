#include "objdata.hpp"
#include "msg.hpp"

ObjData::~ObjData()
{
    if (_root != 0)
        _root->unref();

    if (_node_vertices != 0)
        _node_vertices->unref();
    if (_node_edges != 0)
        _node_edges->unref();
    if (_node_faces != 0)
        _node_faces->unref();
    if (_node_faces2 != 0)
        _node_faces2->unref();
}

void ObjData::addVertex(float x, float y, float z)
{
    _vertices.insertSpace(_num_vertices, 1);
    _vertices.set1Value(_num_vertices, x, y, z);
    _num_vertices++;
}

void ObjData::addEdge(int from, int to)
{
    _edges.insertSpace(_num_edges * 3, 3);
    _edges.set1Value(_num_edges * 3, from);
    _edges.set1Value(_num_edges * 3 + 1, to);
    _edges.set1Value(_num_edges * 3 + 2, -1);
    _num_edges++;
}

void ObjData::addFace(int a, int b, int c)
{
    _faces.insertSpace(_num_faces * 4, 4);
    _faces.set1Value(_num_faces * 4, a);
    _faces.set1Value(_num_faces * 4 + 1, b);
    _faces.set1Value(_num_faces * 4 + 2, c);
    _faces.set1Value(_num_faces * 4 + 3, -1);
    _num_faces++;
}

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
        draw_style->lineWidth = 2;
        sep->addChild(draw_style);

        SoMaterial *line_material = new SoMaterial;
        line_material->diffuseColor.setValue(0.58, 0.62, 1);
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
