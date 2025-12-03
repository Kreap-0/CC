#include <iostream>

#include <ParserContext.hpp>
#include <SymbolObserver.hpp>
#include <SyntaxParser.hpp>
#include <ErrorFileGenerator.hpp>

int main(int argc, char* argv[]) {

    if (argc != 2) {
        std::cerr << "Command line argument error";
        return 1;
    }
    
    try {
        ParserContext ctx(argv[1]);
        
        SymbolTableManager symbolManager;
        ctx.addObserver(&symbolManager);

        SyntaxParser parser(&ctx);
        
        std::cerr << "ParserProgram start." << std::endl;

        parser.parseProgram();

        std::cerr << "ParserProgram over." << std::endl;
        
        std::string baseName = "parser";
        
        symbolManager.generateFiles(baseName);
        
        ErrorFileGenerator errGen(ctx.getErrors());
        errGen.generateFile(baseName);
                
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}