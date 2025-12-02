#pragma once

#include <fstream>
#include <vector>
#include <stack>
#include <string>
#include <memory>

#include <Token.hpp>
#include <ErrorRecoveryStrategy.hpp>
#include <SymbolObserver.hpp>
#include <Info.hpp>

class ErrorRecoveryStrategy;

class ParserContext {
    std::fstream dydFile;
    std::vector<Token> tokenBuffer;
    size_t currentPos = 0;
    int globalVarIndex = 0;
    
    struct ScopeEntry {
        std::string name;
        bool isFunction;
        int varStartPos;
    };
    
    std::stack<ScopeEntry> scopeStack;
    int currentLevel = 0;
    
    std::vector<std::string> errors;
    std::unique_ptr<ErrorRecoveryStrategy> recoveryStrategy;
    
    std::vector<SymbolObserver*> observers;
    
public:
    explicit ParserContext(const std::string& filename);
    ~ParserContext();
    
    void loadTokens(const std::string& filename);
    const Token& currentToken() const;
    void consume();
    bool match(TokenType type);
    void expect(TokenType expected);
    void reportError(const std::string& message);
    void enterScope(const std::string& owner, bool isFunction);
    void exitScope();
    void declareVariable(const std::string& name, const std::string& category);
    void addObserver(SymbolObserver* observer);
    void recover(TokenType expected);
    
    std::vector<std::string> getErrors() const { return errors; }
    int getGlobalVarIndex() const { return globalVarIndex; }
};