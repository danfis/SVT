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

#ifndef SVT_QT2D_FACES_HPP
#define SVT_QT2D_FACES_HPP

#include "parser/obj.h"
#include "elements.hpp"

namespace SVT {

namespace Qt2D {

class Faces : public Elements {
  private:
    QPainterPath _path;
    int _num_faces;

  public:
    Faces(svt_obj_t *obj);
    ~Faces();

    int numFaces() const { return _num_faces; }

    void paint(QPainter &painter, const QRectF &rect);
};

} /* Qt2D */

} /* SVT */

#endif

