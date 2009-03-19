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

#include <Inventor/nodes/SoSwitch.h>
#include <Inventor/nodes/SoPointLight.h>
#include <QWidget>
#include <Quarter/QuarterWidget.h>

namespace SVT {

namespace Coin3d {

void ViewerCameraChangedCallback(void *data, SoSensor *);

class Viewer : public SIM::Coin3D::Quarter::QuarterWidget {
    SoSwitch *_root;
    SoPointLight *_light;
    SoNode *_scene;
    SbVec3f _light_transform; /*! vector which holds data used for relative
                                  transformation of _light from camera
                                  position */
  public:
    Viewer();
    ~Viewer();

    void setSceneGraph(SoNode *);
    void show();

  private:
    /**
     * Callback which is called when camera position is changed
     */
    friend void ViewerCameraChangedCallback(void *data, SoSensor *);

    void _setUpLightPosition();
};

} /* namespace Coin3d */

} /* namespace SVT */

#endif
