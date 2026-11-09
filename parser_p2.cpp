// Person 2: rules R11 - R19

#include "parser.h"
#include "lexer.h"

#include <iostream>
#include <cctype>
#include <iomanip>
#include <string>
#include <sstream>

namespace {
    // private helper
    std::string lower(std::string s) {
        for (char &c : s) {
            c = static_cast<char>(std::tolower(static_cast<unsigned char> (c)));
        }
        return s;
    }
    
    std::string capitalize(std::string s) {
        if (!s.empty()) {
            s[0] = static_cast<char>(std::toupper(static_cast<unsigned char> (s[0])));
        }
        return s;
    }
    void advance() {
        token = lexer(inputFile);
        if (printRules) {
            outputFile << "Token: " << std::left << std::setw(12) << capitalize(token.type) << " Lexeme: " << token.lexeme << "\n";
        }
    }
    void rule(const std::string &text) {
        if (printRules) {
            outputFile <<  "   " << text << "\n";
        }
    }
    bool isType(const char * t) {
        return token.type == t;
    }
    bool isSym(const char * s) {
        return (token.type == "operator" || token.type == "separator") && token.lexeme == s;
    }
    bool isKw(const char * s) {
        return token.type == "keyword" && lower(token.lexeme) == s;
    }
    bool isQualifier() {
        return isKw("integer") || isKw("boolean") || isKw("real");
    }
    bool isStatementStart() {
        return isSym("{") || isSym("identifier") || isKw("if") || isKw("return") || isKw("put") || isKw("get") || isKw("while");
    }
    // line # of token
    int currentLine() {
        inputFile.clear();
        std::streampos pos = inputFile.tellg();
        if (pos < 0) {
            return 1;
        }
        int line = 1;
        char c;
        inputFile.seekg(0);
        while (inputFile.tellg() < pos && inputFile.get(c)) {
            if (c == '\n') {
                line++;
            }
        }
        inputFile.clear();
        inputFile.seekg(pos);
        return line;
    }
    // error message
    void fail(const std::string &errorType) {
        std::ostringstream msg;
        msg << "Syntax error at line " << currentLine() << ": token = " << capitalize(token.type) << ", lexeme = " << token.lexeme << "'";
        if (isType("eof")) {
            msg << " (end of file)";
        }
        msg << ", error type = ";
        if(isType("invalid")) {
            msg << "invalid token; ";
        }
        msg << errorType;
        outputFile << "\n" << msg.str() << "\n";
        outputFile.flush();
        std::cerr << msg.str() << "\n";
        std::exit(2);
    }
    void expectSym(const char * s, const std::string & context) {
        if (!isSym(s)) {
            fail("'" + std::string(s) + "' expected" + (context.empty() ? "" : " " + context));
        }
        advance();
    }
    void expectKw(const char * s) {
        if (!isKw(s)) {
            fail("keyword '" + std::string(s) + "' expected");
        }
        advance();
    }
    void expectIdentifier() {
        if (!isType("identifier")) {
            fail("identifier expected");
        }
        advance();
    }
} // namespace


// R11. <Declaration List> ::= <Declaration> ; <Declaration List Prime>
void declarationList() {
    rule("<Declaration List> ::= <Declaration> ; <Declaration List Prime>");
    declaration();
    expectSym(";", "after the declaration");
    declarationListPrime();
}

// R11. <Declaration List Prime> ::= <Declaration List> | <Empty>
void declarationListPrime() {
    if (isQualifier()) {
        rule("<Declaration List Prime> ::= <Declaration List>");
        declarationList();
    } else {
        rule("<Declaration List Prime> -> \xCE\xB5"); // displays epsilon symbol
    }
}

// R12. <Declaration> ::= <Qualifier> <IDs>
void declaration() {
    rule("<Declaration -> <Qualifier> <IDs>");
    qualifier();
    ids();
}

// R13. <IDs> ::= <Identifier> <IDs Prime>
void ids() {
    rule("<IDs -> <Identifier> <IDs Prime>");
    expectIdentifier();
    idsPrime();
}

// R13. <IDs Prime> ::= , <IDs> | <Empty>
void idsPrime() {
    if (isSym(",")) {
        rule("<IDs Prime> -> , <IDs>");
        advance();
        ids();
    } else {
        rule("<IDs Prime> -> \xCE\xB5");
    }
}

// R14. <Statement List> ::= <Statement> <Statement List Prime>
void statementList() {
    rule("<Statement List> -> <Statement> <Statement List Prime>");
    statement();
    statementListPrime();
}

// R14. <Statement List Prime> ::= <Statement List> | <Empty>
void statementListPrime() {
    if(isStatementStart()) {
        rule("<Statement List Prime> -> <Statement List>");
        statementList();
    } else {
        rule("<Statement List Prime> -> \xCE\xB5");
    }
}

// R15. <Statement> ::= <Compound> | <Assign> | <If> | <Return> | <Print> | <Scan> | <While>
void statement() {
    if (isSym("{")) {
        rule("<Statement> -> <Compound>");
        compound();
    } else if(isType("identifier")) {
        rule("<Statement> -> <Assign>");
        assign();
    } else if (isKw("if")) {
        rule("<Statement> -> <If>");
        ifStatement();
    } else if(isKw("return")) {
        rule("<Statement> -> <Return>");
        returnStatement();
    } else if (isKw("put")) {
        rule("<Statement> -> <Print>");
        print();
    } else if (isKw("get")) {
        rule("<Statement> -> <Scan>");
        scan();
    } else if (isKw("while")) {
        rule("<Statement> -> <While>");
        whileStatement();
    } else {
        fail("statement expected");
    }
}

// R16. <Compound> ::= { <Statement List> }
void compound() {
    rule("<Compound> -> { Statement List > }");
    expectSym("{", "");
    statementList();
    expectSym("}", "to close the compound statement");
}

// R17. <Assign> ::= <Identifier> = <Expression> ;
void assign() {
    rule("<Assign> -> <Identifier> = <Expression> ;");
    expectIdentifier();
    expectSym("=", "after the identifier in an asignment");
    expression();
    expectSym(";", "at the end of assignment");
}

// R18. <If> ::= if ( <Condition> ) <Statement> <If Prime>
void ifStatement() {
    rule("<If> -> if ( <Condition> ) <Statement> <If Prime>");
    expectKw("if");
    expectSym("(", "after 'if'");
    condition();
    expectSym(")", "after the condition");
    statement();
    ifPrime();
}

// R18. <If Prime> ::= fi | else <Statement> fi
void ifPrime() {
    if(isKw("fi")) {
        rule("<If Prime> -> fi");
        advance();
    } else if (isKw("else")) {
        rule("<If Prime> -> else <Statement> fi");
        advance();
        statement();
        expectKw("fi");
    } else {
        fail("'fi' or 'else' expected");
    }
}

// R19. <Return> ::= return <Return Prime>
void returnStatement() {
    rule("<Return> -> return <Return Prime>");
    expectKw("return");
    returnPrime();
}

// R19. <Return Prime> ::= ; | <Expression> ;
void returnPrime() {
    if(isSym(";")) {
        rule("<Return Prime -> ;");
        advance();
    } else{
        rule("<Return Prime> -> <Expression> ;");
        expression();
        expectSym(";", "at the end of the return statement");
    }
}
