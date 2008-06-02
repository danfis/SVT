#ifndef _PARSER_HPP_
#define _PARSER_HPP_

#include <stdio.h>
#include "parser_lexer_common.h"
#include "objdata.hpp"

extern "C" {
    int yylex(void);
}


class Parser {
  private:
    int _cur_token;
    ObjData *_cur_obj;
    bool _parsed;
    FILE *_input;

    void _parsePoints();
    void _parsePoints2d();
    void _parseEdges();
    void _parseFaces();
    void _parseName();
    void _parseDelim();
    void _parseError();

    Parser() : _cur_token(-1), _cur_obj(0), _input(stdin){}
    ~Parser();
  public:
    static Parser *instance();

    bool setInput(const char *filename = 0);
    ObjData *parse();
};
#endif
