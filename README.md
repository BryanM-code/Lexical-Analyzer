# Rat26F Syntax Analyzer (CPSC 323, Assignment 2)

A top-down, recursive-descent parser for the Rat26F language, built on the lexical
analyzer from Assignment 1. It reads a Rat26F source file and writes every token and
lexeme to an output file, followed by the grammar rules used to analyze it. On a
syntax error it reports the line number, what was expected and the token that was
found, then stops.

## Run the program

```powershell
.\rat26f_lexer.exe <source_file> [output_file]
```

- `source_file`: the Rat26F program to analyze (required).
- `output_file`: where the tokens, lexemes and rules are written (optional, default `output.txt`).

Example, using the included tests:

```powershell
.\rat26f_lexer.exe parser_test1.txt parser_output1.txt
```

The screen shows `Parsing complete: no syntax errors found.` or the syntax error.
To turn off the token and rule printing, set `bool printRules = false;` in
`parser_p1.cpp` and rebuild.

## Compile with g++

Open the project folder in VS Code, choose **Terminal > New Terminal**, and run:

```powershell
g++ -std=c++17 -Wall -Wextra -static main.cpp identifier.cpp numbers.cpp lexer.cpp parser_p1.cpp parser_p2.cpp parser_p3.cpp -o rat26f_lexer.exe
```

You need a C++17-compatible GCC compiler. If `g++` is not recognized, make sure
it is installed and its `bin` folder is on PATH. Headers are included by the
`.cpp` files, so they do not need to be listed in the command. `-static` builds
an `.exe` that also runs on computers without MSYS2/MinGW installed.

## Optional CMake build

This option needs a compiler, CMake, and Ninja. With MSYS2 UCRT64 on Windows,
install CMake and Ninja once from the **MSYS2 UCRT64** terminal:

```bash
pacman -S mingw-w64-ucrt-x86_64-cmake mingw-w64-ucrt-x86_64-ninja
```

See the [MSYS2 CMake guide](https://www.msys2.org/docs/cmake/).
Then, from the project folder in PowerShell:

```powershell
cmake -S . -B build -G Ninja
cmake --build build
.\build\rat26f_lexer.exe parser_test1.txt parser_output1.txt
```

After code changes, repeat the last two commands.

## Files

| File | Purpose |
|---|---|
| `main.cpp` | Opens the files, reads the first token, calls `rat26f()` to parse the program. |
| `token.h`, `lexer.h`, `lexer.cpp`, `identifier.*`, `numbers.*` | Lexical analyzer from Assignment 1. |
| `parser.h` | Declares one function per rule of the rewritten grammar, plus the shared variables. |
| `parser_p1.cpp` | Rules R1 - R10 (program, functions, parameters, qualifier, body). |
| `parser_p2.cpp` | Rules R11 - R19 (declarations, IDs, statement list, compound, assign, if, return). |
| `parser_p3.cpp` | Rules R20 - R28 (put, get, while, condition, relop, expressions). |
| `parser_test1.txt` - `parser_test3.txt` | Assignment 2 test programs (7, 18 and 42 lines). |
| `parser_output1.txt` - `parser_output3.txt` | Output of the parser for each test program. |
| `test1.txt` - `test3.txt`, `output1.txt` - `output3.txt` | Assignment 1 lexer tests. |
