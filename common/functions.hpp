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

#ifndef COMMON_FUNCTIONS_HPP_
#define COMMON_FUNCTIONS_HPP_

#include <QRect>
#include <QRectF>

#include "parser/parser.h"
#include "parser/obj.h"

namespace SVT {

namespace Common {


bool parseFloat(const char *str, float *f);
bool parseInt(const char *str, int *i);
bool parseFloatList(const char *str, int len, float *nums);

void chooseRandomColor(float *r, float *g, float *b);

void colorToHex(char str[7], const float color[3]);

inline void rectFToRect(const QRectF &rf, QRect &r)
{
    r.setTop((int)rf.top());
    r.setBottom((int)rf.bottom() + 1);
    r.setLeft((int)rf.left());
    r.setRight((int)rf.right() + 1);
}

inline void rectToRectF(const QRect &r, QRectF &rf)
{
    rf.setTop(r.top());
    rf.setBottom(r.bottom());
    rf.setLeft(r.left());
    rf.setRight(r.right());
}



void parseAll(int argc, char *argv[], svt_parser_t *parser);
void parseCmd(int argc, char *argv[], svt_parser_t *parser);
void parseStdin(svt_parser_t *parser);

}

}
#endif

