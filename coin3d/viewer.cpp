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
#include <Inventor/nodes/SoDirectionalLight.h>
#include <Inventor/sensors/SoFieldSensor.h>
#include <Inventor/events/SoEvent.h>
#include <Inventor/events/SoMouseButtonEvent.h>
#include <Inventor/SoEventManager.h>
#include <Inventor/scxml/SoScXMLStateMachine.h>
#include "viewer.hpp"
#include "common/msg.hpp"
using namespace SIM::Coin3D::Quarter;


#include "viewer.moc"

namespace SVT {

namespace Coin3d {



/**
 * Callback called everytime camera changed.
 */
static void cameraChangedCB(void *data, SoSensor *)
{
    Viewer *viewer = (Viewer *)data;
    viewer->updateLight();
}


Viewer::Viewer()
    : QuarterWidget(), _scene_dyn_clear(false), _disabled_rotation(false)
{
    //setNavigationModeFile(QUrl("coin:/scxml/navigation/examiner.xml"));
    setNavigationModeFile();

    _root = new SoSwitch;
    _root->ref();
    _root->whichChild = SO_SWITCH_ALL;

    _light = new SoDirectionalLight;
    _light->ref();
    _light->on = true;
    _light->intensity = 1.;
    _light->color.setValue(1., 1., 1.);
    _light->direction.setValue(0, 0, 1);

    _root->addChild(_light);
    _root->addChild(_scene.root());
    _root->addChild(_scene_dyn.root());
    QuarterWidget::setSceneGraph(_root);


    SoCamera *cam = this->getSoEventManager()->getCamera();
    if (cam != NULL){
        SoFieldSensor *cam_sensor = new SoFieldSensor(cameraChangedCB, this);
        cam_sensor->attach(&cam->position);
    }

    setBgColor(_bgcolor.redF(), _bgcolor.greenF(), _bgcolor.blueF());

    connect(this, SIGNAL(_addObjDynSignal(Obj *)),
            this, SLOT(_addObjDynSlot(Obj *)));
    connect(this, SIGNAL(_clearObjsDynSignal()),
            this, SLOT(_clearObjsDynSlot()));
}

Viewer::~Viewer()
{
    _light->unref();
    _root->unref();
}

void Viewer::addObj(Obj *o)
{
    _scene.add(o);
}

void Viewer::addObjDyn(Obj *o)
{
    // serialization in one! Qt thread
    emit _addObjDynSignal(o);
}

void Viewer::_addObjDynSlot(Obj *o)
{
    if (_scene_dyn_clear){
        _scene_dyn.clear();
        _scene_dyn_clear = false;
    }
    _scene_dyn.add(o);
}

void Viewer::clearObjsDyn()
{
    // serialization in one! Qt thread
    emit _clearObjsDynSignal();
}

void Viewer::_clearObjsDynSlot()
{
    _scene_dyn_clear = true;
}


void Viewer::updateLight()
{
    SoCamera *cam = this->getSoEventManager()->getCamera();
    SbVec3f rot, orig;

    orig.setValue(0, 0, 1);

    if (cam != NULL){
        cam->orientation.getValue().multVec(orig, rot);
        _light->direction.setValue(rot);
    }else{
         _light->direction.setValue(orig);
    }
}

bool Viewer::processSoEvent(const SoEvent *event)
{
    if (_disabled_rotation){
        // Disabling rotation. Rotation is performed in QuarterWidget using
        // left button of mouse. So this only identifies when left button
        // is down and simply ignore event.
        // This solution, of course, isn't ideal but I wasn't able to find
        // how to do this better.
        if (event->getTypeId() == SoMouseButtonEvent::getClassTypeId()
                && !event->wasShiftDown()
                && !event->wasCtrlDown()
                && !event->wasAltDown()
                && ((SoMouseButtonEvent *)event)->getButton() == SoMouseButtonEvent::BUTTON1
                ){
            return false;
        }
    }
    return QuarterWidget::processSoEvent(event);
}


void Viewer::setBgColor(double r, double g, double b)
{
    _bgcolor.setRgbF(r, g, b);
    setBackgroundColor(_bgcolor);
}

void Viewer::setBgColorR(double v)
{
    _bgcolor.setRedF(v);
    setBackgroundColor(_bgcolor);
}

void Viewer::setBgColorG(double v)
{
    _bgcolor.setGreenF(v);
    setBackgroundColor(_bgcolor);
}

void Viewer::setBgColorB(double v)
{
    _bgcolor.setBlueF(v);
    setBackgroundColor(_bgcolor);
}

} /* namespace Coin3d */

} /* namespace SVT */
