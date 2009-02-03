#ifndef SVT_QT2D_FACES_HPP
#define SVT_QT2D_FACES_HPP

#include "../parser/obj.h"
#include "elements.hpp"

namespace SVT {

namespace Qt2D {

class Faces : public Elements {
  private:
    QPainterPath _path;

  public:
    Faces(svt_obj_t *obj);
    ~Faces();

    void paint(QPainter &painter);
};

} /* Qt2D */

} /* SVT */

#endif

