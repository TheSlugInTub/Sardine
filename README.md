# Sardine 
Sardine is a programming language and this is a compiler for Sardine, it is called OSC, or the Openwell Sardine Compiler.

Sardine is part of the Openwell project which you can find information about here: https://openwell.uk.to

This compiler is written in C++ and the project uses Cmake as its build system.
It currently only supports the return keyword, integer literals, integer variables with the "let" keyword,  and semicolons. But the Sardine programming language will be expanded in the future.

The syntax of the language will look like this:
```
int i;
i = 5;

string name = "John";

void main()
{
    int b = 2;
    i + b;
}
```
It is somewhat similar to C, but it will be simpler and easier to work with.

## Getting started

Just simply clone the git repostory using: `git clone https://github.com/TheSlugInTub/Sardine.git`
And when you have cloned it, add any changes and then type: `cmake --build bld/`, to build the project.

## Use

To compile a file using the Openwell Sardine Compiler, type this command: `osc [filename]`
The language uses .sd as its file extension for files.
