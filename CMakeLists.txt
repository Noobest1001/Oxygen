cmake_minimum_required(VERSION 4.1)
project(Oxygen C)

set(CMAKE_C_STANDARD 23)

add_executable(Oxygen
        src/main.c
        src/Tokenizer.h
        helpers/test.h)
