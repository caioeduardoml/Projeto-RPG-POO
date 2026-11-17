cmake_minimum_required(VERSION 3.16)
project(rpg_manager LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(ENABLE_SANITIZERS "Habilita AddressSanitizer e UndefinedBehaviorSanitizer em Debug" OFF)

# Biblioteca estatica com o nucleo de regras de negocio (sem dependencia de GUI)
file(GLOB_RECURSE RPG_CORE_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/core/*.cpp"
)

add_library(rpg_core STATIC ${RPG_CORE_SOURCES})
target_include_directories(rpg_core PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_compile_options(rpg_core PRIVATE
    -Wall -Wextra -Wpedantic -Wshadow -Wconversion
)

if(ENABLE_SANITIZERS)
    target_compile_options(rpg_core PUBLIC -O1 -g -fsanitize=address,undefined -fno-omit-frame-pointer)
    target_link_options(rpg_core PUBLIC -fsanitize=address,undefined)
endif()

# Aplicacao GUI com Qt5
find_package(Qt5 COMPONENTS Widgets REQUIRED)
set(CMAKE_AUTOMOC ON)

add_executable(rpg_game
    src/main.cpp
    src/MainWindow.cpp
    include/MainWindow.hpp
)
target_link_libraries(rpg_game PRIVATE rpg_core Qt5::Widgets)
target_compile_options(rpg_game PRIVATE
    -Wall -Wextra -Wpedantic -Wshadow -Wconversion
)

# Testes unitarios com GoogleTest
find_package(GTest REQUIRED)
enable_testing()

add_executable(test_rpg
    tests/test_main.cpp
    tests/test_rpg.cpp
)
target_link_libraries(test_rpg PRIVATE rpg_core GTest::gtest GTest::gtest_main pthread)
target_compile_options(test_rpg PRIVATE
    -Wall -Wextra -Wpedantic -Wshadow -Wconversion
)

add_test(NAME RpgUnitTests COMMAND test_rpg)
