cmake_minimum_required(VERSION 3.10)

# Defina o nome do projeto
project(pp2)

# Especificar o padrão de C++ (C++11, C++14, etc.)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Adicionar o executável
add_executable(pp2
    src/main.cc
)
