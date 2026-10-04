

## Compile and run with g++

Open the `Rat26F_Lexer` folder in VS Code, then choose **Terminal > New Terminal**.
Run these commands in PowerShell from the folder containing `main.cpp`:

```powershell
g++ -std=c++17 -Wall -Wextra -Wpedantic main.cpp identifier.cpp numbers.cpp lexer.cpp -o rat26f_lexer.exe
.\rat26f_lexer.exe
```

You need a C++17-compatible GCC compiler. If `g++` is not recognized, make sure
it is installed and its `bin` folder is on PATH. Recompile after changing code,
and only run the executable if compilation succeeds. Headers are included by
the `.cpp` files, so they do not need to be listed in the command.

Expected output for the starter:

```text
not implemented yet.
```

## Optional CMake build, You dont have to do this if you dont want to.

This option needs a compiler, CMake, and Ninja. With MSYS2 UCRT64 on Windows,
install CMake and Ninja once from the **MSYS2 UCRT64** terminal:

```bash
pacman -S mingw-w64-ucrt-x86_64-cmake mingw-w64-ucrt-x86_64-ninja
```

See the [MSYS2 CMake guide](https://www.msys2.org/docs/cmake/).
Then, from the project folder in PowerShell, configure your local copy once:

```powershell
cmake -S . -B build -G Ninja
```

Compile and run:

```powershell
cmake --build build
.\build\rat26f_lexer.exe
```

After code changes, repeat the last two commands. Each person generates
their own `build` folder. Share `CMakeLists.txt` and the source files; generated
build folders and local executables can be recreated. Teammates may also use
the direct `g++` command instead.

