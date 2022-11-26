#!/bin/bash
#clang++ main.cpp lexer.cpp token.cpp -o compiler -std=c++17
clang++ main.cpp lexer.cpp parser.cpp token.cpp -o main -std=c++17
