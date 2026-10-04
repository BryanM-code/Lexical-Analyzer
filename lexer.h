#pragma once

#include <istream>

#include "token.h"

// Person 3: Return the next token, or {"eof", ""} at the end of the file.
Token lexer(std::istream& input);
