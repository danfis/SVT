/**
 * Coin3dTools
 * ----------
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

#ifndef _VIEWER_COMMON_HPP
#define _VIEWER_COMMON_HPP

#include "viewer.hpp"

void chooseRandomColor(float *r, float *g, float *b);
void parseObjData();

void usage(int argc, char *argv[], const char *optstr = 0);


char **processOptions(int argc, char *argv[], int *len);
void applySettings(Viewer *viewer);

#endif
