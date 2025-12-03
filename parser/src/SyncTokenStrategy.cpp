#include <ErrorRecoveryStrategy.hpp>

void SyncTokenStrategy::recover(ParserContext* ctx, TokenType expected) {
    while (/*!syncTokens.count(ctx->currentToken().type) &&*/ 
            ctx->currentToken().type != TOKEN_EOF &&
            ctx->currentToken().type != expected) {
        ctx->consume();
    }
    ctx->consume();
}