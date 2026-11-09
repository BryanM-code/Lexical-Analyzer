// Person 3: rules R20 - R28

#include "parser.h"

// R20. <Print> ::= put ( <Expression> ) ;
void print()
{
}

// R21. <Scan> ::= get ( <IDs> ) ;
void scan()
{
}

// R22. <While> ::= while ( <Condition> ) <Statement>
void whileStatement()
{
}

// R23. <Condition> ::= <Expression> <Relop> <Expression>
void condition()
{
}

// R24. <Relop> ::= == | != | > | < | <= | >=
void relop()
{
}

// R25. <Expression> ::= <Term> <Expression Prime>
void expression()
{
}

// R25. <Expression Prime> ::= + <Term> <Expression Prime> | - <Term> <Expression Prime> | <Empty>
void expressionPrime()
{
}

// R26. <Term> ::= <Factor> <Term Prime>
void term()
{
}

// R26. <Term Prime> ::= * <Factor> <Term Prime> | / <Factor> <Term Prime> | <Empty>
void termPrime()
{
}

// R27. <Factor> ::= - <Primary> | <Primary>
void factor()
{
}

// R28. <Primary> ::= <Identifier> <Primary Prime> | <Integer> | ( <Expression> ) | <Real> | true | false
void primary()
{
}

// R28. <Primary Prime> ::= ( <IDs> ) | <Empty>
void primaryPrime()
{
}
