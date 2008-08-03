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

#include "lexer.h"
#include "lexer_gen.h"
#include "obj.h"

/**
 * Main structure of parser.
 */
struct _svt_parser_t {
    FILE *input;
    svt_yylval_t yylval;
    yyscan_t scanner;

    int cur_tok;
    svt_obj_t *cur_obj;

    svt_obj_t *objs;
    int objs_len;
};
typedef struct _svt_parser_t svt_parser_t;

/**
 * Allocates memory and initialize svt_parser_t struct.
 *
 * Input stream is set as stdin.
 */
svt_parser_t *svtParserNew();

/**
 * Delete all allocated memory.
 *
 * This function also delete list of objs stored inside parser struct, so
 * if you want to you returned objs after this call or you want to delete
 * them by yourself, use svtParserObjsSteal() instead of svtParserObjs()
 * for getting list of objs.
 */
void svtParserDelete(svt_parser_t *);

/**
 * Changes input stream.
 */
void svtParserSetInput(svt_parser_t *parser, FILE *input);

/**
 * Returns head of list of objects previously parsed.
 *
 * If len is not NULL, there is returned length of list.
 * This function only returns head of list, but - after this call - parser
 * still internaly manage this list, so it shouldn't be deleted or
 * modified.
 */
svt_obj_t *svtParserObjs(svt_parser_t *parser, int *len);

/**
 * Similary function to svtParserObjs() but this function also steals
 * pointer from parser.
 *
 * The difference is that after calling this function parser no more manage
 * list of objs, so this list _must_ be deleted by caller
 * (see svtObjDelete()).
 */
svt_obj_t *svtParserObjsSteal(svt_parser_t *parser, int *len);


/**
 * Parse input stream into svt_obj_t structs stored internaly by parser.
 *
 * See svtParserObjs() and svtParserObjsSteal()
 */
int svtParserParse(svt_parser_t *parser);
#endif
