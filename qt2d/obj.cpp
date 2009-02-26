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
#include "painter.hpp"

SVT::Qt2D::Obj::Obj(svt_obj_t *obj)
    : _points(0), _edges(0), _faces(0), _all_on(true), _painter(0)
{
    bool brect_init = false;
    const char *name;

    name = svtObjName(obj);
    if (name != NULL)
        _name = name;

    if (svtObjNumPoints(obj) > 0)
        _points = new Points(obj);

    if (svtObjNumEdges(obj) > 0)
        _edges = new Edges(obj);

    if (svtObjNumFaces(obj) > 0)
        _faces = new Faces(obj);


    // set up bounding rectangle
    if (_points != 0){
        _brect = _points->boundingRect();
        brect_init = true;
    }else if (_edges != 0){
        if (!brect_init){
            _brect = _edges->boundingRect();
        }else{
            _brect = _brect.united(_edges->boundingRect());
        }
    }else if (_faces != 0){
        if (!brect_init){
            _brect = _faces->boundingRect();
        }else{
            _brect = _brect.united(_faces->boundingRect());
        }
    }
}

SVT::Qt2D::Obj::~Obj()
{
    if (_points != 0)
        delete _points;
    if (_edges != 0)
        delete _edges;
    if (_faces != 0)
        delete _faces;
}

void SVT::Qt2D::Obj::pointColor(float *r, float *g, float *b) const
{
    qreal rr, rg, rb;

    if (_points){
        _points->color().getRgbF(&rr, &rg, &rb);
        *r = rr;
        *g = rg;
        *b = rb;
    }
}

void SVT::Qt2D::Obj::edgeColor(float *r, float *g, float *b) const
{
    qreal rr, rg, rb;

    if (_edges){
        _edges->color().getRgbF(&rr, &rg, &rb);
        *r = rr;
        *g = rg;
        *b = rb;
    }
}

void SVT::Qt2D::Obj::faceColor(float *r, float *g, float *b) const
{
    qreal rr, rg, rb;

    if (_faces){
        _faces->color().getRgbF(&rr, &rg, &rb);
        *r = rr;
        *g = rg;
        *b = rb;
    }
}

void SVT::Qt2D::Obj::update()
{
    if (_painter != 0)
        _painter->update(this);
}
