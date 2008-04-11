#include <iostream>
#include <algorithm>
#include <QVBoxLayout>
#include <QMainWindow>
#include "viewer.hpp"
#include "style_window.hpp"
using namespace std;

void ViewerCameraChangedCallback(void *data, SoSensor *)
{
    Viewer *viewer = (Viewer *)data;
    viewer->_setUpLightPosition();
}

Viewer::Viewer(QWidget *parent, const char *name)
    : SoQtExaminerViewer(parent, name)
{
    _light = new SoPointLight;
    _light->ref();
    _root = new SoSeparator;
    _root->ref();

    _light_transform.setValue(0, 0, 0);


    // style
    _style_points = new SoDrawStyle;
    _style_points->ref();
    _style_points->pointSize = 3;

    _style_edges = new SoDrawStyle;
    _style_edges->ref();
    _style_edges->style = SoDrawStyle::LINES;
    _style_edges->lineWidth = 1;

    _style_faces = new SoDrawStyle;
    _style_faces->ref();
    _style_faces->style = SoDrawStyle::FILLED;

    // material
    _material_points = new SoMaterial;
    _material_points->ref();
    _material_points->ambientColor.setValue(0, 0, 0);
    _material_points->diffuseColor.setValue(1, 1, 1);
    _material_points->specularColor.setValue(0, 0, 0);
    _material_points->emissiveColor.setValue(0, 0, 0);
    _material_points->shininess = 0.2;
    _material_points->transparency = 0;

    _material_edges = new SoMaterial;
    _material_edges->ref();
    _material_edges->ambientColor.setValue(0, 0, 0);
    _material_edges->diffuseColor.setValue(0.18, 0.22, 0.6);
    _material_edges->specularColor.setValue(0, 0, 0);
    _material_edges->emissiveColor.setValue(0, 0, 0);
    _material_edges->shininess = 0.01;
    _material_edges->transparency = 0.5;

    _material_faces = new SoMaterial;
    _material_faces->ref();
    _material_faces->diffuseColor.setValue(0.75, 1, 0.41);
    _material_faces->transparency = 0;
}

Viewer::~Viewer()
{
    list<ObjData *>::iterator it, it_end;

    _light->unref();
    _root->unref();

    _style_points->unref();
    _style_edges->unref();
    _style_faces->unref();
    _material_points->unref();
    _material_edges->unref();
    _material_faces->unref();

    it = _objects.begin();
    it_end = _objects.end();
    for (; it != it_end; it++){
        delete *it;
    }
}


void Viewer::addObjData(ObjData *object)
{
    list<ObjData *>::iterator it = _objects.end();
    if (std::find(_objects.begin(), it, object) == it){
        _objects.push_back(object);
    }
}

void Viewer::addToggleButton(ViewerPushButtonCallback callback,
                                   void *closure)
{
    ViewerPushButton *button = new ViewerPushButton(this, callback,
                                                    closure);
    //_buttons.push_back(button);
    addAppPushButton(button);
}

SbBool Viewer::processSoEvent(const SoEvent *const event)
{
    SbBool ret;

    _lockEvent();
    ret = SoQtExaminerViewer::processSoEvent(event);
    _unlockEvent();

    return ret;
}
void Viewer::actualRedraw(void)
{
    _lockRedraw();
    SoQtExaminerViewer::actualRedraw();
    _unlockRedraw();
}

void Viewer::show()
{
    // set up properly alignment to top
    QWidget *parent = SoQtExaminerViewer::getAppPushButtonParent();
    QLayout *layout;
    if (parent != NULL){
        layout = parent->layout();
        if (layout == NULL){
            layout = new QVBoxLayout;
            parent->setLayout(layout);
        }
        layout->setAlignment(Qt::AlignTop);
    }

    _setUpSceneGraph();

    SoQtExaminerViewer::show();

    _initLight();
    _initCallbacks();
}


// private:
void Viewer::_initLight()
{
    _light->on = true;
    _light->intensity = 1;
    _light->color.setValue(1,1,1);

    _setUpLightPosition();
}

void Viewer::_initCallbacks()
{
    SoCamera *camera = this->getCamera();
    if (camera == NULL){
        DBG("No camera");
        return;
    }
    SoFieldSensor *cam_sensor =
        new SoFieldSensor(ViewerCameraChangedCallback, this);
    cam_sensor->attach(&camera->position);
}

void Viewer::_setUpLightPosition()
{
    SoCamera *cam = this->getCamera();
    SbVec3f pos;
    float x, y, z;

    if (cam != NULL){
        pos = cam->position.getValue();
        x = pos[0];
        y = pos[1];
        z = pos[2];

        x = pos[0]*cos(_light_transform[0]) - pos[2]*sin(_light_transform[0]);
        y = pos[1]*cos(_light_transform[1]) - pos[2]*sin(_light_transform[1]);
        z = pos[2]*cos(_light_transform[0]) + pos[1]*sin(_light_transform[0]) +
            pos[2]*cos(_light_transform[1]) + pos[1]*sin(_light_transform[1]);
        z = z / 2;

        pos.setValue(x * -100, y * -100, z * -100);

        SoDB::writelock();
        lock();
        _light->location.setValue(pos);
        unlock();
        SoDB::writeunlock();
    }else{
        SoDB::writelock();
        lock();
        _light->location.setValue(0,0,0);
        unlock();
        SoDB::writeunlock();
    }
}


SoSwitch *Viewer::_buildObjGraph(ObjData *obj)
{
    SoSwitch *sw, *sw2;

    sw = new SoSwitch;
    sw->whichChild = SO_SWITCH_ALL;

    // coordinates
    sw->addChild(obj->coords);

    // points:
    sw2 = new SoSwitch;
    sw2->whichChild = SO_SWITCH_ALL;

    sw2->addChild(_style_points);
    sw2->addChild(_material_points);
    sw2->addChild(obj->points);

    sw->addChild(sw2);

    // edges:
    sw2 = new SoSwitch;
    sw2->whichChild = SO_SWITCH_ALL;

    sw2->addChild(_style_edges);
    sw2->addChild(_material_edges);
    sw2->addChild(obj->edges);

    sw->addChild(sw2);

    // faces:
    /* texture
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
    */

    // non-texure
    sw2 = new SoSwitch;
    sw2->whichChild = SO_SWITCH_ALL;

    sw2->addChild(_style_faces);
    sw2->addChild(_material_faces);
    sw2->addChild(obj->faces);

    sw->addChild(sw2);

    return sw;
}

void Viewer::_setUpSceneGraph()
{
    list<ObjData *>::iterator it, it_end;

    _root->removeAllChildren();
    _root->addChild(_light);

    it = _objects.begin();
    it_end = _objects.end();
    for (; it != it_end; it++){
        _root->addChild(_buildObjGraph(*it));
    }

    SoQtExaminerViewer::setSceneGraph(_root);
    _initLight();
}

void Viewer::leftWheelMotion(float val)
{
    _light_transform[0] = val;
    _setUpLightPosition();
}

void Viewer::bottomWheelMotion(float val)
{
    _light_transform[1] = val;
    _setUpLightPosition();
}
