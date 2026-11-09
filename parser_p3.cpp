// Person 3: rules R20 - R28
// Print, Scan, While, Condition, Relop and arithmetic expressions.

#include "parser.h"
#include "lexer.h"

#include <cctype>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <string>

// ---------------- Small helpers used only in this file ----------------

// Read the next token into 'token' and print it (if the switch is on).
static void nextToken()
{
    token = lexer(inputFile);

    if (printRules && token.type != "eof") {
        outputFile << "Token: " << std::left << std::setw(14) << token.type
                   << "Lexeme: " << token.lexeme << "\n";
    }
}

// Print a production rule (if the switch is on).
static void printRule(const std::string& rule)
{
    if (printRules) {
        outputFile << "     " << rule << "\n";
    }
}

// The current lexeme in lowercase, because keywords are not case sensitive (WHILE = while).
static std::string lowercaseLexeme()
{
    std::string lexeme = token.lexeme;

    for (char& ch : lexeme) {
        ch = static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
    }
    return lexeme;
}

// Print a syntax error to the output file and the screen, then stop the program.
static void syntaxError(const std::string& expected)
{
    std::string found;
    if (token.type == "eof") {
        found = "end of file";
    } else {
        found = token.type + " '" + token.lexeme + "'";
    }

    std::string message = "Syntax error: expected " + expected + " but found " + found;
    outputFile << "\n" << message << "\n";
    std::cout << message << "\n";
    std::exit(1);
}

// If the current token is 'expected', move past it. Otherwise report a syntax error.
static void match(const std::string& expected)
{
    if (lowercaseLexeme() == expected) {
        nextToken();
    } else {
        syntaxError("'" + expected + "'");
    }
}

// ---------------- Rule functions ----------------

// R20. <Print> ::= put ( <Expression> ) ;
void print()
{
    printRule("<Print> -> put ( <Expression> ) ;");
    match("put");
    match("(");
    expression();
    match(")");
    match(";");
}

// R21. <Scan> ::= get ( <IDs> ) ;
void scan()
{
    printRule("<Scan> -> get ( <IDs> ) ;");
    match("get");
    match("(");
    ids();                 // Person 2 (R13)
    match(")");
    match(";");
}

// R22. <While> ::= while ( <Condition> ) <Statement>
void whileStatement()
{
    printRule("<While> -> while ( <Condition> ) <Statement>");
    match("while");
    match("(");
    condition();
    match(")");
    statement();           // Person 2 (R15)
}

// R23. <Condition> ::= <Expression> <Relop> <Expression>
void condition()
{
    printRule("<Condition> -> <Expression> <Relop> <Expression>");
    expression();
    relop();
    expression();
}

// R24. <Relop> ::= == | != | > | < | <= | >=
void relop()
{
    std::string op = token.lexeme;

    if (op == "==" || op == "!=" || op == ">" || op == "<" || op == "<=" || op == ">=") {
        printRule("<Relop> -> " + op);
        nextToken();
    } else {
        syntaxError("a relational operator (==, !=, >, <, <=, >=)");
    }
}

// R25. <Expression> ::= <Term> <Expression Prime>
void expression()
{
    printRule("<Expression> -> <Term> <Expression Prime>");
    term();
    expressionPrime();
}

// R25. <Expression Prime> ::= + <Term> <Expression Prime> | - <Term> <Expression Prime> | <Empty>
void expressionPrime()
{
    if (token.lexeme == "+" || token.lexeme == "-") {
        printRule("<Expression Prime> -> " + token.lexeme + " <Term> <Expression Prime>");
        nextToken();
        term();
        expressionPrime();
    } else {
        printRule("<Expression Prime> -> ε");
    }
}

// R26. <Term> ::= <Factor> <Term Prime>
void term()
{
    printRule("<Term> -> <Factor> <Term Prime>");
    factor();
    termPrime();
}

// R26. <Term Prime> ::= * <Factor> <Term Prime> | / <Factor> <Term Prime> | <Empty>
void termPrime()
{
    if (token.lexeme == "*" || token.lexeme == "/") {
        printRule("<Term Prime> -> " + token.lexeme + " <Factor> <Term Prime>");
        nextToken();
        factor();
        termPrime();
    } else {
        printRule("<Term Prime> -> ε");
    }
}

// R27. <Factor> ::= - <Primary> | <Primary>
void factor()
{
    if (token.lexeme == "-") {
        printRule("<Factor> -> - <Primary>");
        nextToken();
        primary();
    } else {
        printRule("<Factor> -> <Primary>");
        primary();
    }
}

// R28. <Primary> ::= <Identifier> <Primary Prime> | <Integer> | ( <Expression> ) | <Real> | true | false
void primary()
{
    if (token.type == "identifier") {
        printRule("<Primary> -> <Identifier> <Primary Prime>");
        nextToken();
        primaryPrime();
    } else if (token.type == "integer") {
        printRule("<Primary> -> <Integer>");
        nextToken();
    } else if (token.lexeme == "(") {
        printRule("<Primary> -> ( <Expression> )");
        nextToken();
        expression();
        match(")");
    } else if (token.type == "real") {
        printRule("<Primary> -> <Real>");
        nextToken();
    } else if (lowercaseLexeme() == "true") {
        printRule("<Primary> -> true");
        nextToken();
    } else if (lowercaseLexeme() == "false") {
        printRule("<Primary> -> false");
        nextToken();
    } else {
        syntaxError("an identifier, integer, real, '(', true or false");
    }
}

// R28. <Primary Prime> ::= ( <IDs> ) | <Empty>
void primaryPrime()
{
    if (token.lexeme == "(") {
        printRule("<Primary Prime> -> ( <IDs> )");
        nextToken();
        ids();             // Person 2 (R13)
        match(")");
    } else {
        printRule("<Primary Prime> -> ε");
    }
}
