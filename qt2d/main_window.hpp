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

#ifndef QT2D_MAIN_WINDOW_HPP_
#define QT2D_MAIN_WINDOW_HPP_

#include <list>

#include "../qt/main_window.hpp"
#include "../qt/obj_style_widget.hpp"
#include "../qt/obj_widget.hpp"
#include "../parser/obj.h"
#include "painter.hpp"

namespace SVT {

namespace Qt2D {

class MainWindow : public Qt::MainWindow{
  private:
    std::list<Obj *> _objs;
    Painter *_painter;

  public:
    MainWindow();
    ~MainWindow();

    void addObj(svt_obj_t *obj);
    Qt::ObjStyleWidget *showObjStyleWidget(Common::Obj *);
    Qt::ObjWidget *addObjWidget(Common::Obj *, int flags = Qt::OBJ_WIDGET_ALL);
};

} /* Qt2D */

} /* SVT */

#endif
