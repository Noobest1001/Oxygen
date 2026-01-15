cmake_minimum_required(VERSION 4.0)
project(Oxygen)

set(CMAKE_CXX_STANDARD 23)

add_executable(Oxygen
  src/main.cpp
  src/Arena.cpp
  src/Tokenizer.cpp
  src/Parser.cpp
  src/Generate.cpp
  src/GenerateExpression.cpp
  src/GenerateStatement.cpp
)

target_include_directories(Oxygen PRIVATE helpers)
