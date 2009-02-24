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

#include "viewer_live.hpp"

#include "viewer_live.moc"

namespace SVT {

namespace Coin3d {

ViewerLive::ViewerLive(QWidget *win)
    : Viewer(win)
{
    _dyn = new SoSwitch;
    _dyn->whichChild = SO_SWITCH_ALL;
    _dyn->ref();

    _root->addChild(_dyn);

    connect(this, SIGNAL(_setDynSceneGraphSignal(SoNode *)),
            this, SLOT(_setDynSceneGraph(SoNode *)));
    connect(this, SIGNAL(_clearDynSceneGraphSignal()),
            this, SLOT(_clearDynSceneGraph()));
}

ViewerLive::~ViewerLive()
{
    _dyn->unref();
}

void ViewerLive::_setDynSceneGraph(SoNode *root)
{
    _dyn->removeAllChildren();
    _dyn->addChild(root);
    //setSceneGraph(_root);
}

void ViewerLive::_clearDynSceneGraph()
{
    _dyn->removeAllChildren();
}

void ViewerLive::setDynSceneGraph(SoNode *root)
{
    emit _setDynSceneGraph(root);
}

void ViewerLive::clearDynSceneGraph()
{
    emit _clearDynSceneGraphSignal();
}

} /* namespace Coin3d */

} /* namespace SVT */
