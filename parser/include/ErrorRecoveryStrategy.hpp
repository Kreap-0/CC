#include <Token.hpp>

#include <set>

class ErrorRecoveryStrategy {
public:
    virtual void recover(class ParserContext* ctx, TokenType expected) = 0;
    virtual ~ErrorRecoveryStrategy() = default;
};

class SyncTokenStrategy : public ErrorRecoveryStrategy {
    std::set<TokenType> syncTokens;
public:
    SyncTokenStrategy() {
        syncTokens = {SEMICOLON, END, ELSE, TOKEN_EOF};
    }
    
    void recover(ParserContext* ctx, TokenType expected) override {
        while (!syncTokens.count(ctx->currentToken().type) && 
               ctx->currentToken().type != TOKEN_EOF) {
            ctx->consume();
        }
    }
};