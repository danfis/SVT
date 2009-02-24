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

#ifndef COIN3D_VIEWER_LIVE_HPP
#define COIN3D_VIEWER_LIVE_HPP

#include "viewer.hpp"

namespace SVT {

namespace Coin3d {


class ViewerLive : public Viewer {
    Q_OBJECT

  private:
    SoSwitch *_dyn;

  private slots:
    void _setDynSceneGraph(SoNode *);
    void _clearDynSceneGraph();

  signals:
    void _setDynSceneGraphSignal(SoNode *);
    void _clearDynSceneGraphSignal();

  public:
    ViewerLive(QWidget *win);
    ~ViewerLive();

    void setDynSceneGraph(SoNode *);
    void clearDynSceneGraph();
};

} /* namespace Coin3d */

} /* namespace SVT */

#endif

