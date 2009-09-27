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
%option nounput
%option noinput
%option extra-type="svt_yylval_t *"

DIGIT [0-9]
NONZERO [1-9]
ZERO "0"
SIGN [-+]
DOT "."
WHITESPACE [ \t\n]
COMMENT "#"
EXP [eE]
EOL ([ \t]*\n)+
INT {SIGN}?({ZERO})|({NONZERO}{DIGIT}*)
FLOAT {SIGN}?({ZERO}|{NONZERO}{DIGIT}*)({DOT}{DIGIT}*)?({EXP}{SIGN}?{DIGIT}+)?
HEADER_POINTS ^((?i:points:)|(?i:points2d:)){WHITESPACE}*
HEADER_EDGES ^(?i:edges:){WHITESPACE}*
HEADER_FACES ^(?i:faces:){WHITESPACE}*
HEADER_POLY ^((?i:poly:)|(?i:poly3d:)){WHITESPACE}*
HEADER_POLYLINE ^(?i:polyline:){WHITESPACE}*
HEADER_POINT_COLOR ^(?i:point[ ]color):{WHITESPACE}*
HEADER_EDGE_COLOR ^(?i:edge[ ]color):{WHITESPACE}*
HEADER_FACE_COLOR ^(?i:face[ ]color):{WHITESPACE}*
HEADER_POLYFACE ^(?i:polyface:){WHITESPACE}*
HEADER_NAME ^(?i:name:)[ \t]*
DELIM ([-=+]+{WHITESPACE}*)+

%s flts ints name
%%
<INITIAL,flts>{FLOAT} {
    PARSE_FLOAT(T_FLT_NUM);
}

<ints>{INT} {
    PARSE_INT(T_INT_NUM);
}

<flts>{EOL} { return T_EOL; }

{WHITESPACE}+ {}

{COMMENT}[^\n]*\n {}

{HEADER_POINTS} {
    BEGIN(flts);
    yyextra->lineno = yylineno;
    return T_POINTS;
}

{HEADER_EDGES} {
    BEGIN(ints);
    yyextra->lineno = yylineno;
    return T_EDGES;
}

{HEADER_FACES} {
    BEGIN(ints);
    yyextra->lineno = yylineno;
    return T_FACES;
}

{HEADER_POLY} {
    BEGIN(flts);
    yyextra->lineno = yylineno;
    return T_POLY;
}

{HEADER_POLYLINE} {
    BEGIN(flts);
    yyextra->lineno = yylineno;
    return T_POLYLINE;
}

{HEADER_POINT_COLOR} {
    BEGIN(flts);
    yyextra->lineno = yylineno;
    return T_POINT_COLOR;
}

{HEADER_EDGE_COLOR} {
    BEGIN(flts);
    yyextra->lineno = yylineno;
    return T_EDGE_COLOR;
}

{HEADER_FACE_COLOR} {
    BEGIN(flts);
    yyextra->lineno = yylineno;
    return T_FACE_COLOR;
}

{HEADER_POLYFACE} {
    BEGIN(flts);
    yyextra->lineno = yylineno;
    return T_POLYFACE;
}

{HEADER_NAME} {
    BEGIN(name);
    yyextra->lineno = yylineno;
    yyextra->buffer[0] = 0x0;
}
<name>[^\n]* {
    BEGIN(INITIAL);
    strncpy(yyextra->buffer, yytext, YY_BUFSIZE);
    return T_NAME;
}

{DELIM} {
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
