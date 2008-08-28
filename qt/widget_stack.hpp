#ifndef QT_WIDGET_STACK_HPP
#define QT_WIDGET_STACK_HPP

#include <list>
#include <QScrollArea>
#include <QVBoxLayout>

namespace Qt {

class WidgetStack : public QScrollArea {
    QVBoxLayout *_layout;

  public:
    WidgetStack();
    void push(QWidget *);
    void finish();
};

}
#endif
