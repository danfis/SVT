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
#include "coin3d/coin3d.hpp"
#include "common/msg.hpp"

void parseObjData()
{
    svt_obj_t *objs;
    SVT::Coin3d::Obj *data;

    if (svtParserParse(parser) != 0){
        ERR("Can't parse input");
        return;
    }

    objs = svtParserObjsSteal(parser, NULL);
    while (objs != NULL){
        data = new SVT::Coin3d::Obj(objs);

        applyDefaultSettings(data);

        SVT::Coin3d::Coin3d::addObj(data);

        objs = svtObjDelete(objs);
    }
}


void applyDefaultSettings(SVT::Coin3d::Obj *obj)
{
    float r, g, b;

    obj->setAllOn(!Settings::all_off);
    obj->setPointsOn(!Settings::points_off);
    obj->setEdgesOn(!Settings::edges_off);
    obj->setFacesOn(!Settings::faces_off);

    obj->setPointSize(Settings::point_size);
    obj->setEdgeWidth(Settings::edge_width);

    // colour elemets if requested
    if (Settings::colour_points){
        chooseRandomColor(&r, &g, &b);
        obj->setPointColor(r, g, b);
    }else if (!obj->pointColorAlreadySet()){
        r = Settings::point_color[0];
        g = Settings::point_color[1];
        b = Settings::point_color[2];
        obj->setPointColor(r, g, b);
    }

    if (Settings::colour_edges){
        chooseRandomColor(&r, &g, &b);
        obj->setEdgeColor(r, g, b);
    }else if (!obj->edgeColorAlreadySet()){
        r = Settings::edge_color[0];
        g = Settings::edge_color[1];
        b = Settings::edge_color[2];
        obj->setEdgeColor(r, g, b);
    }

    if (Settings::colour_faces){
        chooseRandomColor(&r, &g, &b);
        obj->setFaceColor(r, g, b);
    }else if (obj->faceColorAlreadySet()){
        r = Settings::face_color[0];
        g = Settings::face_color[1];
        b = Settings::face_color[2];
        obj->setFaceColor(r, g, b);
    }
}
