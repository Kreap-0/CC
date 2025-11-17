#pragma once

#include <vector>
#include <memory>

#include <TokenRule.hpp>
#include <TokenRuleFactory.hpp>

class Lexer {
private:
    std::vector<std::unique_ptr<TokenRule>> rules;

public:
    Lexer() {
        rules = TokenRuleFactory::createStandardRules();
    }

    std::vector<Token> tokenize(const std::string& input) const;
};