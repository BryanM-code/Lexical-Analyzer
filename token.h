#pragma once

#include <string>

// Shared by all three team members.
struct Token
{
    std::string type;   // identifier, keyword, integer, real, operator, separator, eof, invalid
    std::string lexeme; // Original source text, including letter case.
};
