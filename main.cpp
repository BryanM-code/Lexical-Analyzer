#include "lexer.h"

#include <iostream>
#include <iomanip>
#include <fstream>
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

    // open source file to read
    std::ifstream source(sourceName);
    if (!source) {
        std::cerr << "error: cannot open source file '" << sourceName << "'\n";
        return 1;
    }
    // open output file to write
    std::ofstream output(outputName);
    if (!output) {
        std::cerr << "error: cannot open output file '" << outputName << "'\n";
        return 1;
    }

    // header for output file
    output << std::left << std::setw(12) << "token" << "lexeme\n\n";
    //std::cout << std::left << std::setw(12) << "token" << "lexeme\n\n";

    // loop through the input file
    while (true) {
        Token tok = lexer(source);

        if (tok.type == "eof") {
            break;
        }

        output << std::left << std::setw(12) << tok.type << tok.lexeme << "\n";
        //std::cout << std::left << std::setw(12) << tok.type << tok.lexeme << "\n";

    }

    return 0;
}
