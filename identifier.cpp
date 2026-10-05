#include "identifier.h"
#include <cctype>
#include <string>
#include <unordered_set>

Token identifierFSM(std::istream& input)
{
    enum class State
    {
        Start,
        InIdentifier
    };

    // Potential keywords. 
    static const std::unordered_set<std::string> keywords = {
        "function", "integer", "boolean", "real",
        "if", "else", "fi", "while", "return",
        "get", "put", "true", "false"
    };

    State state = State::Start; 
    std::string lexeme;

    while (true)
    {
        int next = input.peek();

        if (next == std::char_traits<char>::eof())
        {
            break;
        }

        // Convert 'next' into unsigned char, this is needed for 'isalpha()'.
        unsigned char ch = static_cast<unsigned char>(next); 

        if (state == State::Start)
        {
            
            if (!std::isalpha(ch)) // Checks if the first char is a letter.
            {
                return {
                    "invalid",
                    std::string(1, static_cast<char>(input.get()))
                };
            }

            lexeme += static_cast<char>(input.get());
            state = State::InIdentifier; 
            // Since input starts with a letter, its now a possible identifier.
        }
        else
        {
            
            if (std::isalnum(ch) || ch == '_') // Later chars may have D,L, or '_'
            {
                lexeme += static_cast<char>(input.get());
            }
            else
            {
                break; // Leave this char for the next lexer call.
            }
        }
    }

    if (state == State::Start) // If still in start, char was never accepted. 
    {
        return {"eof", ""};
    }

    int next = input.peek();
    if (next == '.')
    {
        // A word and a decimal number must be separated by whitespace.
        do
        {
            lexeme += static_cast<char>(input.get());
            next = input.peek();
        }
        while (next != std::char_traits<char>::eof() &&
               (std::isalnum(static_cast<unsigned char>(next)) ||
                next == '_' || next == '.'));

        return {"invalid", lexeme};
    }

    // Normalize a copy for case insensitive keyword lookup.
    std::string normalized = lexeme;

    for (char& ch : normalized)
    {
        ch = static_cast<char>(
            std::tolower(static_cast<unsigned char>(ch))
        );
    }

    if (keywords.find(normalized) != keywords.end())
    {
        return {"keyword", lexeme};
    }

    return {"identifier", lexeme};
}
