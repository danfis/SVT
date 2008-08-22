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

#include "settings.hpp"

/* DEFAULT SETTINGS: */

bool Settings::all_off    = false;
bool Settings::points_off = false;
bool Settings::edges_off  = false;
bool Settings::faces_off  = false;

float Settings::point_size = 2.;
float Settings::edge_width = 1.;

float Settings::point_color[] = { 1., 1., 1. };
float Settings::edge_color[]  = { 0., 0., 1. };
float Settings::face_color[]  = { 0., 1., 0. };

bool Settings::colour_points = false;
bool Settings::colour_edges  = false;
bool Settings::colour_faces  = false;

#ifdef TO_SVG
int Settings::svg_width = 500;
bool Settings::svg_view_box_enabled = false;
float Settings::svg_view_box[] = { 0., 0., 100., 100. };
int Settings::svg_precision = 5;
float Settings::svg_bg_color[3] = { 0., 0., 0. };
#endif
