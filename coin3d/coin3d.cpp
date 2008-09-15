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

#include "coin3d.hpp"


namespace SVT {
namespace Coin3d {

Qt::MainWindow *Coin3d::_mainwin = 0;
QWidget *Coin3d::_win = 0;
ViewerLive *Coin3d::_viewer = 0;
ObjManager Coin3d::_obj_manager;

void Coin3d::init(const char *win_title)
{
    _win = SoQt::init(win_title);
    _mainwin = new Qt::MainWindow();
    _viewer = new ViewerLive(_win);
    _mainwin->setCentralWidget(_win);
}

void Coin3d::mainLoop()
{
    _viewer->setSceneGraph(_obj_manager.root());
    _viewer->show();

    _mainwin->show();

    SoQt::show(_mainwin);
    SoQt::mainLoop();
}

void Coin3d::free()
{
    if (_viewer != 0)
        delete _viewer;
    delete _mainwin;
}

void Coin3d::showMessageInStatusBar(QString &str)
{
    //_mainwin->showMsgInStatusBar(str);
}

void Coin3d::addObj(Obj *obj)
{
    _obj_manager.add(obj);
    _mainwin->addObjWidget(obj);
}

void Coin3d::addDynObj(Obj *obj)
{
    _viewer->setDynSceneGraph(obj->root());
}

void Coin3d::clearDynObjs()
{
    _viewer->clearDynSceneGraph();
}

} /* namespace Coin3d */
} /* namespace SVT */
