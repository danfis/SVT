#include <iostream>
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

void GSRM::Viewer::addToggleButton(ViewerPushButtonCallback callback,
                                   void *closure)
{
    ViewerPushButton *button = new ViewerPushButton(this, callback,
                                                    closure);
    _buttons.push_back(button);
    addAppPushButton(button);
}

SbBool GSRM::Viewer::processSoEvent(const SoEvent *const event)
{
    SbBool ret;

    lock();
    ret = SoQtExaminerViewer::processSoEvent(event);
    unlock();

    return ret;
}
void GSRM::Viewer::actualRedraw(void)
{
    lock();
    SoQtExaminerViewer::actualRedraw();
    unlock();
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

    SoQtExaminerViewer::show();

    _initLight();
    _initCallbacks();
}

void GSRM::Viewer::setSceneGraph(SoNode *root)
{
    _root->removeAllChildren();
    _root->addChild(_light);
    _root->addChild(root);

    SoQtExaminerViewer::setSceneGraph(_root);
    _initLight();
}


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
        z = pos[1]*cos(_light_transform[0]) + pos[2]*sin(_light_transform[0]) +
            pos[1]*cos(_light_transform[1]) + pos[2]*sin(_light_transform[1]);

        x = (1 + _light_transform[2]) * x;
        y = (1 + _light_transform[2]) * y;
        z = (1 + _light_transform[2]) * z;

        pos.setValue(x, y, z);

        lock();
        _light->location.setValue(pos * -100);
        unlock();
    }else{
        SoDB::writelock();
        _light->location.setValue(0,0,0);
        SoDB::writeunlock();
    }
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

void GSRM::Viewer::rightWheelMotion(float val)
{
    _light_transform[2] = val;
    _setUpLightPosition();
}
