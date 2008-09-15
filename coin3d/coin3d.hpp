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

#ifndef COIN3D_COIN3D_HPP
#define COIN3D_COIN3D_HPP

#include <Inventor/Qt/SoQt.h>
#include <Inventor/Qt/viewers/SoQtExaminerViewer.h>
#include <QWidget>
#include <list>
#include "../qt/main_window.hpp"
#include "obj_manager.hpp"
#include "viewer.hpp"

namespace SVT {

namespace Coin3d {

class Coin3d {
  private:
    static Qt::MainWindow *_mainwin;
    static QWidget *_win;
    static Viewer *_viewer;
    static ObjManager _obj_manager;

  public:
    static void init(const char *win_title = "");
    static void mainLoop();
    static void free();

    /**
     * Add object to Viewer.
     */
    static void addObj(Obj *obj);
};

} /* namespace Coin3d */
} /* namespace SVT */
#endif

