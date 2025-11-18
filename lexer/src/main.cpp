#include <iostream>
#include <fstream>

#include <Utils.hpp>
#include <Lexer.hpp>

int main(int argc, char* argv[]) {

    std::ofstream ofserr("lexer.err"), ofsdyd("lexer.dyd");

    if (argc != 2 || !std::string(argv[1]).ends_with(".txt")) {
        ofserr << "Command line argument error" << std::endl;
        return 0;
    }

    auto str = read_file_to_string(argv[1]);
    
    Lexer lexer;
    auto tokens = lexer.tokenize(str);

    for (const Token& token : tokens) {
        ofsdyd << token.lexeme << " " << token.type << std::endl;
    }
}