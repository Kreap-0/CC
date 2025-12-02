#include <Lexer.hpp>

#include <cassert>
#include <iostream>

std::vector<Token> Lexer::tokenize(const std::string& input) const {
    std::vector<Token> tokens;

    size_t pos = 0, line = 0;
    while (pos < input.size()) {
        char c = input[pos];

        if (isspace(c)) {
            if (c == '\n') {
                // std::cerr << "push_back" << "\n";
                tokens.push_back({TOKEN_EOLN, "EOLN", line++});
            }
            pos++;
            // std::cerr << pos << "\n";
            continue;
        }
        
        bool matched = false;
        for (auto& rule : rules) {
            if (auto token = rule->match(input, pos)) {
                // std::cerr << "match\n";
                token->line = line;
                tokens.push_back(*token);
                // std::cerr << token->lexeme << "\n" << pos << "\n";
                pos += token->lexeme.length();
                assert(token->lexeme.length() != 0);
                matched = true;
                break;
            }
        }
        
        assert(matched); // TODO
        // if (!matched) {
        //     pos++;
        // }
    }

    tokens.push_back({TOKEN_EOF, "EOF", line});

    return tokens;
}