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

#ifndef QT2D_OBJ_HPP_
#define QT2D_OBJ_HPP_

#include <QRectF>
#include <string>

#include "../common/obj.hpp"
#include "../parser/obj.h"
#include "points.hpp"
#include "edges.hpp"
#include "faces.hpp"

namespace SVT {

namespace Qt2D {

class Painter;

/**
 * Class which describes visualisable object by Coin3d library.
 */
class Obj : public Common::Obj {
  private:
    Points *_points;
    Edges *_edges;
    Faces *_faces;
    std::string _name;
    QRectF _brect; /*! boudning rectangle */
    QRect _brecti; /*! bounding rectangle in ints */
    bool _all_on;
    Painter *_painter;

  public:
    Obj(svt_obj_t *obj);
    ~Obj();

    const std::string &name() const { return _name; }

    int numPoints() const { return (_points ? _points->numPoints() : 0); }
    int numEdges() const { return (_edges ? _edges->numEdges() : 0); }
    int numFaces() const { return (_faces ? _faces->numFaces() : 0); }

    bool pointsOn() const { return (_points ? _points->on() : false); }
    bool edgesOn() const { return (_edges ? _edges->on() : false); }
    bool facesOn() const { return (_faces ? _faces->on() : false); }
    bool allOn() const { return _all_on; }

    bool pointsOff() const { return !pointsOn(); }
    bool edgesOff() const { return !edgesOn(); }
    bool facesOff() const { return !facesOn(); }
    bool allOff() const { return !_all_on; }

    float pointSize() const { return (_points ? _points->size() : -1.); }
    float edgeWidth() const { return (_edges ? _edges->size() : -1.); }

    void pointColor(float *r, float *g, float *b) const;
    void pointColor(float rgb[3]) const
        { pointColor(rgb, rgb + 1, rgb + 2); }
    float pointColorRed() const
        { return (_points ? _points->color().redF() : -1.); }
    float pointColorGreen() const
        { return (_points ? _points->color().greenF() : -1.); }
    float pointColorBlue() const
        { return (_points ? _points->color().blueF() : -1.); }

    void edgeColor(float *r, float *g, float *b) const;
    void edgeColor(float rgb[3]) const
        { edgeColor(rgb, rgb + 1, rgb + 2); }
    float edgeColorRed() const
        { return (_edges ? _edges->color().redF() : -1.); }
    float edgeColorGreen() const
        { return (_edges ? _edges->color().greenF() : -1.); }
    float edgeColorBlue() const
        { return (_edges ? _edges->color().blueF() : -1.); }

    void faceColor(float *r, float *g, float *b) const;
    void faceColor(float rgb[3]) const
        { faceColor(rgb, rgb + 1, rgb + 2); }
    float faceColorRed() const
        { return (_faces ? _faces->color().redF() : -1.); }
    float faceColorGreen() const
        { return (_faces ? _faces->color().greenF() : -1.); }
    float faceColorBlue() const
        { return (_faces ? _faces->color().blueF() : -1.); }

    void setAllOn(bool on = true)
        { _all_on = on; update(); }

    void setPointsOn(bool on = true)
        { if (_points){ _points->setOn(on); update(); } }
    void setEdgesOn(bool on = true)
        { if (_edges){ _edges->setOn(on); update(); } }
    void setFacesOn(bool on = true)
        { if (_faces){ _faces->setOn(on); update(); } }

    void setPointSize(float size)
        { if (_points){ _points->setSize(size); update(); } }
    void setEdgeWidth(float width)
        { if (_edges){ _edges->setSize(width); update(); } }

    void setPointColor(float r, float g, float b)
        { if (_points){ _points->setColor(r, g, b); update(); } }
    void setPointColor(float rgb[3])
        { setPointColor(rgb[0], rgb[1], rgb[2]); }
    void setPointColorRed(float v)
        { if (_points){ _points->setColorRed(v); update(); } }
    void setPointColorGreen(float v)
        { if (_points){ _points->setColorGreen(v); update(); } }
    void setPointColorBlue(float v)
        { if (_points){ _points->setColorBlue(v); update(); } }

    void setEdgeColor(float r, float g, float b)
        { if (_edges){ _edges->setColor(r, g, b); update(); } }
    void setEdgeColor(float rgb[3])
        { setEdgeColor(rgb[0], rgb[1], rgb[2]); }
    void setEdgeColorRed(float v)
        { if (_edges){ _edges->setColorRed(v); update(); } }
    void setEdgeColorGreen(float v)
        { if (_edges){ _edges->setColorGreen(v); update(); } }
    void setEdgeColorBlue(float v)
        { if (_edges){ _edges->setColorBlue(v); update(); } }

    void setFaceColor(float r, float g, float b)
        { if (_faces){ _faces->setColor(r, g, b); update(); } }
    void setFaceColor(float rgb[3])
        { setFaceColor(rgb[0], rgb[1], rgb[2]); }
    void setFaceColorRed(float v)
        { if (_faces){ _faces->setColorRed(v); update(); } }
    void setFaceColorGreen(float v)
        { if (_faces){ _faces->setColorGreen(v); update(); } }
    void setFaceColorBlue(float v)
        { if (_faces){ _faces->setColorBlue(v); update(); } }


    void update();

    void setPainter(Painter *p) { _painter = p; }

    void paint(QPainter &painter, const QRectF &rect)
        { if (_faces) _faces->paint(painter, rect);
          if (_edges) _edges->paint(painter, rect);
          if (_points) _points->paint(painter, rect); }

    const QRectF &boundingRect() const { return _brect; }
};

} /* Common */

} /* SVT */
#endif

