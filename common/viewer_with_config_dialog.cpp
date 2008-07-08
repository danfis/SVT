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

#include "config_dialog.hpp"
#include "viewer_with_config_dialog.hpp"


#include "viewer_with_config_dialog.moc"

ViewerWithConfigDialog::ViewerWithConfigDialog(QWidget *parent, const char *name)
    : Viewer(parent, name), _conf_dialog(0), _conf_button(0)
{
}

void ViewerWithConfigDialog::show()
{
    _setUpConfigDialog();

    Viewer::show();
}

static void ConfigDialogCallback(bool pressed, Viewer *, void *cl);
void ViewerWithConfigDialog::_setUpConfigDialog()
{
    _conf_button = new TogglePushButton((Viewer *)this, ConfigDialogCallback,
                                        (void *)&_conf_dialog);

    addAppPushButton(_conf_button);
}
static void ConfigDialogCallback(bool pressed, Viewer *viewer, void *cl)
{
    ConfigDialog **dialog = (ConfigDialog **)cl;

    if (pressed && *dialog == 0){
        *dialog = new ConfigDialog((ViewerWithConfigDialog *)viewer);
        (*dialog)->show();
        viewer->connect(*dialog, SIGNAL(finished(int)),
                        viewer, SLOT(offConfigDialog(int)));
    }

    if (!pressed && *dialog != 0){
        delete *dialog;
        *dialog = 0;
    }
}

void ViewerWithConfigDialog::offConfigDialog(int)
{
    _conf_dialog = 0;
    _conf_button->setChecked(false);
}
