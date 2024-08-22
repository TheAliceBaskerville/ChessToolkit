cmake_minimum_required(VERSION 3.22)

project(ChessToolkit LANGUAGES CXX VERSION 0.0.1)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Wsign-conversion -Wfloat-equal")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

include_directories("${CMAKE_SOURCE_DIR}/lib/SFML/include")
link_directories("${CMAKE_SOURCE_DIR}/lib/SFML/lib")

set(SFML_DIR "${CMAKE_SOURCE_DIR}/lib/SFML/lib/cmake/SFML")
find_package(SFML 2.6.1 REQUIRED COMPONENTS system window graphics audio)

file(GLOB_RECURSE SRC_FILES src/*.cpp)
add_executable(ChessToolkit ${SRC_FILES})
target_link_libraries(ChessToolkit sfml-system sfml-window sfml-graphics sfml-audio)
target_include_directories(ChessToolkit PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)