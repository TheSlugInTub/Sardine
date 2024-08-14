#pragma once

#include <iostream>
#include <string>
#include <vector>

enum TokenType 
{
    exitToken,
    intLit,
    semi,
    unknown
};

struct Token
{
    std::string value;

    TokenType type;
};

class Lexer
{
public:
    Lexer(std::string& src);
    std::vector<Token> Lex();

private:
    std::string source;
    size_t index = 0;
};
