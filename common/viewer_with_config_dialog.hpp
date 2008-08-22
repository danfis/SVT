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

#ifndef _VIEWER_ADV_HPP_
#define _VIEWER_ADV_HPP_

#include "viewer.hpp"
#include "toggle_push_button.hpp"

class ConfigDialog;


class ViewerWithConfigDialog : public Viewer {
    Q_OBJECT

  protected:
    ConfigDialog *_conf_dialog; /*! holds pointer to shown ConfigDialog
                                    or 0 (if no ConfigDialog is shown) */
    TogglePushButton *_conf_button; /*! button using which is possible to
                                        show/hide ConfigDialog */

    virtual void _setUpConfigDialog();

    friend class ConfigDialog;
  protected slots:
    /**
     * Slot used by _conf_button and _conf_dialog
     */
    void offConfigDialog(int);

  public:
    ViewerWithConfigDialog(QWidget *parent, const char *name = "");
    void show();
};
#endif

