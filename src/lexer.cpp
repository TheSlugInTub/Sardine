#include <lexer.h>

Lexer::Lexer(std::string& src)
{
    source = src;
}

std::vector<Token> Lexer::Lex()
{
    std::vector<Token> tokens;
    while (index < source.size())
    {
        char currentChar = source[index];

        if (std::isspace(currentChar))
        {
            // Skip whitespace
            ++index;
            continue;
        }

        if (currentChar == ';')
        {
            tokens.push_back({ ";", semi });
            ++index;
        }
        else if (std::isdigit(currentChar))
        {
            std::string number;
            while (index < source.size() && std::isdigit(source[index]))
            {
                number += source[index++];
            }
            tokens.push_back({ number, intLit });
        }
        else if (std::isalpha(currentChar))
        {
            std::string word;
            while (index < source.size() && std::isalpha(source[index]))
            {
                word += source[index++];
            }

            if (word == "exit")
            {
                tokens.push_back({ word, exitToken });
            }
            else
            {
                tokens.push_back({ word, unknown });
            }
        }
        else
        {
            tokens.push_back({ std::string(1, currentChar), unknown });
            ++index;
        }
    }

    return tokens;    
}
