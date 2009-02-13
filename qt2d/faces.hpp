#ifndef SVT_QT2D_FACES_HPP
#define SVT_QT2D_FACES_HPP

#include "../parser/obj.h"
#include "elements.hpp"

namespace SVT {

namespace Qt2D {

class Faces : public Elements {
  private:
    QPainterPath _path;
    int _num_faces;

  public:
    Faces(svt_obj_t *obj);
    ~Faces();

    int numFaces() const { return _num_faces; }

    void paint(QPainter &painter);
};

} /* Qt2D */

} /* SVT */

#endif

