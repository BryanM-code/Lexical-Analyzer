// Person 1: rules R1 - R10

#include "parser.h"

// Shared variables declared in parser.h (defined here, once).
Token token;
std::ifstream inputFile;
std::ofstream outputFile;
bool printRules = true;

// R1. <Rat26F> ::= <Opt Function Definitions> @ <Opt Declaration List> @ <Statement List>
void rat26f()
{
}

// R2. <Opt Function Definitions> ::= <Function Definitions> | <Empty>
void optFunctionDefinitions()
{
}

// R3. <Function Definitions> ::= <Function> <Function Definitions Prime>
void functionDefinitions()
{
}

// R3. <Function Definitions Prime> ::= <Function Definitions> | <Empty>
void functionDefinitionsPrime()
{
}

// R4. <Function> ::= function <Identifier> ( <Opt Parameter List> ) <Opt Declaration List> <Body>
void functionDef()
{
}

// R5. <Opt Parameter List> ::= <Parameter List> | <Empty>
void optParameterList()
{
}

// R6. <Parameter List> ::= <Parameter> <Parameter List Prime>
void parameterList()
{
}

// R6. <Parameter List Prime> ::= , <Parameter List> | <Empty>
void parameterListPrime()
{
}

// R7. <Parameter> ::= <IDs> <Qualifier>
void parameter()
{
}

// R8. <Qualifier> ::= integer | boolean | real
void qualifier()
{
}

// R9. <Body> ::= { <Statement List> }
void body()
{
}

// R10. <Opt Declaration List> ::= <Declaration List> | <Empty>
void optDeclarationList()
{
}
