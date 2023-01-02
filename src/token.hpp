#ifndef token_hpp
#define token_hpp

#include <iostream>
#include <string>
#include "token_type.hpp"

class Token
{

public:
    Token(TokenType type, std::string text, int line) : _type(type), _text(text), _line(line){};

    TokenType type() const { return _type; };
    std::string text() const { return _text; };
    int line() const { return _line; };

private:
    TokenType _type;
    // TODO: change to use string_view 
    std::string _text;
    int _line;
};

#endif /* token_hpp */