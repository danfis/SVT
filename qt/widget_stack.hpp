#ifndef QT_WIDGET_STACK_HPP
#define QT_WIDGET_STACK_HPP

#include <list>
#include <QScrollArea>
#include <QVBoxLayout>

namespace SVT {

namespace Qt {

class WidgetStack : public QScrollArea {
    QVBoxLayout *_layout;

  public:
    WidgetStack();
    void push(QWidget *);
    void finish();
};

} /* Qt */

} /* SVT */
#endif
