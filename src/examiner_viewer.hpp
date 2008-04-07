#ifndef _EXAMINER_VIEWER_HPP_
#define _EXAMINER_VIEWER_HPP_

#include <Inventor/Qt/viewers/SoQtExaminerViewer.h>
#include <Inventor/nodes/SoPointLight.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoCamera.h>
#include <Inventor/sensors/SoFieldSensor.h>


void visualExaminerCameraChangedCallback(void *data, SoSensor *);

class VisualExaminerViewer : public SoQtExaminerViewer {
    SoPointLight *_light;
    SoSeparator *_root;
    SoSeparator *_scene_graph;
    float _last_x_val;
    float _last_y_val;
    float _last_z_val;

    void _initLight();
    void _initCallbacks();

  protected:
    SoPointLight *getLight() const { return _light; }
    void _setUpLightPosition();

    void leftWheelMotion(float val);
    void bottomWheelMotion(float val);
    void rightWheelMotion(float val);
    friend void visualExaminerCameraChangedCallback(void *data, SoSensor *);

  public:
    VisualExaminerViewer(QWidget *parent = NULL);
    ~VisualExaminerViewer(){}
    void setSceneGraph(SoSeparator *graph_root);
    void show();
};
#endif
