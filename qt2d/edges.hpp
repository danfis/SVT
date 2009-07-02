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

#ifndef SVT_QT2D_EDGES_HPP
#define SVT_QT2D_EDGES_HPP

#include <QLineF>
#include <list>
#include "parser/obj.h"
#include "elements.hpp"

namespace SVT {

namespace Qt2D {

class Edges : public Elements {
  private:
    std::list<QLineF *> _lines;
    int _num_edges;

  public:
    Edges(svt_obj_t *obj);
    ~Edges();

    int numEdges() const { return _num_edges; }

    void paint(QPainter &painter, const QRectF &rect);
};

} /* Qt2D */

} /* SVT */

#endif

