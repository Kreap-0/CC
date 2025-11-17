#include <TokenRule.hpp>

std::optional<Token> NumberRule::match(const std::string& input, size_t pos) {
    if (pos >= input.length()) return std::nullopt;

    char nxtc = input[pos];
    for (size_t i = pos; i < input.length(); i++) {
        char c = nxtc;
        nxtc = (i + 1 < input.size()) ? input[i + 1] : ' ';
        
        if (!isdigit(c)) break;

        if (!isalnum(nxtc)) {
            return Token {
                CONSTANT,
                input.substr(pos, i - pos + 1)
            };
        }
        
    }
    
    return std::nullopt;
}