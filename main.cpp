#include "lexer.h"
#include "parser.h"

#include <iostream>
#include <iomanip>
#include <string>

// command line arguments
// .\rat26f_lexer <source_file> [output_file]
// argv[1] : source file to read
// argv[2] : output file to write (optional, default output.txt)
int main(int argc, char* argv[])
{
    // not enough arguments, needs source file
    if (argc < 2) {
        std::cout << "usage: " << argv[0] << " <source_file> [output_file]\n";
        return 1;
    }

    const std::string sourceName = argv[1];
    const std::string outputName = (argc > 2) ? argv[2] : "output.txt";

    // open source file to read (inputFile is shared with the parser, see parser.h)
    inputFile.open(sourceName);
    if (!inputFile) {
        std::cerr << "error: cannot open source file '" << sourceName << "'\n";
        return 1;
    }
    // open output file to write (outputFile is shared with the parser, see parser.h)
    outputFile.open(outputName);
    if (!outputFile) {
        std::cerr << "error: cannot open output file '" << outputName << "'\n";
        return 1;
    }

    // read the first token: every rule function expects 'token' to already hold the current token
    token = lexer(inputFile);
    if (printRules && token.type != "eof") {
        outputFile << "Token: " << std::left << std::setw(14) << token.type
                   << "Lexeme: " << token.lexeme << "\n";
    }

    // parse the whole program, starting from R1 <Rat26F>
    // (on a syntax error the parser prints the message and stops the program, so it never returns here)
    rat26f();

    outputFile << "\nParsing complete: no syntax errors found.\n";
    std::cout << "Parsing complete: no syntax errors found.\n";
    return 0;
}
