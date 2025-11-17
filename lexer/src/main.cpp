#include <iostream>

#include <Utils.hpp>
#include <Lexer.hpp>

int main() {
    auto str = read_file_to_string("tmp.txt");
    
    Lexer lexer;
    auto tokens = lexer.tokenize(str);

    for (const Token& token : tokens) {
        std::cout << token.lexeme << " " << token.type << std::endl;
    }
}