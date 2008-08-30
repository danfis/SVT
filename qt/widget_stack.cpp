#include "widget_stack.hpp"

namespace SVT {

namespace Qt {

WidgetStack::WidgetStack()
{
    setAlignment(::Qt::AlignHCenter | ::Qt::AlignTop);
    setLineWidth(0);
    setFrameShape(QFrame::NoFrame);
    setContentsMargins(0, 0, 0, 0);

    _layout = new QVBoxLayout;
    _layout->setSpacing(10);
    _layout->setContentsMargins(0, 0, 0, 0);
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

} /* Qt */

} /* SVT */
