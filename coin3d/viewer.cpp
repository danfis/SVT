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

#include "viewer.hpp"

namespace SVT {

namespace Coin3d {

Viewer::Viewer(QWidget *win)
    : SoQtExaminerViewer(win)
{
    _root = new SoSwitch;
    _root->ref();
    _root->whichChild = SO_SWITCH_ALL;

    _dyn = new SoSwitch;
    _dyn->ref();
    _dyn->whichChild = SO_SWITCH_ALL;

    _root->addChild(_dyn);
}

Viewer::~Viewer()
{
    _root->unref();
    _dyn->unref();
}

void Viewer::setSceneGraph(SoNode *node)
{
    _root->addChild(node);
    SoQtExaminerViewer::setSceneGraph(node);
}

} /* namespace Coin3d */

} /* namespace SVT */
