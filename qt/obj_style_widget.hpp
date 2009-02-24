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

#ifndef QT_OBJ_STYLE_WIDGET_HPP
#define QT_OBJ_STYLE_WIDGET_HPP

#include <QDoubleSpinBox>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>

#include "common/obj.hpp"

namespace SVT {

namespace Qt {

class ObjStyleWidget : public QWidget {
    Q_OBJECT

  private:
    Common::Obj *_obj;

    QDoubleSpinBox *_points[4]; /* size, r, g, b */
    QPushButton *_points_b;
    QDoubleSpinBox *_edges[4];
    QPushButton *_edges_b;
    QDoubleSpinBox *_faces[3]; /* r, g, b */
    QPushButton *_faces_b;

    QWidget *_buildPoints();
    QWidget *_buildEdges();
    QWidget *_buildFaces();

    void _buildColors(QVBoxLayout *layout, QDoubleSpinBox **refs);
    void _buildSize(QVBoxLayout *layout, QDoubleSpinBox **refs);
    void _buildOnOff(QVBoxLayout *layout, QPushButton **refs);

    void _setUpConnections();
    void _setUpDefaultValues();

  public:
    ObjStyleWidget(Common::Obj *obj);

  public slots:
    void setPointSize(double val);
    void setPointColor(double val[3]);
    void setPointColor(double r, double g, double b);
    void setPointColorRed(double val);
    void setPointColorGreen(double val);
    void setPointColorBlue(double val);
    void setPointOnOff(bool on);

    void setEdgeWidth(double val);
    void setEdgeColor(double val[3]);
    void setEdgeColor(double r, double g, double b);
    void setEdgeColorRed(double val);
    void setEdgeColorGreen(double val);
    void setEdgeColorBlue(double val);
    void setEdgeOnOff(bool on);

    void setFaceColor(double val[3]);
    void setFaceColor(double r, double g, double b);
    void setFaceColorRed(double val);
    void setFaceColorGreen(double val);
    void setFaceColorBlue(double val);
    void setFaceOnOff(bool on);


  private slots:
    void _pointSize(double val);
    void _pointColorRed(double val);
    void _pointColorBlue(double val);
    void _pointColorGreen(double val);
    void _pointOnOff(bool off);

    void _edgeWidth(double val);
    void _edgeColorRed(double val);
    void _edgeColorBlue(double val);
    void _edgeColorGreen(double val);
    void _edgeOnOff(bool off);

    void _faceColorRed(double val);
    void _faceColorBlue(double val);
    void _faceColorGreen(double val);
    void _faceOnOff(bool off);

  signals:
    void pointSize(Common::Obj *obj, double val);
    void pointColorRed(Common::Obj *obj, double val);
    void pointColorBlue(Common::Obj *obj, double val);
    void pointColorGreen(Common::Obj *obj, double val);
    void pointColor(Common::Obj *obj, double r, double g, double b);
    void pointOnOff(Common::Obj *obj, bool on);

    void edgeWidth(Common::Obj *obj, double val);
    void edgeColorRed(Common::Obj *obj, double val);
    void edgeColorBlue(Common::Obj *obj, double val);
    void edgeColorGreen(Common::Obj *obj, double val);
    void edgeColor(Common::Obj *obj, double r, double g, double b);
    void edgeOnOff(Common::Obj *obj, bool on);

    void faceColorRed(Common::Obj *obj, double val);
    void faceColorBlue(Common::Obj *obj, double val);
    void faceColorGreen(Common::Obj *obj, double val);
    void faceColor(Common::Obj *obj, double r, double g, double b);
    void faceOnOff(Common::Obj *obj, bool on);
};

} /* Qt */

} /* SVT */

#endif
