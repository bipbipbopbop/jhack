# JHack
### JHack: a C++ library to take control of your computer !


Hello, I'm Jhache and this is my hacking library, **JHack**! I've made this (and will continue to improve it) 
in order to practice with C++ & the WinAPI, and also to try game hacking for the first time.

Behind the catchy introduction is a very simple C++14 Library that is a wrapper on the WinAPI.
The goal of this library is to easily access to a process data & modify it.
On top of that, I want to make useful features that will help programming a game hack !


## Features
Here is a list of the current features:
- a start() function that print "Hello World"! (**amazing**)


## Compilation
I use Cygwin64 toolchain in order to compile the library, as defined in the Makefile (using `g++` and `make`).

In order to compile the Library, just run the command `make`.

For testing the program with the test source file, run the command `make test` to compile the program,
then run the resulting program `a.exe`.
