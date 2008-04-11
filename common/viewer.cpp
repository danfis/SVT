#include <iostream>
#include <algorithm>
#include <QVBoxLayout>
#include <QMainWindow>
#include "viewer.hpp"
#include "style_dialog.hpp"
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
}

Viewer::~Viewer()
{
    list<ObjData *>::iterator it, it_end;

    _light->unref();
    _root->unref();

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
    StylePushButton *button;
    list<ObjData *>::iterator it, it_end;

    it = _objects.begin();
    it_end = _objects.end();
    for (; it != it_end; it++){
        button = new StylePushButton(this, *it);
        addAppPushButton(button);
    }

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


void Viewer::_setUpSceneGraph()
{
    list<ObjData *>::iterator it, it_end;

    _root->removeAllChildren();
    _root->addChild(_light);

    it = _objects.begin();
    it_end = _objects.end();
    for (; it != it_end; it++){
        _root->addChild((*it)->sw);
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
