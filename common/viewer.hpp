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
#include "default_style_dialog.hpp"

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
    std::list<ObjData *> _dyn_objects; /*! list of dynamic objects, i.e.
                                          objects which can be removed */

    SoSeparator *_root; /*! root of scene graph */
    SoSeparator *_dyn_root; /*! root of dynamic objects */
    SoPointLight *_light; /*! main light source */
    SbVec3f _light_transform; /*! vector which holds data used for relative
                                  transformation of _light from camera
                                  position */

    /*! default values: */
    SbColor _color_points, _color_edges, _color_faces;
    float _point_size, _line_width;
    bool _switch_on, _points_switch_on, _edges_switch_on, _faces_switch_on;

    int _lockRedraw() { return _lock1.lock(); }
    int _unlockRedraw() { return _lock1.unlock(); }
    int _lockEvent() { return _lock2.lock(); }
    int _unlockEvent() { return _lock2.unlock(); }


    virtual void _initCallbacks();
    virtual void _initLight();
    virtual void _setUpLightPosition();
    virtual void _setUpSceneGraph();
    virtual void _setUpDynSceneGraph(); /*! set up dynamic part of scene
                                            graph */

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
     * Add ObjData object as dynamic object (it means to list of dynamic
     * objects
     */
    void addDynObjData(ObjData *object);

    /**
     * Set default values by which will be modified all added ObjData
     */
    void setDefaultPointsDiffuseColor(float r, float g, float b)
        { lock(); _color_points.setValue(r, g, b); unlock(); }
    void setDefaultPointsDiffuseColorRed(float val)
        { lock(); _color_points[0] = val; unlock(); }
    void setDefaultPointsDiffuseColorGreen(float val)
        { lock(); _color_points[1] = val; unlock(); }
    void setDefaultPointsDiffuseColorBlue(float val)
        { lock(); _color_points[2] = val; unlock(); }
    void defaultPointsDiffuseColor(float *r, float *g, float *b)
        { lock(); _color_points.getValue(*r, *g, *b); unlock(); }

    void setDefaultEdgesDiffuseColor(float r, float g, float b)
        { lock(); _color_edges.setValue(r, g, b); unlock(); }
    void setDefaultEdgesDiffuseColorRed(float val)
        { lock(); _color_edges[0] = val; unlock(); }
    void setDefaultEdgesDiffuseColorGreen(float val)
        { lock(); _color_edges[1] = val; unlock(); }
    void setDefaultEdgesDiffuseColorBlue(float val)
        { lock(); _color_edges[2] = val; unlock(); }
    void defaultEdgesDiffuseColor(float *r, float *g, float *b)
        { lock(); _color_edges.getValue(*r, *g, *b); unlock(); }

    void setDefaultFacesDiffuseColor(float r, float g, float b)
        { lock(); _color_faces.setValue(r, g, b); unlock(); }
    void setDefaultFacesDiffuseColorRed(float val)
        { lock(); _color_faces[0] = val; unlock(); }
    void setDefaultFacesDiffuseColorGreen(float val)
        { lock(); _color_faces[1] = val; unlock(); }
    void setDefaultFacesDiffuseColorBlue(float val)
        { lock(); _color_faces[2] = val; unlock(); }
    void defaultFacesDiffuseColor(float *r, float *g, float *b)
        { lock(); _color_faces.getValue(*r, *g, *b); unlock(); }

    void setDefaultPointSize(float point_size)
        { lock(); _point_size = point_size; unlock(); }
    void defaultPointSize(float *point_size)
        { lock(); *point_size = _point_size; unlock(); }


    void setDefaultLineWidth(float line_width)
        { lock(); _line_width = line_width; unlock(); }
    void defaultLineWidth(float *line_width)
        { lock(); *line_width = _line_width; unlock(); }

    void setDefaultSwitch(bool on)
        { lock(); _switch_on = on; unlock(); }
    void defaultSwitch(bool *on)
        { lock(); *on = _switch_on; unlock(); }
    void setDefaultPointsSwitch(bool on)
        { lock(); _points_switch_on = on; unlock(); }
    void defaultPointsSwitch(bool *on)
        { lock(); *on = _points_switch_on; unlock(); }

    void setDefaultEdgesSwitch(bool on)
        { lock(); _edges_switch_on = on; unlock(); }
    void defaultEdgesSwitch(bool *on)
        { lock(); *on = _edges_switch_on; unlock(); }

    void setDefaultFacesSwitch(bool on)
        { lock(); _faces_switch_on = on; unlock(); }
    void defaultFacesSwitch(bool *on)
        { lock(); *on = _faces_switch_on; unlock(); }

    void show();

    void clear();
    void rebuildSceneGraph()
        { lock(); _setUpDynSceneGraph(); unlock();}
};
#endif
