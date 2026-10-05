#include "token.h"
#include "numbers.h"
#include <iostream>
#include <cctype>

namespace{
    // int: d+
    // real: d*.d*

    enum State {
        start,
        initial_dig,
        initial_dot,
        after_dot,
        dap, // digit after period/dot
        done
    };

    bool isDigit(int c) {
        // if not end of file and c is a digit 
        return c != EOF && std::isdigit(static_cast<unsigned char>(c)) != 0;
    }
} // namespace

// FSM for integers and reals
Token numberFSM(std::istream& input) {
    State state = start;
    std::string lex;

    while (state != done) {
        int c = input.peek();
        switch(state) {
        case start: // if digit go to int accepting state, if dot go to after_dpt state, else invalid
            if (isDigit(c)) {
                lex += static_cast<char>(input.get());
                state = initial_dig;
            } else if(c == '.') {
                lex += static_cast<char>(input.get());
                state = after_dot;
            } else {
                return {"invalid", ""}; // shouldn't be able to get to this point
            }
            break;
        
        case initial_dig: // if digit comes after digit add to token, else (white space or comment) accept state
            if (isDigit(c)) {
                lex += static_cast<char>(input.get());
            } else if (c == '.') {
                lex += static_cast<char>(input.get());
                state = initial_dot;
            } else {
                state = done; // accepting int
            }
            break;

        case initial_dot: // A decimal point must be followed by a digit.
            if (isDigit(c)) {
                lex += static_cast<char>(input.get());
                state = dap;
            } else {
                return {"invalid", lex};
            }
            break;

        case after_dot: // if digit go to dap state, else invalid (dot after dot)
            if (isDigit(c)) {
                lex += static_cast<char>(input.get());
                state = dap;
            } else {
                return {"invalid", lex};
            }
            break;

        case dap: // if digit comes after dot add to token, else (white space or comment) accept the real num
            if(isDigit(c)) {
                lex += static_cast<char>(input.get());
            } else {
                state = done; // accepting real
            }
        case done:
            break;
        }
    }

    int next = input.peek();
    if (next != EOF &&
        (std::isalpha(static_cast<unsigned char>(next)) ||
         next == '_' || next == '.')) {
        // A number cannot be immediately followed by a word or another decimal.
        do {
            lex += static_cast<char>(input.get());
            next = input.peek();
        } while (next != EOF &&
                 (std::isalnum(static_cast<unsigned char>(next)) ||
                  next == '_' || next == '.'));

        return {"invalid", lex};
    }

    // if lexeme doesn't have a dot, return int, else return real
    if (lex.find(".") == std::string::npos) {
        return {"integer", lex};
    } else {
        return {"real", lex};
    }
}
