#pragma once

#include <fstream>

#include "token.h"

// Syntax analyzer for Rat26F (Assignment 2).
// One function per rule of the rewritten grammar (left recursion removed, left factored).
// R29 <Empty> has no function of its own: it is the "empty" choice inside the Opt and Prime functions.

// Shared by all rule functions (defined in parser_p1.cpp).
extern Token token;              // current token from lexer()
extern std::ifstream inputFile;  // source file being parsed
extern std::ofstream outputFile; // output file for tokens and production rules
extern bool printRules;          // switch: true = print tokens and production rules

// ---- Person 1: R1 - R10 (parser_p1.cpp) ----
void rat26f();                    // R1
void optFunctionDefinitions();    // R2
void functionDefinitions();       // R3
void functionDefinitionsPrime();  // R3
void functionDef();               // R4
void optParameterList();          // R5
void parameterList();             // R6
void parameterListPrime();        // R6
void parameter();                 // R7
void qualifier();                 // R8
void body();                      // R9
void optDeclarationList();        // R10

// ---- Person 2: R11 - R19 (parser_p2.cpp) ----
void declarationList();           // R11
void declarationListPrime();      // R11
void declaration();               // R12
void ids();                       // R13
void idsPrime();                  // R13
void statementList();             // R14
void statementListPrime();        // R14
void statement();                 // R15
void compound();                  // R16
void assign();                    // R17
void ifStatement();               // R18
void ifPrime();                   // R18
void returnStatement();           // R19
void returnPrime();               // R19

// ---- Person 3: R20 - R28 (parser_p3.cpp) ----
void print();                     // R20
void scan();                      // R21
void whileStatement();            // R22
void condition();                 // R23
void relop();                     // R24
void expression();                // R25
void expressionPrime();           // R25
void term();                      // R26
void termPrime();                 // R26
void factor();                    // R27
void primary();                   // R28
void primaryPrime();              // R28
