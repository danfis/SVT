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

#include "toggle_push_button.hpp"
#include "viewer.hpp"


#include "toggle_push_button.moc"

TogglePushButton::TogglePushButton(Viewer *v,
                     TogglePushButtonCallback callback, void *closure,
                     const char *text)
    : QPushButton(text), _viewer(v), _callback(callback),
      _closure(closure)
{
    setCheckable(true);
    connect(this, SIGNAL(clicked()), this, SLOT(callCallback()));
}

TogglePushButton::~TogglePushButton()
{
}

void TogglePushButton::callCallback()
{
    _callback(isChecked(), _viewer, _closure);
}
