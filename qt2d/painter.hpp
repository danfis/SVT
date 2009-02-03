#ifndef SVT_QT2D_PAINTER_HPP
#define SVT_QT2D_PAINTER_HPP

#include <QWidget>
#include <QPainter>
#include <QLinkedList>

namespace SVT {

namespace Qt2D {

class Painter : public QWidget {
  private:
    QPainterPath **_paths;
    int _paths_len;

  protected:
    void paintEvent(QPaintEvent *e);

  public:
    Painter(QWidget *parent = 0);
    ~Painter();
};

} /* Qt2D */

} /* SVT */

#endif
