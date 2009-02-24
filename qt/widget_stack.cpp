/**
 * SVT
 * ----------
 * Copyright (c)2007,2008,2009 Daniel Fiser <danfis (at) danfis (dot) cz>
 *
 *
 * This file is part of SVT
 *
 * SVT is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * SVT is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with SVT. If not, see <http://www.gnu.org/licenses/>.
 */

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
