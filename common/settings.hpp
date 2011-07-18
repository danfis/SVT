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

#ifndef COMMON_SETTINGS_HPP
#define COMMON_SETTINGS_HPP

#include <list>

namespace SVT {

namespace Common {

struct Settings {
    enum Type {
        TYPE_VIEWER2D,
        TYPE_VIEWER3D,
        TYPE_VIEWER3DLIVE,
        TYPE_VIEWER2DLIVE,
        TYPE_TO_SVG,
        TYPE_TO_PNG,
        TYPE_NONE
    };

    Type type;

    bool all_off;
    bool points_off;
    bool edges_off;
    bool faces_off;

    float point_size;
    float edge_width;

    float point_color[3]; /* rgb */
    float edge_color[3];
    float face_color[3];

    bool colour_points;
    bool colour_edges;
    bool colour_faces;

    float bg_color[3];
    bool no_bg;

    bool point_color_changed;

    int svg_width;
    bool svg_view_box_enabled;
    float svg_view_box[4];
    int svg_precision;

    long sleeptime; // in miliseconds
    unsigned int hunksize;
    long delay;

    std::list<char *> errors;

    Settings();

    /**
     * Set up settings from command line options.
     * Returns unused options.
     */
    char **setUpFromOptions(int argc, char *argv[], int *len);

    /**
     * Adds error message to list of errors.
     */
    void addError(const char *);

    /**
     * Returns true if some errors occured.
     */
    bool errorsOccured() const { return errors.size() > 0; }

    /**
     * Prints usage text to stderr.
     */
    void usage(int argc, char *argv[]);
};

extern Settings settings;

}

}
#endif
