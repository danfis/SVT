#include "parser.h"
#include "utils.h"

svt_parser_t *svtParserNew()
{
    svt_parser_t *parser = ALLOC(svt_parser_t);

    parser->input = stdin;
    parser->objs = NULL;
    parser->objs_len = 0;

    return parser;
}

void svtParserDelete(svt_parser_t *parser)
{
    while (parser->objs != NULL)
        parser->objs = svtObjDelete(parser->objs);
    free(parser);
}

void svtParserSetInput(svt_parser_t *parser, FILE *input)
{
    parser->input = input;
}

svt_obj_t *svtParserObjs(svt_parser_t *parser, int *len)
{
    if (len != NULL)
        *len = parser->objs_len;
    return parser->objs;
}

svt_obj_t *svtParserObjsSteal(svt_parser_t *parser, int *len)
{
    svt_obj_t *objs;

    if (len != NULL)
        *len = parser->objs_len;
    objs = parser->objs;

    parser->objs = NULL;
    parser->objs_len = 0;

    return objs;
}

int svtParserParse(svt_parser_t *parser)
{
    if (yylex_init_extra(&parser->yylval, &parser->scanner) != 0){
        perror("Can't initialize scanner");
        return -1;
    }

    yylex_destroy(&parser->scanner);

    return 0;
}
