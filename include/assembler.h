#pragma once

#include <iostream>
#include <vector>
#include <parser.h>
#include <sstream>
#include <fstream>
#include <unordered_map>

class Assembler
{
public:
    Assembler(Node::Prog Prog);

    void assembleExpr(const Node::Expr& expr);

    void assembleStmt(const Node::Stmt& stmt);
    
    std::string assembleProg();

private:
    void push(const std::string& reg);
    void pop(const std::string& reg);

    struct Var
    {
        size_t stackLoc;
    };

    const Node::Prog prog;    
    std::stringstream output;
    size_t stackSize = 0;
    std::unordered_map<std::string, Var> vars {};
};
