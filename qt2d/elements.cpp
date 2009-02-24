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

#include <QPointF>
#include "elements.hpp"

void SVT::Qt2D::Elements::_setPointInBoundingRect(const svt_point_t point)
{
    if (!_brect_init){
        _brect.setTopLeft(QPointF(point[0], -1. * point[1]));
        _brect.setWidth(0.);
        _brect.setHeight(0.);
        _brect_init = true;
        return;
    }

    if (point[0] < _brect.left())
        _brect.setLeft(point[0]);
    if (point[0] > _brect.right())
        _brect.setRight(point[0]);
    if ((-1. * point[1]) < _brect.top())
        _brect.setTop(-1. * point[1]);
    if ((-1. * point[1]) > _brect.bottom())
        _brect.setBottom(-1. * point[1]);
}
