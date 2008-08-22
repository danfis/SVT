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

#include <iostream>
#include "config_dialog.hpp"
#include "coin3dtools.hpp"

MainWindow *Coin3dTools::_mainwin = 0;
QWidget *Coin3dTools::_win = 0;
Viewer *Coin3dTools::_viewer = 0;

void Coin3dTools::init(const char *title)
{
    _win = SoQt::init(title);
    _mainwin = new MainWindow();
    _viewer = new Viewer(_win);
    
    if (_win == 0 || _mainwin == 0){
        std::cerr << "Can't initialize windows!" << std::endl;
        exit(-1);
    }

    _mainwin->setCentralWidget(_win);
}


void Coin3dTools::mainLoop()
{
    if (_viewer != 0){
        _viewer->show();

        _mainwin->createConfigDialog(_viewer);
    }
    SoQt::show(_mainwin);
    SoQt::mainLoop();
}

void Coin3dTools::finish()
{
    if (_viewer != 0)
        delete _viewer;
    delete _mainwin;
}
