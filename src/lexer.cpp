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
        }
        else if (currentChar == '/' && index + 1 < source.size() && source[index + 1] == '/')
        {
            // Skip single-line comment (//)
            index += 2; // Skip the //
            while (index < source.size() && source[index] != '\n')
            {
                ++index; // Skip until end of line
            }
        }
        else if (currentChar == '(')
        {
            tokens.push_back({ "(", openParen });
            ++index;
        }
        else if (currentChar == ')')
        {
            tokens.push_back({ ")", closeParen });
            ++index;
        }else if (currentChar == '=')
        {
            tokens.push_back({ "=", eq });
            ++index;
        }
        else if (currentChar == ';')
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
            }else if (word == "let")
            {
                tokens.push_back( {.type = TokenType::let} );
            }
            else
            {
                tokens.push_back({ .value = word, .type = TokenType::ident });
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
