/**
 * SVT
 * ----------
 * Copyright (c)2007,2008 Daniel Fiser <danfis (at) danfis (dot) cz>
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

#ifndef _CONFIG_DIALOG_HPP_
#define _CONFIG_DIALOG_HPP_

#include <QScrollArea>
#include "viewer.hpp"

/**
 * Dialog which provides configuration of all Objects managed by viewer
 */
class ConfigDialog : public QScrollArea {
    Q_OBJECT

  private:
    Viewer *_viewer;

    /**
     * Build controls for each Object
     */
    QWidget *_buildObj(ObjData *, QString name = "");
    QWidget *_buildDefaultStyle(QString title = "");

  private slots:
    void showWidgetSlot(QWidget *widg)
        { emit showWidget(widg); }
  public:
    ConfigDialog(Viewer *viewer);
    virtual ~ConfigDialog(){}

  signals:
    void showWidget(QWidget *widg);
};
#endif
