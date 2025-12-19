cmake_minimum_required(VERSION 3.16)
project(TutC)

set(CMAKE_CXX_STANDARD 17)

# SDL2 Pfad
set(SDL2_PATH "C:/SDL2-2.32.6/x86_64-w64-mingw32")

set(SDL2_INCLUDE_DIR C:/SDL2-2.32.6/x86_64-w64-mingw32/include)
set(SDL2_LIBRARY C:/SDL2-2.32.6/x86_64-w64-mingw32/lib/x64)

include_directories(${SDL2_INCLUDE_DIR})

add_executable(TutC C/20/Aufgabe/demo0.c)

target_link_libraries(TutC ${SDL2_LIBRARY})
