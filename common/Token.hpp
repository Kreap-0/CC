#pragma once

#include <string>
#include <unordered_map>

enum TokenType {
    NONE,
    BEGIN,
    END,
    INTEGER,
    IF,
    THEN,
    ELSE,
    FUNCTION,
    READ,
    WRITE,
    ID,
    CONSTANT,
    EQ,
    NEQ,
    LEQ,
    LE,
    GEQ,
    GE,
    MINUS,
    MUL,
    ASSIGN,
    LB,
    RB,
    SEMICOLON,
    TOKEN_EOLN,
    TOKEN_EOF
};

static constexpr std::string keywordLiteral[] = {
    "",
    "begin", "end", "integer",
    "if", "then", "else",
    "function", "read", "write",
    "", "", "=",
    "<>", "<=", "<",
    ">=", ">", "-",
    "*", ":=", "(",
    ")", ";"
};

static const std::unordered_map<std::string, TokenType> stringToTokenMap = {
    {"begin", BEGIN},
    {"end", END},
    {"integer", INTEGER},
    {"if", IF},
    {"then", THEN},
    {"else", ELSE},
    {"function", FUNCTION},
    {"read", READ},
    {"write", WRITE},
    {"=", EQ},
    {"<>", NEQ},
    {"<=", LEQ},
    {"<", LE},
    {">=", GEQ},
    {">", GE},
    {"-", MINUS},
    {"*", MUL},
    {":=", ASSIGN},
    {"(", LB},
    {")", RB},
    {";", SEMICOLON}
};

static inline TokenType getTokenType(const std::string& str) {
    auto it = stringToTokenMap.find(str);
    if (it != stringToTokenMap.end()) {
        return it->second;
    }
    return NONE;
}

class Token {
public:
    TokenType type;
    const std::string lexeme;

    Token() = default;
    Token(const TokenType type, const std::string& lexeme) : type(type), lexeme(lexeme) {}
};