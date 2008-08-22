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

#ifndef _SVT_LEXER_H_
#define _SVT_LEXER_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Defined tokens */
#define T_INT_NUM 258
#define T_FLT_NUM 259
#define T_POINTS 260
#define T_EDGES 261
#define T_FACES 262
#define T_DELIM 263
#define T_ERROR 264
#define T_POINTS2D 265
#define T_NAME 267
#define T_POLY 268
#define T_POLYLINE 269

#define YY_BUFSIZE 1000

struct _svt_yylval_t {
    float flt_num;
    int int_num;
    int lineno;
    char c;
    char buffer[YY_BUFSIZE];
};
typedef struct _svt_yylval_t svt_yylval_t;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
