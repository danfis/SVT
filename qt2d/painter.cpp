#include <iostream>
#include "painter.hpp"
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

void Painter::addObj(Obj *o)
{
    _objs.push_back(o);
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
                const QRectF &br = (*it)->boundingRect();

                if (br.left() < brect.left())
                    brect.setLeft(br.left());
                if (br.right() > brect.right())
                    brect.setRight(br.right());
                if (br.top() < brect.top())
                    brect.setTop(br.top());
                if (br.bottom() > brect.bottom())
                    brect.setBottom(br.bottom());
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

    setTranslation(dx, dy);
    setScale(scale);
    update();
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
    setScale(_scale + event->delta() * 1.E-3);
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

        setTranslation(_dx + pos.x() - _mouse_pos.x(),
                       _dy + pos.y() - _mouse_pos.y());

        _mouse_pos = pos;
    }
}


void Painter::repaint(Common::Obj *_o)
{
    //Obj *o = (Obj *)_o;

    update();
}

void Painter::setScale(double val)
{
    _scale = val;
    if (_scale < 0.){
        _scale = MIN_SCALE;
    }

    emit scaleChanged(val);

    update();
}

void Painter::setTranslation(double dx, double dy)
{
    _dx = dx;
    _dy = dy;

    update();
}

} /* Qt2D */

} /* SVT */
