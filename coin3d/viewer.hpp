/**
 * SVT
 * ----------
 * Copyright (c)2007,2008,2009 Daniel Fiser <danfis (at) danfis (dot) cz>
 *
 *
 * This file is part of SVT
 *
 * SVT is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * SVT is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with SVT. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef COIN3D_VIEWER_HPP
#define COIN3D_VIEWER_HPP

#include <Inventor/Qt/viewers/SoQtExaminerViewer.h>
#include <Inventor/nodes/SoSwitch.h>
#include <Inventor/nodes/SoPointLight.h>
#include <QWidget>

namespace SVT {

namespace Coin3d {

void ViewerCameraChangedCallback(void *data, SoSensor *);



class Viewer : public QWidget, public SoQtExaminerViewer {
    Q_OBJECT

  protected:
    SoSwitch *_root; /*! root of scene graph */

  private:
    SoPointLight *_light; /*! main light source */
    SbVec3f _light_transform; /*! vector which holds data used for relative
                                  transformation of _light from camera
                                  position */

    
    /**
     * Overloaded functions for changing behaviour of left and right wheels
     */
    void leftWheelMotion(float val);
    void bottomWheelMotion(float val);

    /**
     * Callback which is called when camera position is changed
     */
    friend void ViewerCameraChangedCallback(void *data, SoSensor *);

  private slots:
    void _setUpLightPosition();

  signals:
    void setUpLightPosition();

  public:
    Viewer(QWidget *win);
    ~Viewer();

    void setSceneGraph(SoNode *node);

    void show();
};

} /* namespace Coin3d */

} /* namespace SVT */

#endif
