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

#ifndef _MAIN_WINDOW_HPP_
#define _MAIN_WINDOW_HPP_

#include <QMainWindow>
#include <QDockWidget>
#include <QStatusBar>
#include "config_dialog.hpp"
#include "viewer.hpp"

class MainWindow : public QMainWindow {
    Q_OBJECT

    ConfigDialog *_config_dialog;
    QDockWidget *_right_dock;
    QStatusBar *_status_bar;

  signals:
    void _showMessageInStatusBar(const QString &msg, int timeout);

  public:
    MainWindow(QWidget *parent = 0, Qt::WindowFlags flags = 0);
    ~MainWindow();

    void createConfigDialog(Viewer *viewer);

  public slots:
    void showInRightDock(QWidget *widg, const char *title = "");

    inline void showMessageInStatusBar(const QString &msg, int timeout = 0)
        { emit _showMessageInStatusBar(msg, timeout); }
};

#endif
