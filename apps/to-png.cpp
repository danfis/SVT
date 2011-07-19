/**
 * SVT
 * ----------
 * Copyright (c)2011 Daniel Fiser <danfis (at) danfis (dot) cz>
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

#include <iostream>
#include <cstdlib>
#include <float.h>
#include <cairo.h>
#include <math.h>
using namespace std;

#include "common/msg.hpp"
#include "common/settings.hpp"
#include "common/functions.hpp"
#include "parser/parser.h"
#include "parser/obj.h"

using SVT::Common::settings;
using SVT::Common::colorToHex;
using SVT::Common::chooseRandomColor;

static void toPNG(svt_obj_t *objs);
static cairo_status_t cairoWriteFn(void *closure, const unsigned char *data,
                                   unsigned int length);

static void size(svt_obj_t *objs,
                 int *width, int *height, float view_box[4]);


int mainToPNG(int argc, char *argv[], svt_parser_t *parser)
{
    int len;
    svt_obj_t *o;

    o = svtParserObjs(parser, &len);
    if (len > 0)
        toPNG(o);

    return 0;
}

void toPNG(svt_obj_t *objs)
{
    svt_obj_t *objs2;
    ostream &out = cout;
    const svt_point_t *points;
    const svt_edge_t *edges;
    const svt_face_t *faces;
    int points_len, edges_len, faces_len;
    float colorf[3];
    const float *col;
    int width, height;
    float view_box[4];
    float xscale, yscale, xoff, yoff, x, y, x2, y2;
    float el_size;
    float transform_matrix[9] =
        { 1.f, 0.f, 0.f,
          0.f, -1.f, 0.f,
          0.f, 0.f, 1.f };
    cairo_surface_t *surface;
    cairo_t *cr;

    // first transform points to fit to svg coordinate system:
    objs2 = objs;
    while (objs2 != NULL){
        svtObjTransformPoints(objs2, transform_matrix);
        objs2 = svtObjNext(objs2);
    }

    size(objs, &width, &height, view_box);
    xscale = width / view_box[2];
    yscale = height / view_box[3];
    xoff   = -view_box[0];
    yoff   = -view_box[1];

    out.precision(settings.svg_precision);
    out.setf(ios::fixed);

    // create cairo context
    surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height);
    cr = cairo_create(surface);

    // draw backgroud
    if (!settings.no_bg){
        cairo_set_source_rgb(cr, settings.bg_color[0],
                                 settings.bg_color[1],
                                 settings.bg_color[2]);
        cairo_move_to(cr, 0, 0);
        cairo_line_to(cr, width, 0);
        cairo_line_to(cr, width, height);
        cairo_line_to(cr, 0, height);
        cairo_line_to(cr, 0, 0);
        cairo_fill(cr);
    }

    for (int i=0; objs != NULL; i++, objs = svtObjNext(objs)){
        points = svtObjPoints(objs, &points_len);
        edges = svtObjEdges(objs, &edges_len);
        faces = svtObjFaces(objs, &faces_len);

        // Faces:
        if (!settings.faces_off && svtObjFacesOff(objs) != 1){
            col = settings.face_color;
            if (settings.colour_faces){
                chooseRandomColor(colorf, colorf + 1, colorf + 2);
                col = colorf;
            }else if (svtObjFaceColor(objs) != NULL){
                col = svtObjFaceColor(objs);
            }

            for (int i=0; i < faces_len; i++){
                if (faces[i][0] < points_len
                    && faces[i][1] < points_len
                    && faces[i][2] < points_len){

                    cairo_set_source_rgb(cr, col[0], col[1], col[2]);

                    x = (points[faces[i][0]][0] + xoff) * xscale;
                    y = (points[faces[i][0]][1] + yoff) * yscale;
                    cairo_move_to(cr, x, y);

                    x = (points[faces[i][1]][0] + xoff) * xscale;
                    y = (points[faces[i][1]][1] + yoff) * yscale;
                    cairo_line_to(cr, x, y);

                    x = (points[faces[i][2]][0] + xoff) * xscale;
                    y = (points[faces[i][2]][1] + yoff) * yscale;
                    cairo_line_to(cr, x, y);

                    x = (points[faces[i][0]][0] + xoff) * xscale;
                    y = (points[faces[i][0]][1] + yoff) * yscale;
                    cairo_line_to(cr, x, y);

                    cairo_fill(cr);
                }
            }
        }

        // Edges:
        if (!settings.edges_off && svtObjEdgesOff(objs) != 1){
            col = settings.edge_color;
            if (settings.colour_edges){
                chooseRandomColor(colorf, colorf + 1, colorf + 2);
                col = colorf;
            }else if (svtObjEdgeColor(objs) != NULL){
                col = svtObjEdgeColor(objs);
            }

            el_size = settings.edge_width;
            if (svtObjEdgeWidth(objs) > 0.f){
                el_size = svtObjEdgeWidth(objs);
            }

            for (int i=0; i < edges_len; i++){
                if (edges[i][0] < points_len && edges[i][1] < points_len){
                    x = (points[edges[i][0]][0] + xoff) * xscale;
                    y = (points[edges[i][0]][1] + yoff) * yscale;
                    x2 = (points[edges[i][1]][0] + xoff) * xscale;
                    y2 = (points[edges[i][1]][1] + yoff) * yscale;

                    cairo_set_line_width(cr, el_size);
                    cairo_set_source_rgb(cr, col[0], col[1], col[2]);
                    cairo_move_to(cr, x, y);
                    cairo_line_to(cr, x2, y2);
                    cairo_stroke (cr);
                }
            }
        }

        // Points:
        if (!settings.points_off && svtObjPointsOff(objs) != 1){
            col = settings.point_color;
            if (settings.colour_points){
                chooseRandomColor(colorf, colorf + 1, colorf + 2);
                col = colorf;
            }else if (svtObjPointColor(objs) != NULL){
                col = svtObjPointColor(objs);
            }

            el_size = settings.point_size;
            if (svtObjPointSize(objs) > 0.f){
                el_size = svtObjPointSize(objs);
            }

            for (int i=0; i < points_len; i++){
                x = (points[i][0] + xoff) * xscale;
                y = (points[i][1] + yoff) * yscale;

                cairo_set_source_rgb(cr, col[0], col[1], col[2]);
                cairo_move_to(cr, x, y);
                cairo_arc(cr, x, y, el_size, 0, 2 * M_PI);
                cairo_fill(cr);
            }
        }

    }


    // write to file and close cairo
    cairo_destroy(cr);
    cairo_surface_write_to_png_stream(surface, cairoWriteFn, (void *)stdout);
    cairo_surface_destroy(surface);
}

void size(svt_obj_t *objs,
          int *width, int *height, float view_box[4])
{
    if (settings.svg_view_box_enabled){
        view_box[0] = settings.svg_view_box[0];
        view_box[1] = -1.f * settings.svg_view_box[1];
        view_box[2] = settings.svg_view_box[2];
        view_box[3] = settings.svg_view_box[3];
    }else{
        // compute viewbox from points:
        const svt_point_t *points;
        int len;
        float bottomleft[2], topright[2];

        bottomleft[0] = bottomleft[1] = 1000000.;
        topright[0] = topright[1] = -1000000.;
        while (objs != NULL){
            points = svtObjPoints(objs, &len);

            for (int i=0; i < len; i++){
                if (points[i][0] < bottomleft[0])
                    bottomleft[0] = points[i][0];
                if (points[i][0] > topright[0])
                    topright[0] = points[i][0];
                if (points[i][1] < bottomleft[1])
                    bottomleft[1] = points[i][1];
                if (points[i][1] > topright[1])
                    topright[1] = points[i][1];
            }

            objs = svtObjNext(objs);
        }

        view_box[0] = bottomleft[0];
        view_box[1] = bottomleft[1];
        view_box[2] = topright[0] - bottomleft[0];
        view_box[3] = topright[1] - bottomleft[1];
    }

    *width = settings.svg_width;
    *height = (int)(((float)*width / view_box[2]) * view_box[3]);
}

static cairo_status_t cairoWriteFn(void *closure, const unsigned char *data,
                                   unsigned int length)
{
    FILE *out = (FILE *)closure;
    size_t wlen;

    wlen = fwrite(data, sizeof(unsigned char), length, out);
    if (wlen == length)
        return CAIRO_STATUS_SUCCESS;
    return CAIRO_STATUS_WRITE_ERROR;
}
