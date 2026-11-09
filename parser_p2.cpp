// Person 2: rules R11 - R19

#include "parser.h"

// R11. <Declaration List> ::= <Declaration> ; <Declaration List Prime>
void declarationList()
{
}

// R11. <Declaration List Prime> ::= <Declaration List> | <Empty>
void declarationListPrime()
{
}

// R12. <Declaration> ::= <Qualifier> <IDs>
void declaration()
{
}

// R13. <IDs> ::= <Identifier> <IDs Prime>
void ids()
{
}

// R13. <IDs Prime> ::= , <IDs> | <Empty>
void idsPrime()
{
}

// R14. <Statement List> ::= <Statement> <Statement List Prime>
void statementList()
{
}

// R14. <Statement List Prime> ::= <Statement List> | <Empty>
void statementListPrime()
{
}

// R15. <Statement> ::= <Compound> | <Assign> | <If> | <Return> | <Print> | <Scan> | <While>
void statement()
{
}

// R16. <Compound> ::= { <Statement List> }
void compound()
{
}

// R17. <Assign> ::= <Identifier> = <Expression> ;
void assign()
{
}

// R18. <If> ::= if ( <Condition> ) <Statement> <If Prime>
void ifStatement()
{
}

// R18. <If Prime> ::= fi | else <Statement> fi
void ifPrime()
{
}

// R19. <Return> ::= return <Return Prime>
void returnStatement()
{
}

// R19. <Return Prime> ::= ; | <Expression> ;
void returnPrime()
{
}
