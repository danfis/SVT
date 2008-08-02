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
