#pragma once

#include <optional>
#include <string>
#include <vector>

#include <Trie.hpp>
#include <Token.hpp>

class TokenRule {
public:
    virtual ~TokenRule() = default;
    virtual std::optional<Token> match(const std::string& input, size_t pos) = 0;
};

class KeywordRule : public TokenRule {
private:
    std::unique_ptr<TrieNode> root;

    void insertKeyword(const std::string& keyword);
    void buildTrie();
    
public:
    std::optional<Token> match(const std::string& input, const size_t pos) override;

    KeywordRule() : root(std::make_unique<TrieNode>()) {
        buildTrie();
    }
};

class IdentifierRule : public TokenRule {
public:
    std::optional<Token> match(const std::string& input, size_t pos) override;
};

class NumberRule : public TokenRule {
public:
    std::optional<Token> match(const std::string& input, size_t pos) override;
};

class OperatorRule : public TokenRule {
public:
    std::optional<Token> match(const std::string& input, size_t pos) override;
};