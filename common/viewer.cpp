#include <iostream>
#include <algorithm>
#include <QVBoxLayout>
#include "viewer.hpp"
#include "config_dialog.hpp"
using namespace std;

#include "viewer.moc"

void ViewerCameraChangedCallback(void *data, SoSensor *)
{
    Viewer *viewer = (Viewer *)data;
    viewer->_setUpLightPosition();
}

Viewer::Viewer(QWidget *parent, const char *name)
    : SoQtExaminerViewer(parent, name), _conf_dialog(0),
      _default_style_dialog(0)
{
    _light = new SoPointLight;
    _light->ref();
    _root = new SoSeparator;
    _root->ref();
    _dyn_root = new SoSeparator;
    _dyn_root->ref();

    _light_transform.setValue(0, 0, 0);

    _color_points.setValue(1, 1, 1);
    _color_edges.setValue(0.2, 0.2, 0.6);
    _color_faces.setValue(0.2, 0.75, 0.2);
    _point_size = 2;
    _line_width = 1;
    _points_switch_on = true;
    _edges_switch_on = true;
    _faces_switch_on = true;
}

Viewer::~Viewer()
{
    list<ObjData *>::iterator it, it_end;

    _light->unref();
    _root->unref();
    _dyn_root->unref();

    it = _objects.begin();
    it_end = _objects.end();
    for (; it != it_end; it++){
        delete *it;
    }
    _objects.clear();

    it = _dyn_objects.begin();
    it_end = _dyn_objects.end();
    for (; it != it_end; it++){
        delete *it;
    }
    _dyn_objects.clear();
}

#define ViewerAddObjData(listName) \
    lock(); \
\
    list<ObjData *>::iterator it = listName.end(); \
    if (std::find(listName.begin(), it, object) == it){ \
        object->material_points->diffuseColor.setValue(_color_points); \
        object->material_edges->diffuseColor.setValue(_color_edges); \
        object->material_faces->diffuseColor.setValue(_color_faces); \
        object->style_points->pointSize.setValue(_point_size); \
        object->style_edges->lineWidth.setValue(_line_width); \
        if (_points_switch_on) \
            object->sw_points->whichChild = SO_SWITCH_ALL; \
        else \
            object->sw_points->whichChild = SO_SWITCH_NONE; \
        if (_edges_switch_on) \
            object->sw_edges->whichChild = SO_SWITCH_ALL; \
        else \
            object->sw_edges->whichChild = SO_SWITCH_NONE; \
        if (_faces_switch_on) \
            object->sw_faces->whichChild = SO_SWITCH_ALL; \
        else \
            object->sw_faces->whichChild = SO_SWITCH_NONE; \
\
        listName.push_back(object); \
    } \
\
    unlock()

void Viewer::addObjData(ObjData *object)
{
    ViewerAddObjData(_objects);
}

void Viewer::addDynObjData(ObjData *object)
{
    ViewerAddObjData(_dyn_objects);
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

//static void ObjDataButtonCallback(bool pressed, Viewer *, void *cl);
void Viewer::show()
{
    _setUpConfigDialog();

    // set up properly alignment of left side bar to top
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
    _setUpDynSceneGraph();

    SoQtExaminerViewer::setSceneGraph(_root);
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

    _root->addChild(_light);

    it = _objects.begin();
    it_end = _objects.end();
    for (; it != it_end; it++){
        _root->addChild((*it)->sw);
    }

    _root->addChild(_dyn_root);
}
void Viewer::_setUpDynSceneGraph()
{
    list<ObjData *>::iterator it, it_end;

    _dyn_root->removeAllChildren();

    it = _dyn_objects.begin();
    it_end = _dyn_objects.end();
    for (; it != it_end; it++){
        _dyn_root->addChild((*it)->sw);
    }
}

static void ConfigDialogCallback(bool pressed, Viewer *, void *cl);
static void DefaultStyleDialogCallback(bool pressed, Viewer *, void *cl);
void Viewer::_setUpConfigDialog()
{
    _default_style_button = new TogglePushButton(this,
                                    DefaultStyleDialogCallback,
                                    (void *)&_default_style_dialog);
    _conf_button = new TogglePushButton(this, ConfigDialogCallback,
                                        (void *)&_conf_dialog);

    addAppPushButton(_default_style_button);
    addAppPushButton(_conf_button);
}
static void ConfigDialogCallback(bool pressed, Viewer *viewer, void *cl)
{
    ConfigDialog **dialog = (ConfigDialog **)cl;

    if (pressed && *dialog == 0){
        *dialog = new ConfigDialog(viewer);
        (*dialog)->show();
        viewer->connect(*dialog, SIGNAL(finished(int)),
                        viewer, SLOT(offConfigDialog(int)));
    }

    if (!pressed && *dialog != 0){
        delete *dialog;
        *dialog = 0;
    }
}
static void DefaultStyleDialogCallback(bool pressed, Viewer *viewer, void *cl)
{
    DefaultStyleDialog **dialog = (DefaultStyleDialog **)cl;

    if (pressed && *dialog == 0){
        *dialog = new DefaultStyleDialog((QWidget *)viewer, viewer);
        (*dialog)->show();
        viewer->connect(*dialog, SIGNAL(finished(int)),
                        viewer, SLOT(offDefaultStyleDialog(int)));
    }

    if (!pressed && *dialog != 0){
        delete *dialog;
        *dialog = 0;
    }
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

void Viewer::offConfigDialog(int)
{
    _conf_dialog = 0;
    _conf_button->setChecked(false);
}
void Viewer::offDefaultStyleDialog(int)
{
    _default_style_dialog = 0;
    _default_style_button->setChecked(false);
}

void Viewer::clear()
{
    lock();

    std::list<ObjData *>::iterator it, it_end;

    it = _dyn_objects.begin();
    it_end = _dyn_objects.end();
    for (; it != it_end; it++){
        delete *it;
    }
    _dyn_objects.clear();
    
    _setUpDynSceneGraph();
    unlock();
}
