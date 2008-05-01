#include <iostream>
#include "parser.hpp"
using namespace std;

yylval_t yylval;


#define SKIP_DELIMS \
    for (_cur_token = yylex(); \
         _cur_token != 0 && _cur_token != T_ERROR \
         && _cur_token == T_DELIM; \
         _cur_token = yylex())

Parser *Parser::instance()
{
    static Parser parser;

    return &parser;
}

ObjData *Parser::parse()
{
    bool end = false;

    _cur_obj = new ObjData;
    _parsed = false;

    if (_cur_token == -1 || _cur_token == T_DELIM){
        SKIP_DELIMS;
    }

    while (_cur_token != 0 && !end){
        switch (_cur_token){
            case T_POINTS:
                _parsePoints();
                break;
            case T_EDGES:
                _parseEdges();
                break;
            case T_FACES:
                _parseFaces();
                break;
            case T_ERROR:
                _parseError();
                break;
            case T_DELIM:
                //_parseDelim();
                end = true;
                break;
            default:
                cout << "Token: " << _cur_token << endl;
                _cur_token = yylex();
        }
    }

    if (!_parsed){
        delete _cur_obj;
        return 0;
    }
    return _cur_obj;
}

void Parser::_parsePoints()
{
    float coords[3];
    int i = 0;

    _parsed = true;

    _cur_token = yylex();
    while (_cur_token == T_FLT_NUM){
        coords[i] = yylval.flt_num;
        i = (i + 1) % 3;

        // three coords already read
        if (i == 0){
            _cur_obj->addVertex(coords[0], coords[1], coords[2]);
        }

        _cur_token = yylex();
    }

    if (i != 0){
        cerr << "Some numbers unparsed: ";
        if (i == 1)
            cerr << coords[0] << endl;
        if (i == 2)
            cerr << coords[0] << " " << coords[1] << endl;
    }
}

void Parser::_parseEdges()
{
    int nums[2];
    int i = 0;

    _parsed = true;

    _cur_token = yylex();
    while (_cur_token == T_INT_NUM){
        nums[i] = yylval.int_num;
        i = (i + 1) % 2;

        if (i == 0){
            _cur_obj->addEdge(nums[0], nums[1]);
        }

        _cur_token = yylex();
    }

    if (i != 0){
        cerr << "Some numbers unparsed: " << nums[0] << endl;
    }
}

void Parser::_parseFaces()
{
    int nums[3];
    int i = 0;

    _parsed = true;

    _cur_token = yylex();
    while (_cur_token == T_INT_NUM){
        nums[i] = yylval.int_num;
        i = (i + 1) % 3;

        if (i == 0){
            _cur_obj->addFace(nums[0], nums[1], nums[2]);
        }

        _cur_token = yylex();
    }

    if (i != 0){
        cerr << "Some numbers unparsed: ";
        if (i == 1)
            cerr << nums[0] << endl;
        if (i == 2)
            cerr << nums[0] << " " << nums[1] << endl;
    }
}

void Parser::_parseDelim()
{
    SKIP_DELIMS;
}

void Parser::_parseError()
{
    char buffer[100];
    int i = 1;
    int line = yylval.lineno;

    buffer[0] = yylval.c;
    while ((_cur_token = yylex()) == T_ERROR){
        buffer[i++] = yylval.c;
    }
    buffer[i] = 0;

    cerr << "Unexpected input on line " << line << ": '" << buffer
         << "'" << endl;
}



/*
int main(int argc, char *argv[])
{
    Parser *parser = Parser::instance();
    ObjData *data;

    SoDB::init();

    while ((data = parser->parse()) != 0){
        cout << "data parsed" << endl;
        delete data;
    }

    return 0;
}
*/
