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
