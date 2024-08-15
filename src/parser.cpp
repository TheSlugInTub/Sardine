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
            .var = Node::ExprIntLit {.intLit = consume()}
        };
    }else if (peak().has_value() && peak().value().type == TokenType::ident)
    {
        return Node::Expr {.var = Node::ExprIdent {.ident = consume() } };
    }else
    {
        return {};
    }
}

std::optional<Node::Stmt> Parser::parseStmt()
{
    if (peak().value().type == TokenType::exitToken && peak(1).has_value() && peak(1).value().type == TokenType::openParen)
        {
            consume();  // Consume the exit token
            consume();  // Consume the openParen token
            Node::StmtExit stmtExit;

            if (auto nodeExpr = parseExpr())
            {
                stmtExit = {.expr = nodeExpr.value()};
            }
            else
            {
                std::cerr << "Invalid expression\n";
                exit(1);
            }

            if (peak().has_value() && peak().value().type == TokenType::closeParen)
            {
                consume();  // Consume the closeParen token
            }
            else
            {
                std::cerr << "Expected `)`\n";
                exit(1);
            }

            if (peak().has_value() && peak().value().type == TokenType::semi)
            {
                consume();  // Consume the semi token
            }
            else
            {
                std::cerr << "Expected `;`\n";
                exit(1);
            }

            return Node::Stmt{.var = stmtExit};
        }else if (peak().has_value() && peak().value().type == TokenType::let
                && peak(1).has_value() && peak(1).value().type == TokenType::ident 
                && peak(2).has_value() && peak(2).value().type == TokenType::eq )
        {
            consume();
            auto stmt_let = Node::StmtLet { .ident = consume() };
            consume();
            if (auto expre = parseExpr())
            {
                stmt_let.expr = expre.value();
            }else
            {
                std::cerr << "Invalid expresion." << std::endl;
                exit(1);
            }

            if (peak().has_value() && peak().value().type == TokenType::semi)
            {
                consume();
            }else
            {
                std::cerr << "Expected `;`\n";
                exit(1);
            }

            return Node::Stmt {.var = stmt_let};
        }else
        {
            std::cerr << "Unexpected token: " << peak().value().value << std::endl;
            exit(1); 
        } 
}

std::optional<Node::Prog> Parser::parseProg()
{
    Node::Prog prog;

    while (peak().has_value())
    {
        if (auto stmt = parseStmt())
        {
            prog.stmts.push_back(stmt.value());
        }else
        {
            std::cerr << "Invalid statement." << std::endl;
            exit(1);
        }
    }

    return prog;
}

std::optional<Token> Parser::peak(int ahead) const
{
    if (index + ahead >= tokens.size())  // Note the >= instead of >
    {
        return {};
    }
    return tokens.at(index + ahead);  // Use index + ahead to get the correct token
}

Token Parser::consume()
{
    if (index < tokens.size())
    {
        return tokens.at(index++);  // Return the current token and increment index
    }
    throw std::out_of_range("No more tokens to consume");
}
