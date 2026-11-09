// Person 1: rules R1 - R10

#include "parser.h"
#include "lexer.h"
#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <iostream>
#include <string>

// Shared variables declared in parser.h (defined here, once).
Token token;
std::ifstream inputFile;
std::ofstream outputFile;
bool printRules = true;

// Lexer token types
static bool isEOF(const Token &t) { return t.type == "eof"; }
static bool isIdentifier(const Token &t) { return t.type == "identifier"; }

// Get current line for errors
static int currentLine() {
    inputFile.clear();
    std::streampos end = inputFile.tellg();
    inputFile.seekg(0);
    int line = 1;
    char c;
    while (inputFile.tellg() < end && inputFile.get(c)) {
       if (c == '\n') {
        ++ line;
       }
    }
    return line;
}

// get current lexeme
static bool lexemeIs(const char *s) {
    std::string a = token.lexeme;
    std::transform(a.begin(), a.end(), a.begin(), [](unsigned char c) { return std::tolower(c); });
    return a == s;
}

// print production statements
static void printRule(const std::string &rule) {
    if (printRules) {
        outputFile << "     " << rule << "\n";
    }
}

// get next token from lexer
static void advance() {
    token = lexer(inputFile);
    if (printRules && !isEOF(token)) {
        outputFile << "Token: " << token.type << "\tLexeme: " << token.lexeme << "\n";
    }
}

// syntax error handling
static void syntaxError(const std::string &expected, const std::string &rule) {
    std::string msg = "Syntax Error at line " + std::to_string(currentLine()) +
                      ": found Token: " + token.type + ", Lexeme: '" + token.lexeme +
                      "' but expected " + expected + " while parsing " + rule + ".";
    std::cerr << msg << "\n";
    if (outputFile.is_open()) {
        outputFile << "\n" << msg << "\n";  
    }
    std::exit(1);
}

// expected lexeme
static void expectLexeme(const char *lex, const std::string &rule) {
    if (!lexemeIs(lex)) {
        syntaxError(std::string("'") + lex + "'", rule);  
    }
    advance();
}

// expected token to be an identifier
static void expectIdentifier(const std::string &rule) {
    if (!isIdentifier(token)) {
        syntaxError("an identifier", rule);
    }
    advance();
}

// R1. <Rat26F> ::= <Opt Function Definitions> @ <Opt Declaration List> @ <Statement List>
void rat26f()
{
    advance();
    printRule("<Rat26F> -> <Opt Function Definitions> @ <Opt Declaration List> @ <Statement List>");
    
    optFunctionDefinitions();
    expectLexeme("@", "<Rat26F> (separator after function definitions)");
    optDeclarationList();
    expectLexeme("@", "<Rat26F> (separator after declaration list)");
    statementList();

    if (!isEOF(token)) {
        syntaxError("end of file", "<Rat26F>");
    }

}

// R2. <Opt Function Definitions> ::= <Function Definitions> | <Empty>
void optFunctionDefinitions()
{
    if (lexemeIs("function")) {
        printRule("<Opt Function Definitions> -> <Function Definitions>");
        functionDefinitions();
    } else {
        printRule("<Opt Function Definitions> -> <Empty>");
    }
}

// R3. <Function Definitions> ::= <Function> <Function Definitions Prime>
void functionDefinitions()
{
    printRule("<Function Definitions> -> <Function> <Function Definitions Prime>");
    functionDef();
    functionDefinitionsPrime();
}

// R3. <Function Definitions Prime> ::= <Function Definitions> | <Empty>
void functionDefinitionsPrime()
{
    if (lexemeIs("function")) {
        printRule("<Function Definitions Prime> -> <Function Definitions>");
        functionDefinitions();
    } else {
        printRule("<Function Definitions Prime> -> <Empty>");
    }
}

// R4. <Function> ::= function <Identifier> ( <Opt Parameter List> ) <Opt Declaration List> <Body>
void functionDef()
{
    printRule("<Function> -> function <Identifier> ( <Opt Parameter List> ) <Opt Declaration List> <Body>");
    expectLexeme("function", "<Function>");
    expectIdentifier("<Function> (function name)");
    expectLexeme("(", "<Function>");
    optParameterList();
    expectLexeme(")", "<Function>");
    optDeclarationList();
    body();
}

// R5. <Opt Parameter List> ::= <Parameter List> | <Empty>
void optParameterList()
{
    if (isIdentifier(token)) {
        printRule("<Opt Parameter List> -> <Parameter List>");
        parameterList();
    } else {
        printRule("<Opt Parameter List> -> <Empty>");
    }
}

// R6. <Parameter List> ::= <Parameter> <Parameter List Prime>
void parameterList()
{
    printRule("<Parameter List> -> <Parameter> <Parameter List Prime>");
    parameter();
    parameterListPrime();
}

// R6. <Parameter List Prime> ::= , <Parameter List> | <Empty>
void parameterListPrime()
{
    if (lexemeIs(",")) {
        printRule("<Parameter List Prime> -> , <Parameter List>");
        advance();
        parameterList();
    } else {
        printRule("<Parameter List Prime> -> <Empty>");
    }
}

// R7. <Parameter> ::= <IDs> <Qualifier>
void parameter()
{
    printRule("<Parameter> -> <IDs> <Qualifier>");
    ids();
    qualifier();
}

// R8. <Qualifier> ::= integer | boolean | real
void qualifier()
{
    if (lexemeIs("integer")) {
        printRule("<Qualifier> -> integer");
    } else if (lexemeIs("boolean")) {
        printRule("<Qualifier> -> boolean");
    } else if (lexemeIs("real")) {
        printRule("<Qualifier> -> real");
    } else {
        syntaxError("'integer', 'boolean' or 'real'", "<Qualifier>");
    }
    advance();
}

// R9. <Body> ::= { <Statement List> }
void body()
{
    printRule("<Body> -> { <Statement List> }");
    expectLexeme("{", "<Body>");
    statementList();
    expectLexeme("}","<Body>");
}

// R10. <Opt Declaration List> ::= <Declaration List> | <Empty>
void optDeclarationList()
{
    if (lexemeIs("integer") || lexemeIs("boolean") || lexemeIs("real")) {
        printRule("<Opt Declaration List> -> <Declaration List>");
        declarationList();
    } else {
        printRule("<Opt Declaration List> -> <Empty>");
    }
}
