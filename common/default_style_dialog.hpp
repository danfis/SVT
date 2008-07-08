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

#ifndef _DEFAULT_STYLE_WINDOW_HPP_
#define _DEFAULT_STYLE_WINDOW_HPP_

#include <QDialog>
#include <QPushButton>
#include "objdata.hpp"

class Viewer;

/**
 * Class which provides dialog for configuring of properties(style) of one
 * ObjData object.
 */
class DefaultStyleDialog : public QWidget {
    Q_OBJECT

  private:
    Viewer *_viewer;

    QWidget *_buildPoints();
    QWidget *_buildEdges();
    QWidget *_buildFaces();

    void lock();
    void unlock();
  private slots:
    void changePointsSize(double val);
    void changePointsDiffuseColorRed(double val);
    void changePointsDiffuseColorGreen(double val);
    void changePointsDiffuseColorBlue(double val);
    void turnOnOffPoints(bool pressed);
    void changeEdgesSize(double val);
    void changeEdgesDiffuseColorRed(double val);
    void changeEdgesDiffuseColorGreen(double val);
    void changeEdgesDiffuseColorBlue(double val);
    void turnOnOffEdges(bool pressed);
    void changeFacesDiffuseColorRed(double val);
    void changeFacesDiffuseColorGreen(double val);
    void changeFacesDiffuseColorBlue(double val);
    void turnOnOffFaces(bool pressed);

  public:
    DefaultStyleDialog(QWidget *parent, Viewer *viewer);
    virtual ~DefaultStyleDialog(){}
};

/**
 * Button by which is possible to show DefaultStyleDialog
 */
class DefaultStylePushButton : public QPushButton {
    Q_OBJECT

  private:
    QWidget *_parent;
    Viewer *_viewer;

  public:
    DefaultStylePushButton(Viewer *viewer, const QString = "");
    ~DefaultStylePushButton(){}

  private slots:
    void showDialogInternal();

  signals:
    void showDialog(QWidget *widg);
};
#endif

