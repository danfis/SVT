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
#include <Inventor/nodes/SoDirectionalLight.h>
#include <QWidget>
#include <Quarter/QuarterWidget.h>
#include "obj_manager.hpp"

namespace SVT {

namespace Coin3d {

class Viewer : public SIM::Coin3D::Quarter::QuarterWidget {
    Q_OBJECT

    SoSwitch *_root;
    ObjManager _scene;
    ObjManager _scene_dyn;
    bool _scene_dyn_clear; /*! true if _scene_dyn should be cleared before
                               adding new obj */
    QColor _bgcolor;
    SoDirectionalLight *_light;
    bool _disabled_rotation;

  public:
    Viewer();
    ~Viewer();

    void addObj(Obj *o);
    void addObjDyn(Obj *o);
    void clearObjsDyn();

    void updateLight();
    bool processSoEvent(const SoEvent *event);

    const QColor &bgcolor() const { return _bgcolor; }

    bool disabledRotation() const { return _disabled_rotation; }

  public slots:
    void setBgColor(double r, double g, double b);
    void setBgColorR(double v);
    void setBgColorG(double v);
    void setBgColorB(double v);
    void disableRotation(double d = true) { _disabled_rotation = d; }

  signals:
    void _addObjDynSignal(Obj *o);
    void _clearObjsDynSignal();

  private slots:
    void _addObjDynSlot(Obj *o);
    void _clearObjsDynSlot();
};

} /* namespace Coin3d */

} /* namespace SVT */

#endif
