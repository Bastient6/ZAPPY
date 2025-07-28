cmake_minimum_required(VERSION 3.28)
project(gui CXX)

file(GLOB_RECURSE SOURCES "src/*.cpp" "src/Parser/*.cpp")
file(GLOB_RECURSE HEADERS "include/*.hpp" "include/Parser/*.hpp")

set(CMAKE_CXX_STANDARD 11)

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)

add_executable(gui ${SOURCES} ${HEADERS})

target_link_libraries(gui sfml-system sfml-window sfml-graphics sfml-network sfml-audio)

target_include_directories(gui PRIVATE include)
