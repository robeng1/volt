#ifndef token_type_hpp
#define token_type_hpp

enum class TokenType : std::uint8_t
{
    LEFT_PAREN,
    RIGHT_PAREN,
    LEFT_BRACE,
    RIGHT_BRACE,
    COMMA,
    DOT,
    MINUS,
    PLUS,
    SEMICOLON,
    SLASH,
    STAR,
    PERCENTAGE,
    EXPONENT,

    // Bitwise operators
    BITWISE_AND,
    BITWISE_LEFT_SHIT,
    BITWISE_NOT,
    BITWISE_OR,
    BITWISE_RIGHT_SHIFT,
    BITWISE_XOR,

    // Logical operators
    LOGICAL_AND,
    LOGICAL_NOT,
    LOGICAL_OR,

    // Assignment operators
    ASSIGN,
    ASSIGN_PLUS,
    ASSIGN_SLASH,
    ASSIGN_EXPONENT,
    ASSIGN_DOUBLE_SLASH,
    ASSIGN_PERCENTAGE,
    ASSIGN_STAR,
    ASSIGN_MINUS,

    // Bitwise assignment operators
    ASSIGN_BITWISE_AND,
    ASSIGN_BITWISE_LEFT_SHIT,
    ASSIGN_BITWISE_OR,
    ASSIGN_BITWISE_RIGHT_SHIFT,
    ASSIGN_BITWISE_XOR,

    // Comparison operators
    EQUAL,
    EQUAL_EQUAL,
    GREATER_THAN,
    GREATER_THAN_EQUAL,
    LESS_THAN,
    LESS_THAN_EQUAL,
    NOT_EQUAL,
    BANG_EQUAL,
    BANG,

    // Keywords
    AND,
    AS,
    ASSERT,
    BREAK,
    CLASS,
    CONTINUE,
    CONTRACT,
    DEF,
    DEL,
    ELIF,
    ELSE,
    EXCEPT,
    FALSE,
    FINALLY,
    FOR,
    FROM,
    FUN,
    GLOBAL,
    IDENTIFIER,
    IF,
    IMPORT,
    IN,
    IS,
    LAMBDA,
    LET,
    NIL,
    NONE,
    NOT,
    NUMBER,
    OR,
    PASS,
    PRINT,
    RAISE,
    RETURN,
    STRING,
    TRUE,
    TRY,
    VAR,
    WHILE,
    WITH,
    YIELD,
    SUPER,
    THIS,

    ERROR,

    _EOF
};

#endif /* token_type_hpp */