#include <assembler.h>
#include <sstream>
#include <fstream>

Assembler::Assembler(Node::Exit Root)
    : root(std::move(Root))
{
}

std::string Assembler::assemble() const
{
    std::stringstream output;
    output << "global _start\n\n_start:\n";

    output << "    mov rax, 60\n";
    output << "    mov rdi, " << std::stoi(root.expr.intLit.value) << "\n";
    output << "    syscall";
    return output.str();
}
