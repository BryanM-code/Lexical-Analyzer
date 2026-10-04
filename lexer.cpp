#include "lexer.h"

#include "identifier.h"
#include "numbers.h"

#include <cctype>
#include <string>

namespace
{
    const std::string SEPARATORS = "(){},;@";

    // helper function to handle operators and determine if they are two characters
    Token oneOrTwoCharOperator(std::istream& input, char first) {
        std::string lexeme(1, first);
        if (input.peek() == '=') {
            lexeme += static_cast<char>(input.get());
        }
        return {"operator", lexeme};
    }
}

Token lexer(std::istream& input)
{
    while (true) {
        int c = input.peek();

        // end of file was reached
        if (c == EOF) {
            return {"eof", ""};
        }
        // check and continue if whitespace
        if (std::isspace(c)) {
            input.get();
            continue;
        }

        // check if a comment has begun
        if (c == '!') {
            input.get();

            // not a comment, an operator
            if (input.peek() == '=') {
                input.get();
                return {"operator", "!="};
            }

            // ignore the content in the comment
            int d;
            while ((d = input.get()) != EOF && d != '!') {}
            if (d == EOF) {
                return {"invalid", "unterminated comment"};
            }
            continue;
        }
        break;
    }

    int c = input.peek();

    // check if current input begins with a letter
    if (std::isalpha(c)) {
        return identifierFSM(input);
    }
    // check if current input begins with a number or dot
    if (std::isdigit(c) || c == '.') {
        return numberFSM(input);
    }

    char ch = static_cast<char>(input.get());
    // check for operators
    switch (ch) {
        case '+':
        case '-':
        case '*':
        case '/':
            return {"operator", std::string(1, ch)};

        case '=':
        case '<':
        case '>':
            return oneOrTwoCharOperator(input, ch);

        default:
            break;
    }

    // check for separators
    if (SEPARATORS.find(ch) != std::string::npos) {
        return {"separator", std::string(1, ch)};
    }

    // any other input is invalid
    return {"invalid", std::string(1, ch)};
}
