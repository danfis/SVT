/**
 * SVT
 * ----------
 * Copyright (c)2009 Daniel Fiser <danfis (at) danfis (dot) cz>
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
//#include "lexer.h"
#include "svt.h"
#include "svt.parser.h"
#include "parse_func.h"


#define PARSE_FLOAT(ret) \
    if (svtParseFloat(yytext, &(yylval->f)) != 0){ \
        return T_ERROR; \
    } \
    return ret

#define PARSE_INT(ret) \
    if (svtParseInt(yytext, &yylval->i) != 0){ \
        return T_ERROR; \
    } \
    return ret

%}

%option noyywrap
%option yylineno
%option nounput
%option noinput
%option extra-type="svt_yylval_t *"
%option reentrant
%option bison-bridge

DIGIT [0-9]
NONZERO [1-9]
ZERO "0"
SIGN [-+]
DOT "."
WHITESPACE [ \t\n]
COMMENT #[^\n]*\n
DELIM ([-=+]+{WHITESPACE}*)+
EXP [eE]
INT {SIGN}?({ZERO})|({NONZERO}{DIGIT}*)
FLOAT {SIGN}?({ZERO}|{NONZERO}{DIGIT}*)({DOT}{DIGIT}*)?({EXP}{SIGN}?{DIGIT}+)?
HEADER_END :{WHITESPACE}*({COMMENT}|\n)
HEADER_POINTS ^(?i:points){HEADER_END}
HEADER_POINTS2D ^(?i:points){HEADER_END}
HEADER_EDGES ^(?i:edges){HEADER_END}
HEADER_FACES ^(?i:faces){HEADER_END}
HEADER_POLY ^(?i:poly){HEADER_END}
HEADER_POLY3D ^(?i:poly3d){HEADER_END}
HEADER_POLYLINE ^(?i:polyline){HEADER_END}
HEADER_POINT_COLOR ^(?i:point[ ]color):{WHITESPACE}*
HEADER_EDGE_COLOR ^(?i:edge[ ]color):{WHITESPACE}*
HEADER_FACE_COLOR ^(?i:face[ ]color):{WHITESPACE}*
HEADER_POLYFACE ^(?i:polyface){HEADER_END}
HEADER_NAME ^(?i:name):[ \t]*
EOL ([ \t]*\n)+

%s points points2d edges faces name poly polyline color polyface
%%
<INITIAL,points,points2d,poly,polyline,color,polyface>{FLOAT} {
    PARSE_FLOAT(T_FLT);
}

<edges,faces>{INT} {
    PARSE_INT(T_INT);
}

{EOL} { return T_EOL; }

{WHITESPACE}+ {}

{COMMENT} {}

{HEADER_POINTS} {
    BEGIN(points);
    printf("Points:\n");
    return T_POINTS;
}

{HEADER_EDGES} {
    BEGIN(edges);
    printf("Edges:\n");
    return T_EDGES;
}
{HEADER_FACES} {
    BEGIN(faces);
    printf("Faces:\n");
    return T_FACES;
}

{HEADER_POLY} {
    BEGIN(poly);
    return T_POLY;
}

{HEADER_POLYLINE} {
    BEGIN(polyline);
    return T_POLYLINE;
}

{HEADER_POINT_COLOR} {
    BEGIN(color);
    return T_POINT_COLOR;
}
{HEADER_EDGE_COLOR} {
    BEGIN(color);
    return T_EDGE_COLOR;
}
{HEADER_FACE_COLOR} {
    BEGIN(color);
    return T_FACE_COLOR;
}

{HEADER_POLYFACE} {
    BEGIN(polyface);
    return T_POLYFACE;
}

{HEADER_NAME} {
    BEGIN(name);
}
<name>{EOL} {
    BEGIN(INITIAL);
    yylval->s = strdup(yytext);
    return T_NAME;
}

{DELIM} {
    BEGIN(INITIAL);
    printf("DELIM\n");
    return T_DELIM;
}

. {
    yylval->c = yytext[0];
    return T_ERROR;
}

%%
