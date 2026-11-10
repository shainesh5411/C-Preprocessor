# C Preprocessor Implementation in C

## Project Overview

This project implements a basic C Preprocessor using the C programming language. It demonstrates how some of the fundamental preprocessing operations are performed before the actual compilation of a C program.

The preprocessor accepts a C source file as input, processes its contents, and generates a corresponding `.i` file containing the preprocessed output.

The project is developed using a modular programming approach, with separate modules for comment removal, header file inclusion, and macro processing.

## Key Features

- **Comment Removal:** Removes single-line (`//`) and multi-line (`/* ... */`) comments while preserving line breaks.
- **Header File Inclusion:** Processes `#include` directives and inserts the contents of the specified header files.
- **Object-Like Macro Expansion:** Identifies and replaces macros defined using `#define`.
- **Function-Like Macro Expansion:** Supports macros with parameters and substitutes actual arguments into their replacement expressions.
- **Modular Design:** Divides the implementation into independent source files and header files for better code organization.
- **Automated Compilation:** Uses a Makefile to automate compilation and linking.

## Processing Workflow

The project follows three major processing stages:

1. Comment Removal
2. Header File Inclusion
3. Macro Expansion

After completing these stages, the final preprocessed output is written to a `.i` file.

## Technologies Used

- Programming Language: C
- Compiler: GCC
- Operating System: Ubuntu/Linux
- Build Automation: Makefile
- Version Control: Git and GitHub

## Project Objective

The primary objective of this project is to understand the working principles of C preprocessing, file handling, string manipulation, macro substitution, modular programming, and the compilation process.
