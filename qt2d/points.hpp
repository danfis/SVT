#ifndef SVT_QT2D_POINTS_HPP
#define SVT_QT2D_POINTS_HPP

#include <QPointF>

#include "../parser/obj.h"
#include "elements.hpp"

namespace SVT {

namespace Qt2D {

class Points : public Elements{
  private:
    QPointF **_points; /*! list of points */
    int _points_len;

  public:
    Points(svt_obj_t *obj);
    ~Points();

    int numPoints() const { return _points_len; }

    void paint(QPainter &painter, const QRectF &rect);
};

} /* Qt2D */

} /* SVT */

#endif


