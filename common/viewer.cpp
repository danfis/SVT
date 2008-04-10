#include <iostream>
#include <algorithm>
#include <QVBoxLayout>
#include "viewer.hpp"
using namespace std;

void GSRM::ViewerCameraChangedCallback(void *data, SoSensor *)
{
    GSRM::Viewer *viewer = (GSRM::Viewer *)data;
    viewer->_setUpLightPosition();
}

GSRM::Viewer::Viewer(QWidget *parent, const char *name)
    : SoQtExaminerViewer(parent, name)
{
    _light = new SoPointLight;
    _light->ref();
    _root = new SoSeparator;
    _root->ref();

    _light_transform.setValue(0, 0, 0);
}

GSRM::Viewer::~Viewer()
{
    _light->unref();
    _root->unref();
}

void GSRM::Viewer::addObjData(ObjData *object)
{
    list<ObjData *>::iterator it = _objects.end();
    if (find(_objects.begin(), it, object) == it){
        _objects.push_back(object);
    }
}

void GSRM::Viewer::addToggleButton(ViewerPushButtonCallback callback,
                                   void *closure)
{
    ViewerPushButton *button = new ViewerPushButton(this, callback,
                                                    closure);
    //_buttons.push_back(button);
    addAppPushButton(button);
}

SbBool GSRM::Viewer::processSoEvent(const SoEvent *const event)
{
    SbBool ret;

    _lockEvent();
    ret = SoQtExaminerViewer::processSoEvent(event);
    _unlockEvent();

    return ret;
}
void GSRM::Viewer::actualRedraw(void)
{
    _lockRedraw();
    SoQtExaminerViewer::actualRedraw();
    _unlockRedraw();
}

void GSRM::Viewer::show()
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

/*
void GSRM::Viewer::setSceneGraph(SoNode *root)
{
    _root->removeAllChildren();
    _root->addChild(_light);
    _root->addChild(root);

    SoQtExaminerViewer::setSceneGraph(_root);
    _initLight();
}
*/


// private:
void GSRM::Viewer::_initLight()
{
    _light->on = true;
    _light->intensity = 1;
    _light->color.setValue(1,1,1);

    _setUpLightPosition();
}

void GSRM::Viewer::_initCallbacks()
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

void GSRM::Viewer::_setUpLightPosition()
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


SoSwitch *GSRM::Viewer::_buildObjGraph(ObjData *obj)
{
    SoSwitch *sw, *sw2;
    SoDrawStyle *style;
    SoMaterial *material;

    sw = new SoSwitch;
    sw->whichChild = SO_SWITCH_ALL;

    // coordinates
    sw->addChild(obj->coords);

    // points:
    sw2 = new SoSwitch;
    sw2->whichChild = SO_SWITCH_ALL;

    style = new SoDrawStyle;
    style->pointSize = 3;
    sw2->addChild(style);

    sw2->addChild(obj->points);

    sw->addChild(sw2);

    // edges:
    sw2 = new SoSwitch;
    sw2->whichChild = SO_SWITCH_ALL;

    style = new SoDrawStyle;
    style->style = SoDrawStyle::LINES;
    style->lineWidth = 1;
    sw2->addChild(style);

    material = new SoMaterial;
    material->ambientColor.setValue(0, 0, 0);
    material->diffuseColor.setValue(0.18, 0.22, 0.6);
    material->specularColor.setValue(0, 0, 0);
    material->emissiveColor.setValue(0, 0, 0);
    material->shininess = 0.01;
    material->transparency = 0.5;
    sw2->addChild(material);

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

    style = new SoDrawStyle;
    style->style = SoDrawStyle::FILLED;
    sw2->addChild(style);

    material = new SoMaterial;
    material->diffuseColor.setValue(0.75, 1, 0.41);
    material->transparency = 0;
    sw2->addChild(material);

    sw2->addChild(obj->faces);

    sw->addChild(sw2);

    return sw;
}

void GSRM::Viewer::_setUpSceneGraph()
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

void GSRM::Viewer::leftWheelMotion(float val)
{
    _light_transform[0] = val;
    _setUpLightPosition();
}

void GSRM::Viewer::bottomWheelMotion(float val)
{
    _light_transform[1] = val;
    _setUpLightPosition();
}
