# nemergent

Makefile Commands Reference

This project uses a Makefile for building and managing the C program. Below are the available commands:

## Build Commands

    make or make all: Compiles the source code and generates the main program executable named insert_nbrs

    make test: Compiles the unit test source files and executes a basic unit testing suite.


## Cleanup Commands

    make clean: Removes the main program executable (insert_nbrs) and the object files directory (objs/).

    make clean_test: Removes the unit test executables and their associated object files.

    make clean_all: Executes both clean and clean_test commands, cleaning all generated files from the project.

    make re: Performs a complete rebuild by first running make clean and then make all.