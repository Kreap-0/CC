#pragma once

#include <Token.hpp>
#include <ParserContext.hpp>

class SyntaxParser {
    ParserContext* ctx;
    
public:
    explicit SyntaxParser(ParserContext* context) : ctx(context) {}
    
    void parseProgram() {
        parseSubprogram();
        ctx->expect(TOKEN_EOF);
    }
    
    void parseSubprogram() {
        ctx->expect(BEGIN);
        ctx->enterScope("global", false);
        parseDeclarationList();
        // ctx->expect(SEMICOLON);
        parseStatementList();
        ctx->expect(END);
        ctx->exitScope();
    }
    
    void parseDeclarationList() {
        parseDeclaration();
        while (ctx->match(SEMICOLON)) {
            if (ctx->currentToken().type == INTEGER)
                parseDeclaration();
            else {
                break;
            }
        }
    }
    
    void parseDeclaration() {
        if (ctx->match(INTEGER)) {
            if (ctx->match(FUNCTION)) {
                parseFunctionDecl();
            } else {
                parseVariableDecl();
            }
        } else {
            ctx->reportError("Expect Variable or Function Declaration.");
            ctx->recover(INTEGER);
        }
    }
    
    void parseVariableDecl() {
        if (ctx->currentToken().type == ID) {
            std::string varName = ctx->currentToken().lexeme;
            ctx->consume();
            ctx->declareVariable(varName, "variable");
        } else {
            ctx->reportError("Expect variable identity.");
            ctx->recover(ID);
        }
    }
    
    void parseFunctionDecl() {        
        if (ctx->currentToken().type != ID) {
            ctx->reportError("Expect function name");
            ctx->recover(ID);
            return;
        }
        
        std::string funcName = ctx->currentToken().lexeme;
        ctx->consume();
        ctx->enterScope(funcName, true);
        
        ctx->expect(LB);
        parseParameter();
        ctx->expect(RB);
        ctx->expect(SEMICOLON);
        
        parseFunctionBody();
        
        ctx->exitScope();
    }
    
    void parseParameter() {
        if (ctx->currentToken().type == ID) {
            std::string paramName = ctx->currentToken().lexeme;
            ctx->consume();
            ctx->declareVariable(paramName, "parameter");
        } else {
            ctx->reportError("Expect function parameter");
            ctx->recover(ID);
        }
    }
    
    void parseFunctionBody() {
        ctx->expect(BEGIN);
        parseDeclarationList();
        // ctx->expect(SEMICOLON);
        parseStatementList();
        ctx->expect(END);
    }
    
    void parseStatementList() {
        parseStatement();
        while (ctx->match(SEMICOLON)) {
            parseStatement();
        }
    }
    
    void parseStatement() {
        switch (ctx->currentToken().type) {
            case READ: parseReadStmt(); break;
            case WRITE: parseWriteStmt(); break;
            case ID: parseAssignStmt(); break;
            case IF: parseIfStmt(); break;
            default:
                ctx->reportError("Expect statement.");
                ctx->recover(ID);
        }
    }
    
    void parseReadStmt() {
        ctx->expect(READ);
        ctx->expect(LB);
        if (ctx->currentToken().type == ID) {
            ctx->consume();
        } else {
            ctx->reportError("Expect parameter.");
        }
        ctx->expect(RB);
    }
    
    void parseWriteStmt() {
        ctx->expect(WRITE);
        ctx->expect(LB);
        if (ctx->currentToken().type == ID) {
            ctx->consume();
        } else {
            ctx->reportError("Expect parameter.");
        }
        ctx->expect(RB);
    }
    
    void parseAssignStmt() {
        if (ctx->currentToken().type == ID) {
            ctx->consume();
        } else {
            ctx->reportError("Expect lvalue.");
        }
        ctx->expect(ASSIGN);
        parseArithmeticExpr();
    }
    
    void parseIfStmt() {
        ctx->expect(IF);
        parseConditionExpr();
        ctx->expect(THEN);
        parseStatement();
        ctx->expect(ELSE);
        parseStatement();
    }
    
    void parseConditionExpr() {
        parseArithmeticExpr();
        parseRelationalOp();
        parseArithmeticExpr();
    }
    
    void parseRelationalOp() {
        TokenType ops[] = {EQ, NEQ, LE, LEQ, GE, GEQ};
        bool matched = false;
        for (auto op : ops) {
            if (ctx->match(op)) {
                matched = true;
                break;
            }
        }
        if (!matched) {
            ctx->reportError("Expect relation operator.");
            ctx->recover(ID);
        }
    }
    
    void parseArithmeticExpr() {
        parseTerm();
        while (ctx->match(MINUS)) {
            parseTerm();
        }
    }
    
    void parseTerm() {
        parseFactor();
        while (ctx->match(MUL)) {
            parseFactor();
        }
    }
    
    void parseFactor() {
        switch (ctx->currentToken().type) {
            case ID: 
                ctx->consume(); 
                if (ctx->match(LB)) {
                    parseArithmeticExpr();
                    ctx->expect(RB);
                }
                break;
            case CONSTANT: 
                ctx->consume(); 
                break;
            default:
                ctx->reportError("Expect factor.");
                ctx->recover(ID);
        }
    }
};