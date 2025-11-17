#include <TokenRule.hpp>

void KeywordRule::insertKeyword(const std::string& keyword) {
    auto* current = root.get();
    
    for (char c : keyword) {
        if (current->children.find(c) == current->children.end()) {
            current->children[c] = std::make_unique<TrieNode>();
        }
        current = current->children[c].get();
    }
    
    current->isEndOfWord = true;
    current->word = keyword;
}

void KeywordRule::buildTrie() {
    std::vector<std::string> keywords = {
        "begin", "end", "integer",
        "if", "then", "else",
        "function", "read", "write"
    };
    
    for (const auto& kw : keywords) {
        insertKeyword(kw);
    }
}
    
std::optional<Token> KeywordRule::match(const std::string& input, const size_t pos) {
    if (pos >= input.length()) return std::nullopt;

    auto* cur = root.get();
    char nxtc = input[pos];
    for (size_t i = pos; i < input.length(); i++) {
        char c = nxtc;
        nxtc = (i + 1 < input.size()) ? input[i + 1] : ' ';
        
        auto it = cur->children.find(c);
        if (it == cur->children.end()) {
            break;
        } else {
            cur = cur->children[c].get();
        }

        if (isalnum(nxtc)) {
            if (!isalpha(nxtc)) {
                break;
            } else {
                continue;
            }
        } else if (cur->isEndOfWord) {
            auto match = input.substr(pos, i - pos + 1);
            return Token {
                getTokenType(match),
                match
            };
        } else {
            break;
        }
    }

    return std::nullopt;
}