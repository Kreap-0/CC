#pragma once

#include <TokenRule.hpp>

class TokenRuleFactory {
public:
    static std::vector<std::unique_ptr<TokenRule>> createStandardRules() {
        std::vector<std::unique_ptr<TokenRule>> tokenRules;

        tokenRules.push_back(std::make_unique<OperatorRule>());
        tokenRules.push_back(std::make_unique<KeywordRule>());
        tokenRules.push_back(std::make_unique<IdentifierRule>());
        tokenRules.push_back(std::make_unique<NumberRule>());

        return tokenRules;
    }
};