%{
#include "parser_lexer_common.h"
%}

%option noyywrap
%option yylineno

DIGIT [0-9]
NONZERO [1-9]
ZERO "0"
MINUS "-"
DOT "."
WHITESPACE [ \t\n]
COMMENT "#"
DELIM [-=+]

%s points points2d edges faces
%%
<points,points2d>{MINUS}?{NONZERO}{DIGIT}*{DOT}?{DIGIT}* {
    yylval.flt_num = atof(yytext);
    yylval.lineno = yylineno;
    return T_FLT_NUM;
}
<points,points2d>{MINUS}?{ZERO}{DOT}? {
    yylval.flt_num = atof(yytext);
    yylval.lineno = yylineno;
    return T_FLT_NUM;
}
<points,points2d>{MINUS}?{ZERO}{DOT}{DIGIT}* {
    yylval.flt_num = atof(yytext);
    yylval.lineno = yylineno;
    return T_FLT_NUM;
}

<edges,faces>{NONZERO}{DIGIT}* {
    yylval.int_num = atoi(yytext);
    yylval.lineno = yylineno;
    return T_INT_NUM;
}
<edges,faces>{ZERO} {
    yylval.int_num = atoi(yytext);
    yylval.lineno = yylineno;
    return T_INT_NUM;
}

{WHITESPACE}+ {}

{COMMENT}[^\n]*\n {}

[Pp][Oo][Ii][Nn][Tt][Ss]: {
    BEGIN(points);
    yylval.lineno = yylineno;
    return T_POINTS;
}
[Pp][Oo][Ii][Nn][Tt][Ss][2][Dd]: {
    BEGIN(points2d);
    yylval.lineno = yylineno;
    return T_POINTS2D;
}

[Ee][Dd][Gg][Ee][Ss]: {
    BEGIN(edges);
    yylval.lineno = yylineno;
    return T_EDGES;
}
[Ff][Aa][Cc][Ee][Ss]: {
    BEGIN(faces);
    yylval.lineno = yylineno;
    return T_FACES;
}

{DELIM}+\n {
    BEGIN(INITIAL);
    yylval.lineno = yylineno;
    return T_DELIM;
           }

. {
    yylval.lineno = yylineno;
    yylval.c = yytext[0];
    return T_ERROR;
}
%%
