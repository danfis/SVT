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

#ifndef QT_WIDGET_STACK_HPP
#define QT_WIDGET_STACK_HPP

#include <list>
#include <QScrollArea>
#include <QVBoxLayout>

namespace SVT {

namespace Qt {

class WidgetStack : public QScrollArea {
    QVBoxLayout *_layout;
    int _max_width;

  public:
    WidgetStack();
    void push(QWidget *);
    void finish();
};

} /* Qt */

} /* SVT */
#endif
