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

#include "common_coin.hpp"
#include "common.hpp"
#include "settings.hpp"
#include "common/objdata.hpp"
#include "common/viewer.hpp"
#include "common/coin3dtools.hpp"

void parseObjData()
{
    svt_obj_t *objs;
    ObjData *data;
    Viewer *viewer;
    float r, g, b;

    viewer = Coin3dTools::viewer();

    if (svtParserParse(parser) != 0){
        ERR("Can't parse input");
        return;
    }

    objs = svtParserObjsSteal(parser, NULL);
    while (objs != NULL){
        data = new ObjData(objs);
        viewer->addObjData(data);

        // colour elemets if requested
        if (Settings::colour_points){
            chooseRandomColor(&r, &g, &b);
            data->material_points->diffuseColor.setValue(r, g, b);
        }
        if (Settings::colour_edges){
            chooseRandomColor(&r, &g, &b);
            data->material_edges->diffuseColor.setValue(r, g, b);
        }
        if (Settings::colour_faces){
            chooseRandomColor(&r, &g, &b);
            data->material_faces->diffuseColor.setValue(r, g, b);
        }

        objs = svtObjDelete(objs);
    }
}


void applySettings(Viewer *viewer)
{
    viewer->setDefaultSwitch(!Settings::all_off);
    viewer->setDefaultPointsSwitch(!Settings::points_off);
    viewer->setDefaultEdgesSwitch(!Settings::edges_off);
    viewer->setDefaultFacesSwitch(!Settings::faces_off);

    viewer->setDefaultPointSize(Settings::point_size);
    viewer->setDefaultLineWidth(Settings::edge_width);

    viewer->setDefaultPointsDiffuseColorRed(Settings::point_color[0]);
    viewer->setDefaultPointsDiffuseColorGreen(Settings::point_color[1]);
    viewer->setDefaultPointsDiffuseColorBlue(Settings::point_color[2]);
    viewer->setDefaultEdgesDiffuseColorRed(Settings::edge_color[0]);
    viewer->setDefaultEdgesDiffuseColorGreen(Settings::edge_color[1]);
    viewer->setDefaultEdgesDiffuseColorBlue(Settings::edge_color[2]);
    viewer->setDefaultFacesDiffuseColorRed(Settings::face_color[0]);
    viewer->setDefaultFacesDiffuseColorGreen(Settings::face_color[1]);
    viewer->setDefaultFacesDiffuseColorBlue(Settings::face_color[2]);
}
