#include "lexer.h"

#include "identifier.h"
#include "numbers.h"

Token lexer(std::istream& /* input */)
{
    // TODO: Person 3 - Skip whitespace and !...! comments.
    // Call identifierFSM() or numberFSM(), or read an operator/separator.
    // Handle != versus comments, invalid input, and end of file.
    return {"unimplemented", ""};
}
