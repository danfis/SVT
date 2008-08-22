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

#ifndef COMMON_HPP
#define COMMON_HPP

#include "parser/parse_func.h"

void chooseRandomColor(float *r, float *g, float *b);

void usage(int argc, char *argv[], const char *optstr = 0);

char **processOptions(int argc, char *argv[], int *len);

void colorToHex(char str[7], float color[3]);

bool parseFloat(const char *str, float *f);
bool parseInt(const char *str, int *i);
bool parseFloatList(const char *str, int len, float *nums);
#endif
