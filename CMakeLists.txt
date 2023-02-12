cmake_minimum_required(VERSION 3.22)
project(ProjetoMP)

set(CMAKE_CXX_STANDARD 23)

SET(GCC_COVERAGE_COMPILE_FLAGS "-g -O0 -coverage -fprofile-arcs -ftest-coverage")
SET(GCC_COVERAGE_LINK_FLAGS    "-coverage -lgcov")
SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )
SET( CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}" )


find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(ProjetoMP
        main.cpp
        # src/Builders.cpp
        # src/Comandos.cpp
        # src/Containers.cpp
        src/Controladoras.cpp
        src/Entidades.cpp
        src/Telas.cpp
        src/ComandosSQL.cpp
        )

target_link_libraries(ProjetoMP ${CURSES_LIBRARIES} sqlite3)
target_include_directories(ProjetoMP PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

enable_testing()

add_executable(Testes
  tests/TestesEntidades.cpp
)
target_link_libraries(
  Testes
  GTest::gtest_main
)

target_include_directories(Testes PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

include(GoogleTest)
gtest_discover_tests(Testes)
