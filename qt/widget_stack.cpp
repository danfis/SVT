#include "widget_stack.hpp"

namespace Qt {

WidgetStack::WidgetStack()
{
    _layout = new QVBoxLayout;
}

void WidgetStack::push(QWidget *w)
{
    _layout->addWidget(w);
}

void WidgetStack::finish()
{
    QWidget *main = new QWidget;
    main->setLayout(_layout);
    setWidget(main);
}

}
