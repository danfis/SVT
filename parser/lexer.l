%{
#include "lexer.h"
#include "parse_func.h"

#define PARSE_FLOAT(ret) \
    if (parseFloat(yytext, &yyextra->flt_num) != 0){ \
        return T_ERROR; \
    } \
    yyextra->lineno = yylineno; \
    return ret

#define PARSE_INT(ret) \
    if (parseInt(yytext, &yyextra->int_num) != 0){ \
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

%s points points2d edges faces name
%%
<points,points2d>{SIGN}?{ZERO}({DOT}{DIGIT}*)?({EXP}{SIGN}?{DIGIT}+)?  { /* -0.1234e-23 */
    PARSE_FLOAT(T_FLT_NUM);
}

<points,points2d>{SIGN}?{NONZERO}{DIGIT}*({DOT}{DIGIT}*)?({EXP}{SIGN}?{DIGIT}+)?  { /* -1043.1234e-23 */
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

[Nn][Aa][Mm][Ee]:[ \t]* {
    BEGIN(name);
    yyextra->lineno = yylineno;
    yyextra->buffer[0] = 0x0;
}
<name>[^\n]* {
    BEGIN(INITIAL);
    strncpy(yyextra->buffer, yytext, BUFSIZE);
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
