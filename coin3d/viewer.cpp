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
#include <Inventor/events/SoEvent.h>
#include <Inventor/events/SoMouseButtonEvent.h>
#include <Inventor/SoEventManager.h>
#include <Inventor/nodes/SoCamera.h>
#include "viewer.hpp"
#include "common/msg.hpp"
using namespace SIM::Coin3D::Quarter;


namespace SVT {

namespace Coin3d {

Viewer::Viewer()
    : QuarterWidget()
{
    setNavigationModeFile(QUrl("coin:/scxml/navigation/examiner.xml"));
    //setBackgroundColor(QColor(255, 255, 255));
}

Viewer::~Viewer()
{
}

} /* namespace Coin3d */

} /* namespace SVT */
