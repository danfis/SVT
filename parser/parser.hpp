#ifndef _PARSER_HPP_
#define _PARSER_HPP_

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

    void _parsePoints();
    void _parseEdges();
    void _parseFaces();
    void _parseDelim();
    void _parseError();

    Parser() : _cur_token(-1), _cur_obj(0){}
  public:
    static Parser *instance();

    ObjData *parse();
};
#endif
