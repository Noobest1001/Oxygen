cmake_minimum_required(VERSION 4.0)
project(Oxygen)

set(CMAKE_CXX_STANDARD 23)

add_executable(Oxygen src/main.cpp
        helpers/Tokenizer.hpp
        helpers/Generation.hpp
        helpers/Arena.hpp
        helpers/Parser.hpp
)
