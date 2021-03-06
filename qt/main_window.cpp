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

#include <QShortcut>
#include "main_window.hpp"


#include "main_window.moc"

namespace SVT {

namespace Qt {

MainWindow::MainWindow()
{
    QShortcut *shortcut;

    _obj_widgets = new WidgetStack;

    _left_dock = new QDockWidget;
    _left_dock->setAllowedAreas(::Qt::LeftDockWidgetArea);
    _left_dock->setFeatures(QDockWidget::DockWidgetFloatable
                            | QDockWidget::DockWidgetMovable);
    _left_dock->setWidget(_obj_widgets);
    addDockWidget(::Qt::LeftDockWidgetArea, _left_dock, ::Qt::Vertical);

    _right_dock = 0;

    _status = new QStatusBar;
    setStatusBar(_status);

    // shortcut for close window
    shortcut = new QShortcut(::Qt::Key_Q, this);
    connect(shortcut, SIGNAL(activated()),
            this, SLOT(close()));

    connect(this, SIGNAL(_showMsgInStatusBarSignal(const QString &)),
            _status, SLOT(showMessage(const QString &)));

    resize(800, 600);
}

MainWindow::~MainWindow()
{
    delete _obj_widgets;
}

void MainWindow::addObjWidget(Common::Obj *obj, int flags)
{
    ObjWidget *o = new ObjWidget(obj, flags);
    _obj_widgets->push(o);

    connect(o, SIGNAL(config(Common::Obj *)),
            this, SLOT(showObjStyleWidget(Common::Obj *)));
}

void MainWindow::show()
{
    _obj_widgets->finish();
    QMainWindow::show();
}

void MainWindow::showMsgInStatusBarSignal(const QString &msg)
{
    emit _showMsgInStatusBarSignal(msg);
}

void MainWindow::showObjStyleWidget(Common::Obj *obj)
{
    ObjStyleWidget *osw = new ObjStyleWidget(obj);

    if (_right_dock != 0
        && dockWidgetArea(_right_dock) != ::Qt::NoDockWidgetArea){
        delete _right_dock;
    }

    _right_dock = new QDockWidget;
    _right_dock->setAllowedAreas(::Qt::RightDockWidgetArea);
    _right_dock->setFeatures(QDockWidget::DockWidgetFloatable
                             | QDockWidget::DockWidgetMovable
                             | QDockWidget::DockWidgetClosable);
    _right_dock->setWidget(osw);
    addDockWidget(::Qt::RightDockWidgetArea, _right_dock, ::Qt::Vertical);
}

void MainWindow::showMsgInStatusBar(const QString &msg)
{
    _status->showMessage(msg);
}

} /* Qt */

} /* SVT */
