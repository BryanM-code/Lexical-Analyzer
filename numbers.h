#pragma once

#include <istream>

#include "token.h"

// Person 2: Read an integer or real, starting before its first digit or '.'.
// Leave the next character unread.
Token numberFSM(std::istream& input);
