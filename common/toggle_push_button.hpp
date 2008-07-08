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

#ifndef _VIEWER_PUSH_BUTTON_H_
#define _VIEWER_PUSH_BUTTON_H_

#include <QPushButton>
#include <Inventor/nodes/SoSwitch.h>

class Viewer;

typedef void (*TogglePushButtonCallback)(bool pressed, Viewer *,
                                         void *closure);

/**
 * PushButton which provides functionality of toggle/released button.
 */
class TogglePushButton : public QPushButton {
    Q_OBJECT

  private:
    Viewer *_viewer; /*! pointer to Viewer object */
    TogglePushButtonCallback _callback;
    void *_closure;

  private slots:
    void callCallback();

  public:
    TogglePushButton(Viewer *, TogglePushButtonCallback, void *closure = NULL,
                     const char *text = NULL);
    ~TogglePushButton();
};
#endif
