#include <iostream>
#include <Inventor/Qt/SoQt.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoCoordinate3.h>
#include <Inventor/nodes/SoFaceSet.h>
#include <Inventor/nodes/SoIndexedFaceSet.h>
#include <Inventor/nodes/SoPointSet.h>
#include <Inventor/nodes/SoIndexedLineSet.h>
#include <Inventor/nodes/SoDrawStyle.h>
#include <Inventor/nodes/SoDirectionalLight.h>
#include <Inventor/nodes/SoPointLight.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/nodes/SoTexture2.h>
#include <Inventor/nodes/SoLightModel.h>
#include <Inventor/nodes/SoCamera.h>
#include <Inventor/nodes/SoFrustumCamera.h>
#include <Inventor/nodes/SoOrthographicCamera.h>
#include <Inventor/sensors/SoFieldSensor.h>
#include <Inventor/Qt/viewers/SoQtExaminerViewer.h>
#include <Inventor/nodes/SoSwitch.h>
using namespace std;

#include "viewer.hpp"
#include "msg.hpp"

#define MAX_VERTICES 30000
#define MAX_EDGES 300000
#define MAX_FACES 300000
int num_vertices;
static float vertices[MAX_VERTICES][3];
int num_edges;
static int edges[MAX_EDGES * 3];
int num_faces;
static int faces[MAX_FACES * 4];
SoPointLight *light;
SoDirectionalLight *light2;


void callback(bool pressed, GSRM::Viewer *viewer, void *cl)
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
void readData(std::istream &in)
{
    float x, y, z;
    int a, b, c;
    int cur = 0;

    DBG("Start reading.");

    cin >> num_vertices;
    cin >> num_edges;
    cin >> num_faces;

    for (cur = 0; cur < num_vertices; cur++){
        cin >> x;
        cin >> y;
        cin >> z;
        if (!cin.good()) break;

        vertices[cur][0] = x;
        vertices[cur][1] = y;
        vertices[cur][2] = z;
    }
    if (cur != num_vertices){
        ERR("num vertices: " << num_vertices << ", found: " << cur);
        exit(-1);
    }

    for (cur = 0; cur < num_edges; cur++){
        cin >> a;
        cin >> b;
        if (!cin.good()) break;

        edges[cur*3] = a;
        edges[cur*3 + 1] = b;
        edges[cur*3 + 2] = -1;
    }
    if (cur != num_edges){
        ERR("num edges: " << num_edges << ", found: " << cur);
        exit(-1);
    }

    for (cur = 0; cur < num_faces; cur++){
        cin >> a;
        cin >> b;
        cin >> c;
        if (!cin.good()) break;

        faces[cur*4] = a;
        faces[cur*4 + 1] = b;
        faces[cur*4 + 2] = c;
        faces[cur*4 + 3] = -1;
    }
    if (cur != num_faces){
        ERR("num faces: " << num_faces << ", found: " << cur);
        exit(-1);
    }
    
    DBG("End reading.");


    DBG("Num vertices: " << num_vertices);
    DBG("Num edges:    " << num_edges);
    DBG("Num faces:    " << num_faces);
}


// Callback that reports whenever the viewer's position changes.
/*
static void cameraChangedCB(void *data, SoSensor *)
{
   SoCamera *viewerCamera = (SoCamera *)data;

   SoDB::writelock();
   SbVec3f cameraPosition = viewerCamera->position.getValue();
   light->location.setValue(cameraPosition * -100);
   SoDB::writeunlock();
}
*/

static void setCoords(SoGroup *sep)
{
    SoCoordinate3 *coords = new SoCoordinate3;
    coords->point.setValues(0, num_vertices, vertices);
    sep->addChild(coords);
}

static void setVertices(SoGroup *sep)
{
    SoDrawStyle *draw_style = new SoDrawStyle;
    draw_style->pointSize = 3;
    sep->addChild(draw_style);

    SoPointSet *points = new SoPointSet;
    points->numPoints = num_vertices;
    sep->addChild(points);
}

static void setEdges(SoGroup *sep)
{
    SoDrawStyle *draw_style_lines = new SoDrawStyle;
    draw_style_lines->style = SoDrawStyle::LINES;
    draw_style_lines->lineWidth = 2;
    sep->addChild(draw_style_lines);

    SoMaterial *line_material = new SoMaterial;
    line_material->diffuseColor.setValue(0.58, 0.62, 1);
    sep->addChild(line_material);

    SoIndexedLineSet *lines = new SoIndexedLineSet;
    lines->coordIndex.setValues(0, num_edges * 3, edges);
    sep->addChild(lines);
}

static void setFaces(SoGroup *sep, GSRM::Viewer *viewer)
{
    /*
    SoDrawStyle *style = new SoDrawStyle;
    style->style = SoDrawStyle::FILLED;
    sep->addChild(style);

    SoMaterial *material2 = new SoMaterial;
    material2->diffuseColor.setValue(0.75, 1, 0.41);
    material2->transparency = 0;
    sep->addChild(material2);
    */

    SoTexture2 *texture = new SoTexture2;
    texture->filename = "texture.jpg";
    texture->model = SoTexture2::MODULATE;
    sep->addChild(texture);

    SoLightModel *light_model = new SoLightModel;
    light_model->model = SoLightModel::PHONG;
    sep->addChild(light_model);

    //SoDirectionalLight *light = new SoDirectionalLight;
    //SoPointLight *light = new SoPointLight;
    light = new SoPointLight;
    light->on = true;
    light->intensity = 1;
    light->color.setValue(1, 1, 1);
    //light->direction.setValue(0, 0, 1);
    //light->location.setValue(1, 0, 0);
    sep->addChild(light);

    SoIndexedFaceSet *face = new SoIndexedFaceSet;
    face->coordIndex.setValues(0, num_faces * 4, faces);
    sep->addChild(face);
}

int main(int argc, char *argv[])
{
    QWidget *mainwin;
    GSRM::Viewer *viewer;
    SoSeparator *root;
    SoSwitch *sw;


    readData(cin);

    mainwin = SoQt::init(argc, argv, argv[0]);
    if (mainwin == NULL){
        ERR("Can't create main window");
        exit(1);
    }

    root = new SoSeparator;
    root->ref();



    viewer = new GSRM::Viewer(mainwin);
    viewer->setSceneGraph(root);

    sw = new SoSwitch;
    sw->whichChild = SO_SWITCH_ALL;
    //viewer->addToggleButton(callback, sw);
    root->addChild(sw);
    setCoords(sw);

    sw = new SoSwitch;
    sw->whichChild = SO_SWITCH_ALL;
    viewer->addToggleButton(callback, sw);
    root->addChild(sw);
    setVertices(sw);

    sw = new SoSwitch;
    sw->whichChild = SO_SWITCH_ALL;
    viewer->addToggleButton(callback, sw);
    root->addChild(sw);
    setEdges(sw);

    sw = new SoSwitch;
    sw->whichChild = SO_SWITCH_ALL;
    viewer->addToggleButton(callback, sw);
    root->addChild(sw);
    setFaces(sw, viewer);

    viewer->show();


    // Pop up the main window.
    SoQt::show(mainwin);

    SoQt::mainLoop();
    root->unref();

    return 0;
}
