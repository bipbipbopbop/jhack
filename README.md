# JHack
### JHack: a C++ library to take control of your computer !


Hello, I'm Jhache and this is my hacking library, **JHack**! I've made this (and will continue to improve it) 
in order to practice with C++ & the WinAPI, and also to try game hacking for the first time.

Behind the catchy introduction is a very simple C++17 Library that is a wrapper on the WinAPI.
The goal of this library is to easily access to a process data & modify it.
On top of that, I want to make useful features that will help programming a game hack !


## Features
Here is a list of the current features:
- a `start()` function that print "Hello World"! (**amazing**)
- a `getProcessHandleByName()` function to retrieve a Process Handle.


## Compilation
Just run the CMakeLists.txt file with the command `cmake`. You may want to build the project in a separate directory, for example `build/`. Both `build.sh` and `build.ps1` scripts can do that for you.

In order to test the program, you first need to enable the tests in the cmake configuration (`cmake -DENABLE_TESTS=ON`, done by the build scripts). Then you just need to run `ctest` in your build directory.
