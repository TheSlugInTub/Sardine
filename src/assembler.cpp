#include <assembler.h>
#include <sstream>
#include <fstream>

Assembler::Assembler(Node::Prog Prog)
    : prog(std::move(Prog))
{
}

void Assembler::assembleExpr(const Node::Expr& expr)
{
    struct ExprVisitor
    {
        Assembler* asem;
        

        void operator()(const Node::ExprIntLit& expr_int_lit) const
        {
            asem->output << "    mov rax, " << expr_int_lit.intLit.value << "\n";
            asem->push("rax");
        }

        void operator()(const Node::ExprIdent& expr_ident)
        {
            if (!asem->vars.contains(expr_ident.ident.value))
            {
                std::cerr << "OSC:ERROR: Undeclared identifier/variable: " << expr_ident.ident.value << std::endl;
                exit(1);
            }

            const auto& var = asem->vars.at(expr_ident.ident.value);
            std::stringstream offset;
            offset << "QWORD [rsp + " << (asem->stackSize - var.stackLoc - 1) * 8 << "]\n";
            asem->push(offset.str());
        }
    };
    
    ExprVisitor visitor{.asem = this};
    std::visit(visitor, expr.var);
}

void Assembler::assembleStmt(const Node::Stmt& stmt)
{
    struct StmtVisitor
    {
        Assembler* asem;
        void operator()(const Node::StmtExit& stmt_exit) const
        {
            asem->assembleExpr(stmt_exit.expr);
            asem->output << "    mov rax, 60\n";
            asem->pop("rdi");
            asem->output << "    syscall\n";
        }

        void operator()(const Node::StmtLet& stmt_let)
        {
            if (asem->vars.contains(stmt_let.ident.value))
            {
                std::cerr << "OSC:ERROR: Multiple declarations with the same identifier: " << stmt_let.ident.value << std::endl;
                exit(1);
            }

            asem->vars.insert({stmt_let.ident.value, Var {.stackLoc = asem->stackSize}});
            asem->assembleExpr(stmt_let.expr);
        }
    };

    StmtVisitor visitor { .asem = this } ;
    std::visit(visitor, stmt.var);
}

std::string Assembler::assembleProg()
{
    output << "global _start\n\n_start:\n";

    for (const Node::Stmt& stmt : prog.stmts)
    {
        assembleStmt(stmt);
    }

    output << "    mov rax, 60\n";
    output << "    mov rdi, 0\n";
    output << "    syscall\n";
    return output.str();
}

void Assembler::push(const std::string& reg)
{
    output << "    push " << reg << "\n";
    stackSize++;
}

void Assembler::pop(const std::string& reg)
{
    output << "    pop " << reg << "\n";
    stackSize--;
}
