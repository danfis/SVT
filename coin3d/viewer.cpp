/**
 * SVT
 * ----------
 * Copyright (c)2007,2008 Daniel Fiser <danfis (at) danfis (dot) cz>
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

#include <Inventor/nodes/SoCamera.h>
#include <Inventor/sensors/SoFieldSensor.h>
#include "viewer.hpp"
#include "../common/msg.hpp"


#include "viewer.moc"

namespace SVT {

namespace Coin3d {

void ViewerCameraChangedCallback(void *data, SoSensor *)
{
    Viewer *viewer = (Viewer *)data;
    viewer->_setUpLightPosition();
}

Viewer::Viewer(QWidget *win)
    : QWidget(0), SoQtExaminerViewer(win)
{
    SoDB::init();

    _root = new SoSwitch;
    _root->ref();
    _root->whichChild = SO_SWITCH_ALL;

    _light = new SoPointLight;
    _light->ref();
    _light->on = true;
    _light->intensity = 1;
    _light->color.setValue(1,1,1);
    _root->addChild(_light);
    _light_transform.setValue(0, 0, 0);
    connect(this, SIGNAL(setUpLightPosition()),
            this, SLOT(_setUpLightPosition()));
}

Viewer::~Viewer()
{
    _light->unref();
    _root->unref();
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

        _light->location.setValue(pos);
    }else{
        _light->location.setValue(0,0,0);
    }
}

void Viewer::leftWheelMotion(float val)
{
    _light_transform[0] = val;
    emit setUpLightPosition();
}

void Viewer::bottomWheelMotion(float val)
{
    _light_transform[1] = val;
    emit setUpLightPosition();
}

void Viewer::setSceneGraph(SoNode *node)
{
    _root->addChild(node);
    SoQtExaminerViewer::setSceneGraph(_root);
}

void Viewer::show()
{
    SoQtExaminerViewer::show();

    SoCamera *camera = this->getCamera();
    if (camera != NULL){
        SoFieldSensor *cam_sensor =
            new SoFieldSensor(ViewerCameraChangedCallback, this);
        cam_sensor->attach(&camera->position);
    }

    viewAll();

    emit setUpLightPosition();
}

} /* namespace Coin3d */

} /* namespace SVT */
