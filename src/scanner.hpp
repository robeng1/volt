#ifndef scanner_hpp
#define scanner_hpp

#include <string>
#include "token.hpp"

class Scanner
{
    std::string source;
    std::string::size_type start;
    std::string::size_type current;
    int line;

    bool is_at_end();
    char advance();
    char peek();
    char peek_next();
    bool match(char expected);

    Token make_token(TokenType type);
    Token error_token(const std::string &message);

    void skip_whitespace();
    TokenType check_keyword(size_t pos, size_t len, std::string rest, TokenType type);
    TokenType identifier_type();
    Token identifier();
    Token number();
    Token string();

public:
    Scanner(std::string source) : source(source),
                                  start(0),
                                  current(0),
                                  line(1){};

    Token scan_token();
};

#endif /* scanner_hpp */