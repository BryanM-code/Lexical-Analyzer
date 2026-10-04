#pragma once

#include <istream>

#include "token.h"

// Person 1: Read an identifier or keyword, starting before its first letter.
// Leave the next character unread.
Token identifierFSM(std::istream& input);
