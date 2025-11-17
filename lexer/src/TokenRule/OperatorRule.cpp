#include <TokenRule.hpp>

std::optional<Token> OperatorRule::match(const std::string& input, size_t pos) {
    if (pos >= input.length()) return std::nullopt;

    char c1 = input[pos];
    char c2 = (pos + 1 < input.size()) ? input[pos + 1] : ' ';
    
    if (c1 == '<') {
        if (c2 == '=') {
            return Token { LEQ, "<=" };
        } else if (c2 == '>') {
            return Token { NEQ, "<>" };
        } else {
            return Token { LE, "<" };
        }
    } else if (c1 == '=') {
        return Token { EQ, "=" };
    } else if (c1 == '>') {
        if (c2 == '=') {
            return Token { GEQ, ">=" };
        } else {
            return Token { GE, ">" };
        }
    } else if (c1 == '-') {
        return Token { MINUS, "-" };
    } else if (c1 == '*') {
        return Token { MUL, "*" };
    } else if (c1 == '(') {
        return Token { LB, "(" };
    } else if (c1 == ')') {
        return Token { RB, ")" };
    } else if (c1 == ';') {
        return Token { SEMICOLON, ";" };
    } else if (c1 == ':' && c2 == '=') {
        return Token { ASSIGN, ":=" };
    }
    
    return std::nullopt;
}