#include <ParserContext.hpp>

#include <sstream>
#include <iostream>

ParserContext::ParserContext(const std::string& filename) {
    recoveryStrategy = std::make_unique<SyncTokenStrategy>();
    loadTokens(filename);
}

ParserContext::~ParserContext() {
    if (dydFile.is_open()) dydFile.close();
}

void ParserContext::loadTokens(const std::string& filename) {
    dydFile.open(filename);
    if (!dydFile) {
        throw std::runtime_error("Can't open file: " + filename);
    }

    std::string line;
    int lineNum = 1;
    while (getline(dydFile, line)) {
        std::istringstream iss(line);
        std::string lexeme;
        size_t tokenTypeId;
        iss >> lexeme >> tokenTypeId;
        
        TokenType type = static_cast<TokenType>(tokenTypeId);

        if (type == TOKEN_EOLN) {
            lineNum += 1;
        } else {
            tokenBuffer.emplace_back(type, lexeme, lineNum);
        }
    }

    std::cerr << "LoadTokens over." << std::endl;
}

const Token& ParserContext::currentToken() const {
    return (currentPos < tokenBuffer.size()) 
            ? tokenBuffer[currentPos] 
            : tokenBuffer.back();
}

void ParserContext::consume() {
    if (currentPos < tokenBuffer.size() - 1) {
        currentPos++;
    }
}

bool ParserContext::match(TokenType type) {
    if (currentToken().type == type) {
        consume();
        return true;
    }
    return false;
}

void ParserContext::expect(TokenType expected) {
    if (!match(expected)) {
        reportError("Expect '" + TokenLiteral[expected] + 
                    "', But found '" + TokenLiteral[currentToken().type] + "'");
        recoveryStrategy->recover(this, expected);
    }
}

void ParserContext::reportError(const std::string& message) {
    std::cerr << "[Line " + std::to_string(currentToken().line) + 
                        "] Syntax Error: " + message << std::endl;
    errors.push_back("[Line " + std::to_string(currentToken().line) + 
                        "] Syntax Error: " + message);
}

void ParserContext::enterScope(const std::string& owner, bool isFunction) {
    currentLevel++;
    scopeStack.push({owner, isFunction, globalVarIndex});
    
    if (isFunction) {
        FunctionInfo func(owner, "function", currentLevel);
        for (auto* obs : observers) obs->onFunctionDeclared(func);
    }
}

void ParserContext::exitScope() {
    if (scopeStack.empty()) return;
    
    ScopeEntry scope = scopeStack.top();
    scopeStack.pop();
    currentLevel--;
    
    if (scope.isFunction) {
        int endPos = globalVarIndex - 1;
        for (auto* obs : observers) {
            obs->updateFunctionRange(scope.name, scope.varStartPos, endPos);
        }
    }
}

void ParserContext::declareVariable(const std::string& name, const std::string& category) {
    if (scopeStack.empty()) {
        reportError("Variable '" + name + "' defined out of scope");
        return;
    }
    
    ScopeEntry& currentScope = scopeStack.top();
    VariableInfo var{
        name,
        currentScope.name,
        category,
        "integer",
        currentLevel,
        globalVarIndex++
    };
    
    for (auto* obs : observers) obs->onVariableDeclared(var);
}

void ParserContext::addObserver(SymbolObserver* observer) {
    observers.push_back(observer);
}

void ParserContext::recover(TokenType expected) {
    if (recoveryStrategy) {
        recoveryStrategy->recover(this, expected);
    }
}