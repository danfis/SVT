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

#include <getopt.h>

#include "parse_func.h"

/**
 * Indicates if some these elements should be coloured
 */
extern bool colour_points;
extern bool colour_edges;
extern bool colour_faces;

extern char **args;
extern int num_args;

extern struct option options[];

enum Options {
    HELP = 'h',
    ALL_OFF,
    POINTS_OFF,
    EDGES_OFF,
    FACES_OFF,
    POINT_SIZE,
    EDGE_WIDTH,
    POINT_COLOR_RED,
    POINT_COLOR_GREEN,
    POINT_COLOR_BLUE,
    EDGE_COLOR_RED,
    EDGE_COLOR_GREEN,
    EDGE_COLOR_BLUE,
    FACE_COLOR_RED,
    FACE_COLOR_GREEN,
    FACE_COLOR_BLUE,
    COLOUR_POINTS,
    COLOUR_EDGES,
    COLOUR_FACES,
    OPTIONS_END
};

void chooseRandomColor(float *r, float *g, float *b);
void parseObjData();

void usage(int argc, char *argv[], const char *optstr = 0);


#endif
