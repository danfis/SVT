#include <iostream>
#include "painter.hpp"
using namespace std;


#include "painter.moc"


namespace SVT {

namespace Qt2D {


Painter::Painter(QWidget *parent)
    : QWidget(parent),
      _scale(1.), _dx(0.), _dy(0.),
      _brect_init(false), _mouse_pressed(false)
{
}

Painter::~Painter()
{
}

void Painter::addObj(Obj *o)
{
    _objs.push_back(o);

    if (!_brect_init){
        const QRectF &br = o->boundingRect();

        _brect = br;
        _brect_init = true;
    }else{
        const QRectF &br = o->boundingRect();

        if (br.left() < _brect.left())
            _brect.setLeft(br.left());
        if (br.right() > _brect.right())
            _brect.setRight(br.right());
        if (br.top() < _brect.top())
            _brect.setTop(br.top());
        if (br.bottom() > _brect.bottom())
            _brect.setBottom(br.bottom());
    }
}

void Painter::scaleToWindow()
{
    QSize wsize = size();
    qreal tmp;
    QPointF center = _brect.center();
    QPointF wcenter(wsize.width() / 2., wsize.height() / 2.);

    // scale:
    tmp = (qreal)wsize.width() / _brect.width();
    _scale = (qreal)wsize.height() / _brect.height();
    if (tmp < _scale)
        _scale = tmp;

    // dx, dy
    center *= _scale;
    _dx = wcenter.x() - center.x();
    _dy = wcenter.y() - center.y();
}


void Painter::paintEvent(QPaintEvent *e)
{
    QMatrix tr;
    QPainter painter(this);
    list<Obj *>::iterator it, it_end;

    tr.translate(_dx, _dy);
    tr.scale(_scale, _scale);
    painter.setWorldMatrix(tr);

    painter.setRenderHint(QPainter::Antialiasing);

    it = _objs.begin();
    it_end = _objs.end();
    for (; it != it_end; ++it){
        if (!(*it)->allOff())
            (*it)->paint(painter);
    }

    painter.end();
}


void Painter::wheelEvent(QWheelEvent *event)
{
    _scale += event->delta() * 1.E-3;

    update();
}

void Painter::mousePressEvent(QMouseEvent *event)
{
    _mouse_pressed = true;
    _mouse_pos = event->globalPos();
}

void Painter::mouseReleaseEvent(QMouseEvent *event)
{
    _mouse_pressed = false;
    _mouse_pos = event->globalPos();
}

void Painter::mouseMoveEvent(QMouseEvent *event)
{
    QPoint pos = event->globalPos();

    _dx += pos.x() - _mouse_pos.x();
    _dy += pos.y() - _mouse_pos.y();

    _mouse_pos = pos;

    update();
}


void Painter::repaint(Common::Obj *_o)
{
    //Obj *o = (Obj *)_o;

    update();
}


} /* Qt2D */

} /* SVT */
