#include <iostream>
using namespace std;
#include "examiner_viewer.hpp"
#include "msg.hpp"

void visualExaminerCameraChangedCallback(void *data, SoSensor *)
{
    VisualExaminerViewer *viewer = (VisualExaminerViewer *)data;
    viewer->_setUpLightPosition();
}

VisualExaminerViewer::VisualExaminerViewer(QWidget *parent)
        : SoQtExaminerViewer(parent)
{
    _light = new SoPointLight;
    _root = new SoSeparator;
    _scene_graph = NULL;
    _last_x_val = 0;
    _last_y_val = 0;
    _last_z_val = 0;
}

void VisualExaminerViewer::setSceneGraph(SoSeparator *graph_root)
{
    _scene_graph = graph_root;

    _root->removeAllChildren();
    _root->addChild(_light);
    _root->addChild(graph_root);

    SoQtExaminerViewer::setSceneGraph(_root);
    _initLight();
}

void VisualExaminerViewer::show()
{
    SoQtExaminerViewer::show();

    _initLight();
    _initCallbacks();
}

void VisualExaminerViewer::_initLight()
{
    _light->on = true;
    _light->intensity = 1;
    _light->color.setValue(1,1,1);

    _setUpLightPosition();
}

void VisualExaminerViewer::_initCallbacks()
{
    SoCamera *camera = this->getCamera();
    if (camera == NULL){
        DBG("No camera");
        return;
    }
    SoFieldSensor *cam_sensor =
        new SoFieldSensor(visualExaminerCameraChangedCallback, this);
    cam_sensor->attach(&camera->position);
}

void VisualExaminerViewer::_setUpLightPosition()
{
    SoCamera *cam = this->getCamera();

    if (cam != NULL){
        SoDB::writelock();
        _light->location.setValue(cam->position.getValue() * -100);
        SoDB::writeunlock();
    }else{
        SoDB::writelock();
        _light->location.setValue(0,0,0);
        SoDB::writeunlock();
    }
}


void VisualExaminerViewer::leftWheelMotion(float val)
{
    SbVec3f vector = _light->location.getValue();
    float val2 = val - _last_x_val;
    float x = vector[0]*cosf(val2) - vector[2]*sinf(val2);
    float y = vector[1];
    float z = vector[0]*sinf(val2) + vector[2]*cosf(val2);
    
    _last_x_val = val;

    SoDB::writelock();
    _light->location.setValue(x, y, z);
    SoDB::writeunlock();
}

void VisualExaminerViewer::bottomWheelMotion(float val)
{
    SbVec3f vector = _light->location.getValue();
    float val2 = val - _last_y_val;
    float x = vector[0];
    float y = vector[1]*cosf(val2) - vector[2]*sinf(val2);
    float z = vector[1]*sinf(val2) + vector[2]*cosf(val2);
    
    _last_y_val = val;

    SoDB::writelock();
    _light->location.setValue(x, y, z);
    SoDB::writeunlock();
}

void VisualExaminerViewer::rightWheelMotion(float val)
{
    float val2 = val - _last_z_val;
    SbVec3f vector = _light->location.getValue();

    _last_z_val = val;
    _light->location.setValue(vector + vector * val2);
}
