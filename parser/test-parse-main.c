#include "svt.h"
#include "svt.parser.h"
#include "svt.lex.h"

extern int yyparse (yyscan_t yyscanner);

svt_yylval_t yylval;
yyscan_t scanner;

int main(int argc, char *argv[])
{
    yylex_init(&scanner);
    yyset_in(stdin, scanner);

    yyparse(scanner);

    yylex_destroy(scanner);
    return 0;
}
