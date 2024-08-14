#pragma once

#include <iostream>
#include <lexer.h>
#include <optional>
#include <vector>

namespace Node
{
    struct Expr
    {
        Token intLit;
    };

    struct Exit
    {
        Expr expr;       
    };
}

class Parser
{
public:
    Parser(std::vector<Token> Tokens);

    std::optional<Node::Expr> parseExpr();
    Node::Exit parse();

private:
    std::vector<Token> tokens;
    size_t index = 0;

    std::optional<Token> peak(int ahead = 1) const;
    Token consume();
};
