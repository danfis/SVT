#ifndef _VIEWER_H_
#define _VIEWER_H_

#include <vector>
#include <Inventor/Qt/viewers/SoQtExaminerViewer.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoPointLight.h>
#include <Inventor/nodes/SoCamera.h>
#include <Inventor/sensors/SoFieldSensor.h>
#include <Inventor/threads/SbMutex.h>

#include "msg.hpp"
#include "viewer_push_button.hpp"

namespace GSRM {

void ViewerCameraChangedCallback(void *data, SoSensor *);

/**
 * Viewer based on SoQtExaminerViewer
 */
class Viewer : public QObject, public SoQtExaminerViewer{
  private:
    SbMutex _lock; /*! internal lock for multithreading */
    std::vector<ViewerPushButton *> _buttons; /*! list of registered buttons */

    SoPointLight *_light;
    SoSeparator *_root;
    SbVec3f _light_transform;

  protected:
    virtual SbBool processSoEvent(const SoEvent *const event);
    virtual void actualRedraw(void);

    virtual void _initCallbacks();
    virtual void _initLight();
    virtual void _setUpLightPosition();

    void leftWheelMotion(float val);
    void bottomWheelMotion(float val);
    void rightWheelMotion(float val);
  public:
    Viewer(QWidget *parent, const char *name = "");
    virtual ~Viewer();

    /**
     * Lock/Unlock viewer
     */
    int lock() { return _lock.lock(); }
    int unlock() { return _lock.unlock(); }

    /**
     * Add button using which is possible to show/hide given SoSeparator
     */
    void addToggleButton(ViewerPushButtonCallback callback,
                         void *closure = NULL);

    virtual void show();
    void setSceneGraph(SoNode *root);

    friend void ViewerCameraChangedCallback(void *data, SoSensor *);
};

}
#endif
