# Textships-2

A simple game based on the pen and paper game "Battleships"

The program uses [BearLibTerminal](http://foo.wyrd.name/en:bearlibterminal) as it's engine, available under the [MIT License](https://opensource.org/license/MIT)

# Using the source code

### For C++ in Visual Studio Code

The only thing required to use the source code is to have VSC configured for compiling C++ programs with GCC. Then, in the compiler arguments, one must add 2 lines, ```"-L${workspaceFolder}\\lib",``` and ```"-lBearLibTerminal",```, in that order, but not neccesarily one immediately after another
