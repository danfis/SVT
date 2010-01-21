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

#ifndef COMMON_OBJ_HPP_
#define COMMON_OBJ_HPP_

#include <string>

#include "common/settings.hpp"

namespace SVT {

namespace Common {

/**
 * Class which describes visualisable object by Coin3d library.
 */
class Obj {
  protected:
    /*! Indicates, if colors weren't already set up or something wasn't
     *  already turned on/off */
    bool _point_color_set, _edge_color_set, _face_color_set;
    bool _points_off_set, _edges_off_set, _faces_off_set;

  public:
    Obj() : _point_color_set(false), _edge_color_set(false),
            _face_color_set(false),
            _points_off_set(false), _edges_off_set(false),
            _faces_off_set(false){}
    //~Obj()

    virtual const std::string &name() const = 0;

    virtual int numPoints() const = 0;
    virtual int numEdges() const = 0;
    virtual int numFaces() const = 0;

    virtual bool pointsOn() const = 0;
    virtual bool edgesOn() const = 0;
    virtual bool facesOn() const = 0;
    virtual bool allOn() const = 0;

    virtual bool pointsOff() const { return !pointsOn(); }
    virtual bool edgesOff() const { return !edgesOn(); }
    virtual bool facesOff() const { return !facesOn(); }
    virtual bool allOff() const { return !allOn(); }

    virtual float pointSize() const = 0;
    virtual float edgeWidth() const = 0;

    virtual void pointColor(float *r, float *g, float *b) const = 0;
    virtual void pointColor(float rgb[3]) const
        { pointColor(rgb, rgb + 1, rgb + 2); }
    virtual float pointColorRed() const = 0;
    virtual float pointColorGreen() const = 0;
    virtual float pointColorBlue() const = 0;
    bool pointColorAlreadySet() { return _point_color_set; }

    virtual void edgeColor(float *r, float *g, float *b) const = 0;
    virtual void edgeColor(float rgb[3]) const
        { edgeColor(rgb, rgb + 1, rgb + 2); }
    virtual float edgeColorRed() const = 0;
    virtual float edgeColorGreen() const = 0;
    virtual float edgeColorBlue() const = 0;
    bool edgeColorAlreadySet() { return _edge_color_set; }

    virtual void faceColor(float *r, float *g, float *b) const = 0;
    virtual void faceColor(float rgb[3]) const
        { faceColor(rgb, rgb + 1, rgb + 2); }
    virtual float faceColorRed() const = 0;
    virtual float faceColorGreen() const = 0;
    virtual float faceColorBlue() const = 0;
    bool faceColorAlreadySet() { return _face_color_set; }

    bool pointsOffAlreadySet() { return _points_off_set; }
    bool edgesOffAlreadySet() { return _edges_off_set; }
    bool facesOffAlreadySet() { return _faces_off_set; }

    virtual void setAllOn(bool on = true) = 0;

    virtual void setPointsOn(bool on = true) = 0;
    virtual void setEdgesOn(bool on = true) = 0;
    virtual void setFacesOn(bool on = true) = 0;

    virtual void setPointSize(float size) = 0;
    virtual void setEdgeWidth(float width) = 0;

    virtual void setPointColor(float r, float g, float b) = 0;
    virtual void setPointColor(float rgb[3])
        { setPointColor(rgb[0], rgb[1], rgb[2]); }
    virtual void setPointColorRed(float v) = 0;
    virtual void setPointColorGreen(float v) = 0;
    virtual void setPointColorBlue(float v) = 0;

    virtual void setEdgeColor(float r, float g, float b) = 0;
    virtual void setEdgeColor(float rgb[3])
        { setEdgeColor(rgb[0], rgb[1], rgb[2]); }
    virtual void setEdgeColorRed(float v) = 0;
    virtual void setEdgeColorGreen(float v) = 0;
    virtual void setEdgeColorBlue(float v) = 0;

    virtual void setFaceColor(float r, float g, float b) = 0;
    virtual void setFaceColor(float rgb[3])
        { setFaceColor(rgb[0], rgb[1], rgb[2]); }
    virtual void setFaceColorRed(float v) = 0;
    virtual void setFaceColorGreen(float v) = 0;
    virtual void setFaceColorBlue(float v) = 0;

    virtual void applySettings(const Settings &s);
};

} /* Common */

} /* SVT */
#endif
