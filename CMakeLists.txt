cmake_minimum_required(VERSION 3.22)
project(ProjetoMP)

set(CMAKE_CXX_STANDARD 23)

SET(GCC_COVERAGE_COMPILE_FLAGS "-g -O0 -coverage -fprofile-arcs -ftest-coverage")
SET(GCC_COVERAGE_LINK_FLAGS    "-coverage -lgcov")
SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )
SET( CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}" )


find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})


enable_testing()

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
