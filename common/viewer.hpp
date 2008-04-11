#ifndef _VIEWER_H_
#define _VIEWER_H_

#include <list>
#include <Inventor/Qt/viewers/SoQtExaminerViewer.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoPointLight.h>
#include <Inventor/nodes/SoCamera.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/nodes/SoSwitch.h>
#include <Inventor/nodes/SoDrawStyle.h>
#include <Inventor/sensors/SoFieldSensor.h>
#include <Inventor/threads/SbMutex.h>
#include <QDockWidget>

#include "msg.hpp"
#include "objdata.hpp"
#include "viewer_push_button.hpp"

void ViewerCameraChangedCallback(void *data, SoSensor *);

/**
 * Vewer based on SoQtExaminerViewer
 */
class Viewer : public QWidget, public SoQtExaminerViewer{
  private:
    SbMutex _lock1, _lock2; /*! internal locks for multithreading */

    std::list<ObjData *> _objects; /*! list of objects managed by this
                                       viewer */

    SoPointLight *_light;
    SoSeparator *_root;
    SoDrawStyle *_style_points, *_style_edges, *_style_faces;
    SoMaterial *_material_points, *_material_edges, *_material_faces;
    SbVec3f _light_transform;

  protected:
    int _lockRedraw() { return _lock1.lock(); }
    int _unlockRedraw() { return _lock1.unlock(); }
    int _lockEvent() { return _lock2.lock(); }
    int _unlockEvent() { return _lock2.unlock(); }

    virtual SbBool processSoEvent(const SoEvent *const event);
    virtual void actualRedraw(void);

    virtual void _initCallbacks();
    virtual void _initLight();
    virtual void _setUpLightPosition();

    SoSwitch *_buildObjGraph(ObjData *);
    virtual void _setUpSceneGraph();

    void leftWheelMotion(float val);
    void bottomWheelMotion(float val);

    void setSceneGraph(SoNode *root){}
  public:
    Viewer(QWidget *parent, const char *name = "");
    virtual ~Viewer();

    /**
     * Lock/Unlock viewer
     */
    bool lock() { return _lockRedraw() == 0 && _lockEvent() == 0; }
    bool unlock() { return _unlockRedraw() == 0 && _unlockEvent() == 0; }

    /**
     * Add ObjData object to viewer to manage it
     */
    void addObjData(ObjData *object);

    /**
     * Add button using which is possible to show/hide given SoSeparator
     */
    void addToggleButton(ViewerPushButtonCallback callback,
                         void *closure = NULL);

    virtual void show();

    friend void ViewerCameraChangedCallback(void *data, SoSensor *);
};
#endif
