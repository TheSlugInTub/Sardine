#include <parser.h>

Parser::Parser(std::vector<Token> Tokens)
    : tokens(std::move(Tokens))
{
}

std::optional<Node::Expr> Parser::parseExpr()
{
    if (peak().has_value() && peak().value().type == TokenType::intLit)
    {
        return Node::Expr
        {
            .intLit = consume()
        };
    }else
    {
        return {};
    }
}

Node::Exit Parser::parse()
{
    Node::Exit exitNode;

    while (peak().has_value())
    {
        if (peak().value().type == TokenType::exitToken)
        {
            consume();

            if (auto nodeExpr = parseExpr())
            {
                exitNode = Node::Exit {.expr = nodeExpr.value()};
            }else
            {
                std::cerr << "Invalid expression\n";
                exit(1);
            }

            if (peak().has_value() && peak().value().type == TokenType::semi)
            {
                consume();
            }else
            {
                std::cerr << "Invalid expression\n";
                exit(1);
            }
        }
    }

    index = 0;
    return exitNode;
}

std::optional<Token> Parser::peak(int ahead) const
{
    if (index + ahead > tokens.size())
    {
        return {};
    }else
    {
        return tokens.at(index);
    }
}

Token Parser::consume()
{
    return tokens.at(index++);
}
