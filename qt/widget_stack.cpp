#include "widget_stack.hpp"

namespace SVT {

namespace Qt {

WidgetStack::WidgetStack()
    :_max_width(0)
{
    setAlignment(::Qt::AlignHCenter | ::Qt::AlignTop);
    setLineWidth(0);
    setContentsMargins(0, 0, 0, 0);

    _layout = new QVBoxLayout;
    _layout->setSpacing(10);
    _layout->setContentsMargins(0, 0, 0, 0);
}

void WidgetStack::push(QWidget *w)
{
    _layout->addWidget(w);
    if (w->width() > _max_width)
        _max_width = w->width();
}

void WidgetStack::finish()
{
    QWidget *main = new QWidget;
    main->setContentsMargins(0, 0, 0, 0);
    main->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    main->setLayout(_layout);
    setMaximumWidth(_max_width);
    setWidget(main);
}

} /* Qt */

} /* SVT */
