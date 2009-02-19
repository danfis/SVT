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
