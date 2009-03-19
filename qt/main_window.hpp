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

#ifndef QT_MAIN_WINDOW_HPP
#define QT_MAIN_WINDOW_HPP

#include <QMainWindow>
#include <QDockWidget>
#include <QStatusBar>
#include <QString>

#include "common/obj.hpp"

#include "obj_widget.hpp"
#include "obj_style_widget.hpp"
#include "widget_stack.hpp"

namespace SVT {

namespace Qt {

class MainWindow : public QMainWindow {
    Q_OBJECT

  protected:
    WidgetStack *_obj_widgets;
    QDockWidget *_left_dock, *_right_dock;
    QStatusBar *_status;

  public:
    MainWindow();
    virtual ~MainWindow();

    virtual void addObjWidget(Common::Obj *, int flags = OBJ_WIDGET_ALL);

    virtual void show();

    virtual void showMsgInStatusBarSignal(const QString &msg);

    virtual void setBgColor(double r, double g, double b) {}
  signals:
    virtual void _showMsgInStatusBarSignal(const QString &msg);
  public slots:
    virtual void showObjStyleWidget(Common::Obj *);
    virtual void showMsgInStatusBar(const QString &msg);
};

} /* Qt */

} /* SVT */

#endif
