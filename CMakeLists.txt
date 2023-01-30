cmake_minimum_required(VERSION 3.24)
project(ProjetoMP)

set(CMAKE_CXX_STANDARD 23)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_executable(ProjetoMP
        main.cpp
        src/Builders.cpp
        src/Comandos.cpp
        src/Containers.cpp
        src/Controladoras.cpp
        src/Dominios.cpp
        src/Entidades.cpp
        src/Telas.cpp
        )

target_link_libraries(ProjetoMP ${CURSES_LIBRARIES})
target_include_directories(ProjetoMP PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)