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

%{
#include "lexer.h"
#include "parse_func.h"

#define PARSE_FLOAT(ret) \
    if (svtParseFloat(yytext, &yyextra->flt_num) != 0){ \
        return T_ERROR; \
    } \
    yyextra->lineno = yylineno; \
    return ret

#define PARSE_INT(ret) \
    if (svtParseInt(yytext, &yyextra->int_num) != 0){ \
        return T_ERROR; \
    } \
    yyextra->lineno = yylineno; \
    return ret

%}

%option noyywrap
%option yylineno
%option reentrant
%option extra-type="svt_yylval_t *"

DIGIT [0-9]
NONZERO [1-9]
ZERO "0"
SIGN [-+]
DOT "."
WHITESPACE [ \t\n]
COMMENT "#"
DELIM [-=+]
EXP [eE]

%s points points2d edges faces name poly polyline color polyface
%%
<INITIAL,points,points2d,poly,polyline,color,polyface>{SIGN}?{ZERO}({DOT}{DIGIT}*)?({EXP}{SIGN}?{DIGIT}+)?  { /* -0.1234e-23 */
    PARSE_FLOAT(T_FLT_NUM);
}

<INITIAL,points,points2d,poly,polyline,color,polyface>{SIGN}?{NONZERO}{DIGIT}*({DOT}{DIGIT}*)?({EXP}{SIGN}?{DIGIT}+)?  { /* -1043.1234e-23 */
    PARSE_FLOAT(T_FLT_NUM);
}

<edges,faces>{NONZERO}{DIGIT}* {
    PARSE_INT(T_INT_NUM);
}
<edges,faces>{ZERO} {
    PARSE_INT(T_INT_NUM);
}

{WHITESPACE}+ {}

{COMMENT}[^\n]*\n {}

[Pp][Oo][Ii][Nn][Tt][Ss]: {
    BEGIN(points);
    yyextra->lineno = yylineno;
    return T_POINTS;
}
[Pp][Oo][Ii][Nn][Tt][Ss][2][Dd]: {
    BEGIN(points2d);
    yyextra->lineno = yylineno;
    return T_POINTS2D;
}

[Ee][Dd][Gg][Ee][Ss]: {
    BEGIN(edges);
    yyextra->lineno = yylineno;
    return T_EDGES;
}
[Ff][Aa][Cc][Ee][Ss]: {
    BEGIN(faces);
    yyextra->lineno = yylineno;
    return T_FACES;
}

[Pp][Oo][Ll][Yy]: {
    BEGIN(poly);
    yyextra->lineno = yylineno;
    return T_POLY;
}

[Pp][Oo][Ll][Yy][Ll][Ii][Nn][Ee]: {
    BEGIN(polyline);
    yyextra->lineno = yylineno;
    return T_POLYLINE;
}

[Pp][Oo][Ii][Nn][Tt][ ][Cc][Oo][Ll][Oo][Rr]: {
    BEGIN(color);
    yyextra->lineno = yylineno;
    return T_POINT_COLOR;
}
[Ee][Dd][Gg][Ee][ ][Cc][Oo][Ll][Oo][Rr]: {
    BEGIN(color);
    yyextra->lineno = yylineno;
    return T_EDGE_COLOR;
}
[Ff][Aa][Cc][Ee][ ][Cc][Oo][Ll][Oo][Rr]: {
    BEGIN(color);
    yyextra->lineno = yylineno;
    return T_FACE_COLOR;
}

[Pp][Oo][Ll][Yy][Ff][Aa][Cc][Ee]: {
    BEGIN(polyface);
    yyextra->lineno = yylineno;
    return T_POLYFACE;
}

[Nn][Aa][Mm][Ee]:[ \t]* {
    BEGIN(name);
    yyextra->lineno = yylineno;
    yyextra->buffer[0] = 0x0;
}
<name>[^\n]* {
    BEGIN(INITIAL);
    strncpy(yyextra->buffer, yytext, YY_BUFSIZE);
    return T_NAME;
}

{DELIM}+\n {
    BEGIN(INITIAL);
    yyextra->lineno = yylineno;
    return T_DELIM;
}

. {
    yyextra->lineno = yylineno;
    yyextra->c = yytext[0];
    return T_ERROR;
}
%%
