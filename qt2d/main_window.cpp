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

#include "obj.hpp"
#include "main_window.hpp"


namespace SVT {

namespace Qt2D {

MainWindow::MainWindow()
    : Qt::MainWindow(), _painter(0)
{
    _config = new Qt::ConfigWidget();
    _obj_widgets->push(_config);

    _painter = new Painter();

    connect(_config, SIGNAL(fitToWin()),
            _painter, SLOT(fitToWin()));

    setCentralWidget(_painter);
}

MainWindow::~MainWindow()
{
    std::list<Obj *>::iterator it, it_end;

    if (_painter != 0)
        delete _painter;

    it = _objs.begin();
    it_end = _objs.end();
    for (; it != it_end; ++it){
        delete *it;
    }
    
}

void MainWindow::addObj(Obj *o)
{
    addObjWidget(o);
    _painter->addObj(o);

    _objs.push_back(o);
}


}

}
