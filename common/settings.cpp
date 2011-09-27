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

#include <getopt.h>
#include <cstdlib>
#include <cstring>
#include <iostream>

#include "settings.hpp"
#include "functions.hpp"

namespace SVT {

namespace Common {

Settings settings;


enum Options {
    HELP = 'h',

    VIEWER2D,
    VIEWER3D,
    VIEWER3DLIVE,
    VIEWER2DLIVE,
    TO_SVG,
    TO_PNG,
    TO_POV,

    ALL_OFF,
    POINTS_OFF,
    EDGES_OFF,
    FACES_OFF,
    POINT_SIZE,
    EDGE_WIDTH,
    POINT_COLOR,
    EDGE_COLOR,
    FACE_COLOR,
    COLOUR_POINTS,
    COLOUR_EDGES,
    COLOUR_FACES,

    OUTPUT_WIDTH,
    VIEW_BOX,
    PRECISION,
    BG_COLOR,
    NO_BG,

    SLEEPTIME,
    HUNKSIZE,
    DELAY,

    OPTIONS_END
};


struct option options[] = {
    { "help", no_argument, NULL, HELP },

    { "2d", no_argument, NULL, VIEWER2D },
    { "3d", no_argument, NULL, VIEWER3D },
    { "3d-live", no_argument, NULL, VIEWER3DLIVE },
    { "2d-live", no_argument, NULL, VIEWER2DLIVE },
    { "to-svg", no_argument, NULL, TO_SVG },
    { "to-png", no_argument, NULL, TO_PNG },
    { "to-pov", no_argument, NULL, TO_POV },

    { "all-off", no_argument, NULL, ALL_OFF },
    { "points-off", no_argument, NULL, POINTS_OFF },
    { "edges-off", no_argument, NULL, EDGES_OFF },
    { "faces-off", no_argument, NULL, FACES_OFF },
    { "point-size", required_argument, NULL, POINT_SIZE },
    { "edge-width", required_argument, NULL, EDGE_WIDTH },
    { "point-color", required_argument, NULL, POINT_COLOR },
    { "edge-color", required_argument, NULL, EDGE_COLOR },
    { "face-color", required_argument, NULL, FACE_COLOR },
    { "colour-points", no_argument, NULL, COLOUR_POINTS },
    { "colour-edges",  no_argument, NULL, COLOUR_EDGES },
    { "colour-faces",  no_argument, NULL, COLOUR_FACES },

    { "output-width", required_argument, NULL, OUTPUT_WIDTH },
    { "view-box", required_argument, NULL, VIEW_BOX },
    { "precision", required_argument, NULL, PRECISION },
    { "bg-color", required_argument, NULL, BG_COLOR },
    { "no-bg", no_argument, NULL, NO_BG },

    { "sleeptime", required_argument, NULL, SLEEPTIME },
    { "hunksize", required_argument, NULL, HUNKSIZE },
    { "delay", required_argument, NULL, DELAY },

    { NULL, 0, NULL, 0 }
};

Settings::Settings()
{
    // default settings
    type = TYPE_NONE;

    all_off    = false;
    points_off = false;
    edges_off  = false;
    faces_off  = false;

    point_size = 2.;
    edge_width = 1.;

    point_color[0] = 0.;
    point_color[1] = 0.;
    point_color[2] = 0.;
    edge_color[0]  = 0.;
    edge_color[1]  = 0.;
    edge_color[2]  = 1.;
    face_color[0]  = 0.;
    face_color[1]  = 1.;
    face_color[2]  = 0.;

    colour_points = false;
    colour_edges  = false;
    colour_faces  = false;

    point_color_changed = false;

    svg_width = 500;
    svg_view_box_enabled = false;
    svg_view_box[0] = 0.;
    svg_view_box[1] = 0.;
    svg_view_box[2] = 100.;
    svg_view_box[3] = 100.;
    svg_precision = 5;
    bg_color[0] = 1.;
    bg_color[1] = 1.;
    bg_color[2] = 1.;
    no_bg = false;

    sleeptime = 1000; // default sleeptime is 1s
    hunksize = 1;
}




#define FLOAT(option_name) \
    if (!parseFloat(optarg, &f)) \
        addError("Error: option \"" option_name "\" requires float argument")

#define FLOAT3(option_name) \
    if (!parseFloatList(optarg, 3, fl)) \
        addError("Error: option \"" option_name "\" requires triplet of floats as argument.")

#define FLOAT4(option_name) \
    if (!parseFloatList(optarg, 4, fl)) \
        addError("Error: option \"" option_name "\" requires four floats as argument.")

#define INT(option_name) \
    if (!parseInt(optarg, &i)) \
        addError("Error: option \"" option_name "\"  requires int argument.")

#define LONG(option_name) \
    if (!parseLong(optarg, &l)) \
        addError("Error: option \"" option_name "\"  requires int argument.")

char **Settings::setUpFromOptions(int argc, char *argv[], int *len)
{
    int c, option_index;
    float f;
    char **args;
    float fl[4];
    int i;
    long l;
    bool usag = false;

    while ((c = getopt_long(argc, argv, "h", options, &option_index)) != -1){
        switch (c){
            case HELP:
                usag = true;
                break;

            case VIEWER2D:
                type = TYPE_VIEWER2D;
                break;
            case VIEWER3D:
                type = TYPE_VIEWER3D;
                break;
            case VIEWER3DLIVE:
                type = TYPE_VIEWER3DLIVE;
                break;
            case VIEWER2DLIVE:
                type = TYPE_VIEWER2DLIVE;
                break;
            case TO_SVG:
                type = TYPE_TO_SVG;
                break;

            case TO_PNG:
                type = TYPE_TO_PNG;
                break;
            case TO_POV:
                type = TYPE_TO_POV;
                break;

            case ALL_OFF:
                all_off = true;
                break;
            case POINTS_OFF:
                points_off = true;
                break;
            case EDGES_OFF:
                edges_off = true;
                break;
            case FACES_OFF:
                faces_off = true;
                break;
            case POINT_SIZE:
                FLOAT("--point-size");
                point_size = f;
                break;
            case EDGE_WIDTH:
                FLOAT("--edge-width");
                edge_width = f;
                break;
            case POINT_COLOR:
                FLOAT3("--point-color");
                point_color[0] = fl[0];
                point_color[1] = fl[1];
                point_color[2] = fl[2];
                point_color_changed = true;
                break;
            case EDGE_COLOR:
                FLOAT3("--edge-color");
                edge_color[0] = fl[0];
                edge_color[1] = fl[1];
                edge_color[2] = fl[2];
                break;
            case FACE_COLOR:
                FLOAT3("--face-color");
                face_color[0] = fl[0];
                face_color[1] = fl[1];
                face_color[2] = fl[2];
                break;
            case COLOUR_POINTS:
                colour_points = true;
                break;
            case COLOUR_EDGES:
                colour_edges = true;
                break;
            case COLOUR_FACES:
                colour_faces = true;
                break;

            case OUTPUT_WIDTH:
                INT("--output-width");
                svg_width = i;
                break;
            case VIEW_BOX:
                FLOAT4("--view-box");
                svg_view_box_enabled = true;
                svg_view_box[0] = fl[0];
                svg_view_box[1] = fl[1];
                svg_view_box[2] = fl[2];
                svg_view_box[3] = fl[3];
                break;
            case PRECISION:
                INT("--precision");
                svg_precision = i;
                break;
            case BG_COLOR:
                FLOAT3("--bg-color");
                bg_color[0] = fl[0];
                bg_color[1] = fl[1];
                bg_color[2] = fl[2];
                break;
            case NO_BG:
                no_bg = true;
                break;

            case SLEEPTIME:
                LONG("--sleeptime");
                sleeptime = l;
                break;
            case HUNKSIZE:
                INT("--hunksize");
                hunksize = i;
                break;
            case DELAY:
                LONG("--delay");
                delay = l;
                break;

            default:
                usag = true;
        }
    }

    if (usag)
        usage(argc, argv);

    if (argc - optind > 0){
        args = argv + optind;
        *len = argc - optind;
    }else{
        args = 0;
        *len = 0;
    }

    return args;
}

void Settings::addError(const char *err)
{
    unsigned int len = strlen(err);
    char *e = new char[len + 1];

    memcpy(e, err, len);
    e[len] = 0;

    errors.push_back(e);
}

void Settings::usage(int argc, char *argv[])
{
    std::list<char *>::iterator it, it_end;

    it = errors.begin();
    it_end = errors.end();
    for (; it != it_end; ++it){
        std::cerr << *it << std::endl;
    }

    std::cerr << "Usage: " << argv[0] << " [ Options ] <file.txt" << std::endl;
    std::cerr << "          or" << std::endl;
    std::cerr << "       " << argv[0] << " [ Options ] file1.txt file2.txt ..." << std::endl;

/*
#ifdef VIEWER_LIVE
    std::cerr << "Usage: " << argv[0] << " [ Options ] staticobjs1.txt staticobjs2.txt ... <dynobjs.txt" << std::endl;
#endif
*/

    std::cerr << std::endl;
    std::cerr << "Options:" << std::endl;
    std::cerr << "  --help                      Show this help." << std::endl;
    std::cerr << "  --all-off                   Turn off all objects." << std::endl;
    std::cerr << "  --points-off                Turn off all points." << std::endl;
    std::cerr << "  --edges-off                 Turn off all edges." << std::endl;
    std::cerr << "  --faces-off                 Turn off all faces." << std::endl;
    std::cerr << std::endl;
    std::cerr << "  --point-size         float  Set size of points to specified value." << std::endl;
    std::cerr << "  --edge-width         float  Set width of edges to specified value." << std::endl;
    std::cerr << std::endl;
    std::cerr << "  --point-color        float,float,float  Set color of points." << std::endl;
    std::cerr << "  --edge-color         float,float,float  Set color of edges." << std::endl;
    std::cerr << "  --face-color         float,float,float  Set color of faces." << std::endl;
    std::cerr << "  --point-color-red    float  Set color of points to specified value." << std::endl;
    std::cerr << "  --point-color-green  float  Value must be between 0 and 1." << std::endl;
    std::cerr << "  --point-color-blue   float" << std::endl;
    std::cerr << "  --edge-color-red     float  Set color of edges to specified value." << std::endl;
    std::cerr << "  --edge-color-green   float  Value must be between 0 and 1." << std::endl;
    std::cerr << "  --edge-color-blue    float" << std::endl;
    std::cerr << "  --face-color-red     float  Set color of faces to specified value." << std::endl;
    std::cerr << "  --face-color-green   float  Value must be between 0 and 1." << std::endl;
    std::cerr << "  --face-color-blue    float" << std::endl;
    std::cerr << std::endl;
    std::cerr << "  --colour-points             Colour points from different objects by different color." << std::endl;
    std::cerr << "  --colour-edges              Colour edges from different objects by different color." << std::endl;
    std::cerr << "  --colour-faces              Colour faces from different objects by different color." << std::endl;

    std::cerr << std::endl;
    std::cerr << "  --output-width int    Width of resulting picture.  Heigh is computed from viewbox." << std::endl;
    std::cerr << "  --view-box     float,float,float,float  Proportions of viewbox." << std::endl;
    std::cerr << "                                          Parameters are: x, y, width, height with respect to svg coordinate system" << std::endl;
    std::cerr << "  --precision    int    Set up precision of floating point numbers when priting them out." << std::endl;
    std::cerr << "  --bg-color     float,float,float  Background color." << std::endl;
    std::cerr << "  --no-bg                           Turn off background color." << std::endl;

    std::cerr << std::endl;
    std::cerr << "  --sleeptime    int    Sleeptime (in ms) between frames in 'live' mode." << std::endl;
    std::cerr << "  --hunksize     int    Number of objects per frame in 'live' mode." << std::endl;
    std::cerr << "  --delay        int    Time before svt starts to read objects from stdin (in ms) in 'live' mode." << std::endl;

    exit(-1);
}


}

}
