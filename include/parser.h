#pragma once

#include <iostream>
#include <lexer.h>
#include <optional>
#include <vector>
#include <variant>

namespace Node
{
    struct ExprIntLit
    {
        Token intLit;
    };

    struct ExprIdent
    {
        Token ident;
    };

    struct Expr
    {
        std::variant<ExprIntLit, ExprIdent> var;
    };

    struct StmtExit
    {
        Expr expr;
    };

    struct StmtLet
    {
        Token ident;
        Expr expr;
    };

    struct Stmt
    {
        std::variant<StmtExit, StmtLet> var;
    };

    struct Prog
    {
        std::vector<Stmt> stmts;  
    };
}

class Parser
{
public:
    Parser(std::vector<Token> Tokens);

    std::optional<Node::Expr> parseExpr();
    std::optional<Node::Stmt> parseStmt();
    std::optional<Node::Prog> parseProg();

private:
    std::vector<Token> tokens;
    size_t index = 0;

    std::optional<Token> peak(int ahead = 0) const;
    Token consume();
};
