/**
 * Coin3dTools
 * ------------
 * Copyright (c)2007 Daniel Fiser <danfis (at) danfis (dot) cz>
 *
 *
 * This file is part of Coin3dTools
 *
 * Coin3dTools is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Coin3dTools is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Coin3dTools.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _SVT_PARSER_H_
#define _SVT_PARSER_H_

#include <stdio.h>

#include "obj.h"

/**
 * Main structure of parser.
 */
struct _svt_parser_t {
    FILE *input;

    svt_obj_t *objs;
    int objs_len;
};
typedef struct _svt_parser_t svt_parser_t;

svt_parser_t *svtParserNew();
void svtParserDelete(svt_parser_t *);

void svtParserSetInput(svt_parser_t *parser, FILE *input);
#endif
