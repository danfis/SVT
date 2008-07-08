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

#ifndef _INIT_HPP_
#define _INIT_HPP_

#include <Inventor/Qt/SoQt.h>
#include <QWidget>
#include <QStatusBar>
#include "viewer.hpp"
#include "main_window.hpp"


class Coin3dTools {
  private:
    static MainWindow *_mainwin;
    static QWidget *_win;
    static QStatusBar *_status_bar;
    static Viewer *_viewer;

  public:
    /**
     * Initialize Coin3dTools lib
     */
    static void init(const char *title="");

    /**
     * Starts Coin3dTools previously initialized
     */
    static void mainLoop();

    /**
     * Finish everything (free memory etc...)
     */
    static void finish();

    /**
     * Creates and return Viewer instance. If Viewer is already created it
     * only returns pointer to it.
     */
    static Viewer *viewer();
};

#endif
