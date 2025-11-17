#include <TokenRule.hpp>

std::optional<Token> IdentifierRule::match(const std::string& input, size_t pos) {
    if (pos >= input.length()) return std::nullopt;

    char nxtc = input[pos];
    if (!isalpha(nxtc)) return std::nullopt;
    for (size_t i = pos; i < input.length(); i++) {
        char c = nxtc;
        nxtc = (i + 1 < input.size()) ? input[i + 1] : ' ';
        
        if (!isalnum(nxtc)) {
            return Token {
                ID,
                input.substr(pos, i - pos + 1)
            };
        }
        
    }

    return std::nullopt;
}