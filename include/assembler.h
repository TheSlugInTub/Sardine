#pragma once

#include <iostream>
#include <vector>
#include <parser.h>

class Assembler
{
public:
    Assembler(Node::Exit Root);

    std::string assemble() const;

private:
    const Node::Exit root;    

};
