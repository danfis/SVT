%{
#include "parser_lexer_common.h"
%}

%option yylineno

DIGIT [0-9]
NONZERO [1-9]
ZERO "0"
MINUS "-"
DOT "."
WHITESPACE [ \t\n]
COMMENT "#"
DELIM [-=+]

%s points edges faces
%%
<points>{MINUS}?{NONZERO}{DIGIT}*{DOT}?{DIGIT}* {
    yylval.flt_num = atof(yytext);
    yylval.lineno = yylineno;
    return T_FLT_NUM;
}
<points>{MINUS}?{ZERO}{DOT}? {
    yylval.flt_num = atof(yytext);
    yylval.lineno = yylineno;
    return T_FLT_NUM;
}
<points>{MINUS}?{ZERO}{DOT}{DIGIT}* {
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
