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
#include "toggle_push_button.hpp"

class ConfigDialog;

void ViewerCameraChangedCallback(void *data, SoSensor *);

/**
 * Main viewer class based on SoQtExaminerViewer.
 * This class provides functionality of movable light source (which is also
 * moving with camera) and buttons for style configuration of visualised
 * objects.
 */
class Viewer : public QWidget, public SoQtExaminerViewer{
    Q_OBJECT

  protected:
    SbMutex _lock1, _lock2; /*! internal locks for multithreading */

    std::list<ObjData *> _objects; /*! list of objects managed by this
                                       viewer */

    SoSeparator *_root; /*! root of scene graph */
    SoPointLight *_light; /*! main light source */
    SbVec3f _light_transform; /*! vector which holds data used for relative
                                  transformation of _light from camera
                                  position */

    /*! default values: */
    SbColor _color_points, _color_edges, _color_faces;
    float _point_size, _line_width;
    bool _points_switch_on, _edges_switch_on, _faces_switch_on;

    ConfigDialog *_conf_dialog; /*! holds pointer to shown ConfigDialog
                                    or 0 (if no ConfigDialog is shown) */
    TogglePushButton *_conf_button; /*! button using which is possible to
                                        show/hide ConfigDialog */

    int _lockRedraw() { return _lock1.lock(); }
    int _unlockRedraw() { return _lock1.unlock(); }
    int _lockEvent() { return _lock2.lock(); }
    int _unlockEvent() { return _lock2.unlock(); }


    virtual void _initCallbacks();
    virtual void _initLight();
    virtual void _setUpLightPosition();
    virtual void _setUpConfigDialog();
    virtual void _setUpSceneGraph();

    /**
     * Overloaded methods of SoQtExaminerViewer
     */
    virtual SbBool processSoEvent(const SoEvent *const event);
    virtual void actualRedraw(void);
    void leftWheelMotion(float val);
    void bottomWheelMotion(float val);
    void setSceneGraph(SoNode *root){}

    friend class ConfigDialog;
    friend void ViewerCameraChangedCallback(void *data, SoSensor *);
  protected slots:
    /**
     * Slot used by _conf_button and _conf_dialog
     */
    void offConfigDialog(int);

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
     * Set default values by which will be modified all added ObjData
     */
    void setDefaultPointsDiffuseColor(float r, float g, float b)
        { _color_points.setValue(r, g, b); }
    void setDefaultEdgesDiffuseColor(float r, float g, float b)
        { _color_edges.setValue(r, g, b); }
    void setDefaultFacesDiffuseColor(float r, float g, float b)
        { _color_faces.setValue(r, g, b); }
    void setdefaultPointSize(float point_size)
        { _point_size = point_size; }
    void setDefaultLineWidth(float line_width)
        { _line_width = line_width; }
    void setDefaultPointsSwitch(bool on)
        { _points_switch_on = on; }
    void setDefaultEdgesSwitch(bool on)
        { _edges_switch_on = on; }
    void setFacesEdgesSwitch(bool on)
        { _faces_switch_on = on; }

    void show();

    void clear();
    void rebuildSceneGraph()
        { lock(); _setUpSceneGraph(); unlock();}
};
#endif
