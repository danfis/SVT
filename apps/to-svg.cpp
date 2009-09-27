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

#include <iostream>
#include <cstdlib>
#include <float.h>
using namespace std;

#include "common/msg.hpp"
#include "common/settings.hpp"
#include "common/functions.hpp"
#include "parser/parser.h"
#include "parser/obj.h"

using SVT::Common::settings;
using SVT::Common::colorToHex;
using SVT::Common::chooseRandomColor;

static void toSvg(svt_obj_t *objs);
static void printPoint(const svt_point_t point,
                       const float colorf[3],
                       ostream &);
static void printEdge(const svt_point_t from,
                      const svt_point_t to,
                      const float colorf[3],
                      ostream &);
static void printFace(const svt_point_t p1,
                      const svt_point_t p2,
                      const svt_point_t p3,
                      const float colorf[3],
                      ostream &);

static void size(svt_obj_t *objs,
                 int *width, int *height, float view_box[4]);


int mainToSVG(int argc, char *argv[], svt_parser_t *parser)
{
    int len;
    svt_obj_t *o;

    o = svtParserObjs(parser, &len);
    if (len > 0)
        toSvg(o);

    return 0;
}

void toSvg(svt_obj_t *objs)
{
    svt_obj_t *objs2;
    ostream &out = cout;
    const svt_point_t *points;
    const svt_edge_t *edges;
    const svt_face_t *faces;
    int points_len, edges_len, faces_len;
    float colorf[3];
    const float *col;
    char color[7];
    int width, height;
    float view_box[4];
    float transform_matrix[9] =
        { 1.f, 0.f, 0.f,
          0.f, -1.f, 0.f,
          0.f, 0.f, 1.f };

    // first transform points to fit to svg coordinate system:
    objs2 = objs;
    while (objs2 != NULL){
        svtObjTransformPoints(objs2, transform_matrix);
        objs2 = svtObjNext(objs2);
    }

    size(objs, &width, &height, view_box);

    out.precision(settings.svg_precision);
    out.setf(ios::fixed);

    // header:
    out << "<?xml version=\"1.0\" standalone=\"no\"?>" << endl;
    out << "<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\" " << endl
        << "    \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">"
        << endl;

    out << "<svg"
        << " width=\"" << width << "px\""
        << " height=\"" << height << "px\""
        << " viewBox=\"" << view_box[0] << " " << view_box[1] << " "
                         << view_box[2] << " " << view_box[3] << "\""
        << endl
        << "       xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">" << endl;

    // background:
    colorToHex(color, settings.bg_color);
    out << "<rect"
        << " x=\"" << view_box[0] << "\""
        << " y=\"" << view_box[1] << "\""
        << " width=\"" << view_box[2] << "\""
        << " height=\"" << view_box[3] << "\""
        << " fill=\"#" << color << "\""
        << " stroke=\"none\" />" << endl << endl;


    // body:
    for (int i=0; objs != NULL; i++){
        points = svtObjPoints(objs, &points_len);
        edges = svtObjEdges(objs, &edges_len);
        faces = svtObjFaces(objs, &faces_len);

        out << "<g id=\"" << i << "\">" << endl;

        // FACES:
        if (!settings.faces_off){
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
                    printFace(points[faces[i][0]],
                              points[faces[i][1]],
                              points[faces[i][2]],
                              col,
                              cout);
                }
            }
        }

        // EDGES:
        if (!settings.edges_off){
            col = settings.edge_color;
            if (settings.colour_edges){
                chooseRandomColor(colorf, colorf + 1, colorf + 2);
                col = colorf;
            }else if (svtObjEdgeColor(objs) != NULL){
                col = svtObjEdgeColor(objs);
            }

            for (int i=0; i < edges_len; i++){
                if (edges[i][0] < points_len && edges[i][1] < points_len){
                    printEdge(points[edges[i][0]],
                              points[edges[i][1]],
                              col,
                              cout);
                }
            }
        }

        // POINTS:
        if (!settings.points_off){
            col = settings.point_color;
            if (settings.colour_points){
                chooseRandomColor(colorf, colorf + 1, colorf + 2);
                col = colorf;
            }else if (svtObjPointColor(objs) != NULL){
                col = svtObjPointColor(objs);
            }

            for (int i=0; i < points_len; i++){
                printPoint(points[i], col, out);
            }
        }

        out << "</g>" << endl;
        objs = svtObjNext(objs);
    }

    // footer:
    out << "</svg>" << endl;
}

void printPoint(const svt_point_t point,
                const float colorf[3],
                ostream &out)
{
    float x, y, move;
    char color[7];

    x = point[0];
    y = point[1];

    move = settings.point_size / 2;
    x -= move;
    y -= move;

    colorToHex(color, colorf);

    out << "\t<rect x=\"" << x << "\" y=\"" << y << "\""
        << " width=\"" << settings.point_size << "\""
        << " height=\"" << settings.point_size << "\""
        << " fill=\"#" << color << "\""
        << " stroke=\"none\" />" << endl;

}

void printEdge(const svt_point_t from,
               const svt_point_t to,
               const float colorf[3],
               ostream &out)
{
    float x1, y1, x2, y2;
    char color[7];

    x1 = from[0];
    y1 = from[1];
    x2 = to[0];
    y2 = to[1];

    colorToHex(color, colorf);

    out << "\t<line x1=\"" << x1 << "\" y1=\"" << y1 << "\""
        << " x2=\"" << x2 << "\" y2=\"" << y2 << "\""
        << " stroke=\"#" << color << "\""
        << " stroke-width=\"" << settings.edge_width << "\" />"
        << endl;
}


void printFace(const svt_point_t p1,
               const svt_point_t p2,
               const svt_point_t p3,
               const float colorf[3],
               ostream &out)
{
    float x1, y1, x2, y2, x3, y3;
    char color[7];

    x1 = p1[0];
    y1 = p1[1];
    x2 = p2[0];
    y2 = p2[1];
    x3 = p3[0];
    y3 = p3[1];

    colorToHex(color, colorf);

    out << "\t<polygon"
        << " points=\"" << x1 << "," << y1 << " "
                        << x2 << "," << y2 << " "
                        << x3 << "," << y3 << "\""
        << " fill=\"#" << color << "\""
        << " stroke=\"none\" />"
        << endl;
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
