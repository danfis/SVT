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

#ifndef SVT_QT2D_POINTS_HPP
#define SVT_QT2D_POINTS_HPP

#include <QPointF>

#include "parser/obj.h"
#include "elements.hpp"

namespace SVT {

namespace Qt2D {

class Points : public Elements{
  private:
    QPointF **_points; /*! list of points */
    int _points_len;

  public:
    Points(svt_obj_t *obj);
    ~Points();

    int numPoints() const { return _points_len; }

    void paint(QPainter &painter, const QRectF &rect);
};

} /* Qt2D */

} /* SVT */

#endif


