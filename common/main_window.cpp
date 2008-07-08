/**
 * Coin3dTools
 * ------------
 * Copyright (c)2007 Daniel Fiser <danfis (at) danfis (dot) cz>
 *
 *
 * This file is part of Coin3dTools
 *
 * Coin3dTools is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Coin3dTools is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Coin3dTools.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "main_window.hpp"

#include "main_window.moc"

MainWindow::MainWindow(QWidget *parent, Qt::WindowFlags flags)
    : QMainWindow(parent, flags),
      _config_dialog(0), _right_dock(0)
{
    setDockOptions(QMainWindow::AnimatedDocks |
                   QMainWindow::AllowNestedDocks |
                   QMainWindow::AllowTabbedDocks);


    resize(800, 600);
}

MainWindow::~MainWindow()
{
    if (_config_dialog != 0)
        delete _config_dialog;
}

void MainWindow::createConfigDialog(Viewer *viewer)
{
    if (_config_dialog != 0)
        delete _config_dialog;

    _config_dialog = new ConfigDialog(viewer);

    QDockWidget *config_dock = new QDockWidget("Config");
    config_dock->setAllowedAreas(Qt::LeftDockWidgetArea);
    config_dock->setFeatures(QDockWidget::DockWidgetMovable |
                             QDockWidget::DockWidgetFloatable);
    config_dock->setWidget(_config_dialog);

    addDockWidget(Qt::LeftDockWidgetArea, config_dock);

    connect(_config_dialog, SIGNAL(showWidget(QWidget *)),
            this, SLOT(showInRightDock(QWidget *)));
}

void MainWindow::showInRightDock(QWidget *widg, const char *title)
{
    if (_right_dock != 0){
        removeDockWidget(_right_dock);
        delete _right_dock;
        _right_dock = 0;
    }

    _right_dock = new QDockWidget(title);
    _right_dock->setAllowedAreas(Qt::RightDockWidgetArea);
    _right_dock->setFeatures(QDockWidget::DockWidgetClosable |
                             QDockWidget::DockWidgetMovable |
                             QDockWidget::DockWidgetFloatable);
    _right_dock->setWidget(widg);

    addDockWidget(Qt::RightDockWidgetArea, _right_dock);
}
