#include "scanner.hpp"

static bool is_digit(char c)
{
    return c >= '0' && c <= '9';
}

static bool is_alpha(char c)
{
    return (c >= 'a' && c <= 'z') ||
           (c >= 'A' && c <= 'Z') ||
           c == '_';
}

Token Scanner::scan_token()
{
    skip_whitespace();

    start = current;

    if (is_at_end())
        return make_token(TokenType::_EOF);

    auto c = advance();

    if (is_digit(c))
        return number();
    if (is_alpha(c))
        return identifier();

    switch (c)
    {
    case '(':
        return make_token(TokenType::LEFT_PAREN);
    case ')':
        return make_token(TokenType::RIGHT_PAREN);
    case '{':
        return make_token(TokenType::LEFT_BRACE);
    case '}':
        return make_token(TokenType::RIGHT_BRACE);
    case ';':
        return make_token(TokenType::SEMICOLON);
    case ',':
        return make_token(TokenType::COMMA);
    case '.':
        return make_token(TokenType::DOT);
    case '-':
        return make_token(TokenType::MINUS);
    case '+':
        return make_token(TokenType::PLUS);
    case '/':
        return make_token(TokenType::SLASH);
    case '*':
        return make_token(TokenType::STAR);
    case '!':
        return make_token(match('=') ? TokenType::BANG_EQUAL : TokenType::BANG);
    case '=':
        return make_token(match('=') ? TokenType::EQUAL_EQUAL : TokenType::EQUAL);
    case '<':
        return make_token(match('=') ? TokenType::LESS_THAN_EQUAL : TokenType::LESS_THAN);
    case '>':
        return make_token(match('=') ? TokenType::GREATER_THAN_EQUAL : TokenType::GREATER_THAN);

    case '"':
        return string();
    }

    return error_token("Unexpected character.");
}

bool Scanner::is_at_end()
{
    return current == source.length();
}

char Scanner::advance()
{
    current++;
    return source[current - 1];
}

char Scanner::peek()
{
    if (is_at_end())
        return '\0';
    return source[current];
}

char Scanner::peek_next()
{
    if ((current + 1) >= source.length())
        return '\0';
    return source[current + 1];
}

bool Scanner::match(char expected)
{
    if (is_at_end())
        return false;
    if (source[current] != expected)
        return false;

    current++;
    return true;
}

Token Scanner::make_token(TokenType type)
{
    auto text = std::string(&source[start], current - start);
    return Token(type, text, line);
}

Token Scanner::error_token(const std::string &message)
{
    return Token(TokenType::ERROR, message, line);
}

void Scanner::skip_whitespace()
{
    while (true)
    {
        auto c = peek();
        switch (c)
        {
        case ' ':
        case '\r':
        case '\t':
            advance();
            break;

        case '\n':
            line++;
            advance();
            break;

        case '/':
            if (peek_next() == '/')
            {
                // A comment goes until the end of the line.
                while (peek() != '\n' && !is_at_end())
                    advance();
            }
            else
            {
                return;
            }
            break;

        default:
            return;
        }
    }
}

TokenType Scanner::check_keyword(size_t pos, size_t len, std::string rest, TokenType type)
{
    if (current - start == pos + len && source.compare(start + pos, len, rest) == 0)
    {
        return type;
    }

    return TokenType::IDENTIFIER;
}

TokenType Scanner::identifier_type()
{
    switch (source[start])
    {
    case 'a':
        return check_keyword(1, 2, "nd", TokenType::AND);
    case 'c':
        return check_keyword(1, 4, "lass", TokenType::CLASS);
    case 'd':
        return check_keyword(1, 2, "ef", TokenType::DEF);
    case 'e':
        return check_keyword(1, 3, "lse", TokenType::ELSE);
    case 'f':
        if (current - start > 1)
        {
            switch (source[start + 1])
            {
            case 'a':
                return check_keyword(2, 3, "lse", TokenType::FALSE);
            case 'o':
                return check_keyword(2, 1, "r", TokenType::FOR);
            case 'u':
                return check_keyword(2, 1, "n", TokenType::FUN);
            }
        }
        break;
    case 'i':
        return check_keyword(1, 1, "f", TokenType::IF);
    case 'n':
        return check_keyword(1, 2, "il", TokenType::NIL);
    case 'o':
        return check_keyword(1, 1, "r", TokenType::OR);
    case 'p':
        return check_keyword(1, 4, "rint", TokenType::PRINT);
    case 'r':
        return check_keyword(1, 5, "eturn", TokenType::RETURN);
    case 's':
        return check_keyword(1, 4, "uper", TokenType::SUPER);
    case 't':
        if (current - start > 1)
        {
            switch (source[start + 1])
            {
            case 'h':
                return check_keyword(2, 2, "is", TokenType::THIS);
            case 'r':
                return check_keyword(2, 2, "ue", TokenType::TRUE);
            }
        }
        break;
    case 'v':
        return check_keyword(1, 2, "ar", TokenType::VAR);
    case 'l':
        return check_keyword(1, 2, "et", TokenType::LET);
    case 'w':
        return check_keyword(1, 4, "hile", TokenType::WHILE);
    }

    return TokenType::IDENTIFIER;
}

Token Scanner::identifier()
{
    while (is_alpha(peek()) || is_digit(peek()))
        advance();

    return make_token(identifier_type());
}

Token Scanner::number()
{
    while (is_digit(peek()))
        advance();

    // Look for a fractional part.
    if (peek() == '.' && is_digit(peek_next()))
    {
        // Consume the "."
        advance();

        while (is_digit(peek()))
            advance();
    }

    return make_token(TokenType::NUMBER);
}

Token Scanner::string()
{
    while (peek() != '"' && !is_at_end())
    {
        if (peek() == '\n')
            line++;
        advance();
    }

    if (is_at_end())
        return error_token("Unterminated string.");

    // The closing ".
    advance();
    return make_token(TokenType::STRING);
}