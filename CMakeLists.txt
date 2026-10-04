cmake_minimum_required(VERSION 3.16)
project(Rat26F_Lexer LANGUAGES CXX)

add_executable(rat26f_lexer
    main.cpp
    identifier.cpp
    numbers.cpp
    lexer.cpp
)

target_compile_features(rat26f_lexer PRIVATE cxx_std_17)
set_target_properties(rat26f_lexer PROPERTIES CXX_EXTENSIONS OFF)
