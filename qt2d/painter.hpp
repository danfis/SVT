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

#ifndef SVT_QT2D_PAINTER_HPP
#define SVT_QT2D_PAINTER_HPP

#include <QWidget>
#include <QPainter>
#include <QLinkedList>
#include <QRectF>
#include <QMatrix>
#include <QWheelEvent>
#include <list>

#include "obj.hpp"

namespace SVT {

namespace Qt2D {

class Painter : public QWidget {
    Q_OBJECT

  private:
    std::list<Obj *> _objs;
    qreal _scale, _dx, _dy; /*! world transfomataions */
    bool _mouse_pressed; /*! indicates if mouse's left button is pressed */
    QPoint _mouse_pos; /*! last position of mouse */


    /**
     * Sets up transformation matrix (scale and translation)
     */
    void _setUpTransf(QMatrix &m) const;

    /**
     * Same as _setUpTransf() but reverse transformation is used.
     */
    void _setUpReverseTransf(QMatrix &m) const;

  protected:
    void paintEvent(QPaintEvent *e);

  public:
    Painter(QWidget *parent = 0);
    ~Painter();

    void addObj(Obj *o);

    void wheelEvent(QWheelEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

  public slots:
    void update(Common::Obj *o = 0);
    void setScale(qreal val) { setTransf(_dx, _dy, val); }
    void setTranslation(qreal dx, qreal dy) { setTransf(dx, dy, _scale); }
    void setTransf(qreal dx, qreal dy, qreal scale);
    void fitToWin();

  signals:
    void scaleChanged(double val);
};

} /* Qt2D */

} /* SVT */

#endif
