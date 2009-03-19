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

#include <iostream>
#include "painter.hpp"
#include "common/functions.hpp"
#include "common/msg.hpp"
using namespace std;


#include "painter.moc"

#define MIN_SCALE 0.05

namespace SVT {

namespace Qt2D {


Painter::Painter(QWidget *parent)
    : QWidget(parent),
      _scale(1.), _dx(0.), _dy(0.),
      _mouse_pressed(false)
{
}

Painter::~Painter()
{
}

void Painter::_setUpTransf(QMatrix &m) const
{
    m.reset();
    m.translate(_dx, _dy);
    m.scale(_scale, _scale);
}

void Painter::_setUpReverseTransf(QMatrix &m) const
{
    m.reset();
    m.scale(1. / _scale, 1. / _scale);
    m.translate(-_dx, -_dy);
}


void Painter::addObj(Obj *o)
{
    _objs.push_back(o);
    o->setPainter(this);
}

void Painter::fitToWin()
{
    std::list<Obj *>::iterator it, it_end;
    QRectF brect; // boundig rectangle
    int objs_on;
    QSize wsize = size();
    qreal tmp, scale, dx, dy;
    QPointF center;
    QPointF wcenter(wsize.width() / 2., wsize.height() / 2.);

    if (_objs.size() <= 0)
        return;

    // compute bounding rectangle
    it = _objs.begin();
    it_end = _objs.end();
    objs_on = 0;
    for (; it != it_end; ++it){
        if ((*it)->allOn()){
            if (objs_on == 0){
                brect = (*it)->boundingRect();
            }else{
                brect = brect.united((*it)->boundingRect());
            }

            objs_on++;
        }
    }

    if (objs_on <= 0)
        return;

    // copy center of bounding rect
    center = brect.center();

    // scale:
    tmp = (qreal)wsize.width() / brect.width();
    scale = (qreal)wsize.height() / brect.height();
    if (tmp < scale)
        scale = tmp;

    // dx, dy
    center *= scale;
    dx = wcenter.x() - center.x();
    dy = wcenter.y() - center.y();

    setTransf(dx, dy, scale);
    update();
}


void Painter::paintEvent(QPaintEvent *event)
{
    const QRect &rect_update_i = event->rect();
    QRectF rect_update;
    QMatrix tr, tr_rev;
    QPainter painter(this);
    list<Obj *>::iterator it, it_end;

    // set up bg color
    painter.fillRect(0, 0, width(), height(), _bgcolor);

    // set up transformations
    _setUpTransf(tr);
    _setUpReverseTransf(tr_rev);

    // set up world matrix
    painter.setWorldMatrix(tr);

    // turn on antialiasing
    painter.setRenderHint(QPainter::Antialiasing);

    // set up update rectangle
    Common::rectToRectF(rect_update_i, rect_update);
    rect_update = tr_rev.mapRect(rect_update);

    it = _objs.begin();
    it_end = _objs.end();
    for (; it != it_end; ++it){
        // paint object only if is enabled and if object falls into
        // rectangle which should be updated
        if ((*it)->allOn() && (*it)->boundingRect().intersects(rect_update)){
            (*it)->paint(painter, rect_update);
        }
    }

    painter.end();
}


void Painter::wheelEvent(QWheelEvent *event)
{
    //setScale(_scale + event->delta() * 1.E-3);
    scale(event->delta() * 1E-3);
}

void Painter::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton){
        _mouse_pressed = true;
        _mouse_pos = event->globalPos();
    }
}

void Painter::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && _mouse_pressed){
        _mouse_pressed = false;
        _mouse_pos = event->globalPos();
    }
}

void Painter::mouseMoveEvent(QMouseEvent *event)
{

    if (_mouse_pressed){
        QPoint pos = event->globalPos();

        translate(pos.x() - _mouse_pos.x(),
                  pos.y() - _mouse_pos.y());

        _mouse_pos = pos;
    }
}

void Painter::setBgColor(double r, double g, double b)
{
    _bgcolor.setRgbF(r, g, b);
    update();
}

void Painter::setBgColorR(double v)
{
    _bgcolor.setRedF(v);
    update();
}

void Painter::setBgColorG(double v)
{
    _bgcolor.setGreenF(v);
    update();
}

void Painter::setBgColorB(double v)
{
    _bgcolor.setBlueF(v);
    update();
}

void Painter::update(Common::Obj *o)
{
    if (o != 0){
        /*
        Obj *obj = (Obj *)o;
        QRect r;
        QMatrix tr;

        _setUpTransf(tr);

        Common::rectFToRect(tr.mapRect(obj->boundingRect()), r);

        QWidget::update(r);
        */
        QWidget::update();
    }else{
        QWidget::update();
    }
}

void Painter::setTransf(double dx, double dy, double scale)
{
    _scale = scale;
    _dx = dx;
    _dy = dy;

    update();
}

void Painter::scale(double val, double center_x, double center_y)
{
    double relscale;

    relscale = 1. + val;
    //DBG("relscale: " << relscale);

    _scale *= relscale;

    // scale also translation
    _dx *= relscale;
    _dy *= relscale;

    // and center window
    _dx -= width() * (relscale - 1) / 2.;
    _dy -= height() * (relscale - 1) / 2.;

    update();
}

void Painter::translate(double dx, double dy)
{
    _dx += dx;
    _dy += dy;

    update();
}


} /* Qt2D */

} /* SVT */
