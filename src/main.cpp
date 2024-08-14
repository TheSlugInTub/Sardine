#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <lexer.h>
#include <vector>
#include <parser.h>
#include <assembler.h>

int main(int argc, char const *argv[])
{
	if (argc < 2) 
    {
        std::cout << "SARDINE: No files provided.\n";
        return 1; 
    }

    std::string filePath = argv[1];
    std::ifstream file(filePath);

    // Check if the file was opened successfully
    if (!file.is_open()) {
        std::cerr << "ERROR: Could not open file " << filePath << std::endl;
        return 1;
    }

    // Read the file contents into a string
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string fileContents = buffer.str();

    // Close the file
    file.close();

    Lexer lexer(fileContents);

    // Print the file contents
    std::vector<Token> tokens = lexer.Lex();

    for (auto& token : tokens)
    {
        std::cout << token.value << std::endl;
    }

    Parser parser(std::move(tokens));
    std::optional<Node::Exit> tree = parser.parse();

    Assembler assem(tree.value());

    std::fstream outfile("out.asm", std::ios::out);
    outfile << assem.assemble();
    outfile.close();

    system("nasm -felf64 out.asm");    
    system("ld -o out out.o");

    return 0;
}

