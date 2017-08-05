cmake_minimum_required(VERSION 2.8)

project(Compiler)

set(CONFIGURATION_NAME "Debug")

# Установка переменных со списком исходников
set(Sources main.cpp lexer.cpp parser.cpp nodeBase.cpp nodeFunction.cpp nodeStmts.cpp nodeDeclare.cpp)
set(Headers constants.h token.h parser.h nodeBase.h nodeFunction.h nodeStmts.h nodeDeclare.h)

# include_directories(.)

# Compiler options
add_definitions(-std=c++14 -Wall -O0)

# Создает исполняемый файл с именем main
add_executable(${PROJECT_NAME} ${Sources} ${Headers})
