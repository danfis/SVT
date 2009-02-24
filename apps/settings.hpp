/**
 * SVT
 * ----------
 * Copyright (c)2007,2008,2009 Daniel Fiser <danfis (at) danfis (dot) cz>
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

#ifndef SETTINGS_HPP
#define SETTINGS_HPP

struct Settings {
    static bool all_off;
    static bool points_off;
    static bool edges_off;
    static bool faces_off;

    static float point_size;
    static float edge_width;

    static float point_color[3]; /* rgb */
    static float edge_color[3];
    static float face_color[3];

    static bool colour_points;
    static bool colour_edges;
    static bool colour_faces;

#ifdef TO_SVG
    static int svg_width;
    static bool svg_view_box_enabled;
    static float svg_view_box[4];
    static int svg_precision;
    static float svg_bg_color[3];
#endif
};

#endif
