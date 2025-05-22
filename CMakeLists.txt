cmake_minimum_required(VERSION 4.0.2)
project(Minecraft-Toos)

set(CMAKE_CXX_STANDARD 20)

add_definitions(-DUNICODE -D_UNICODE)

set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")

set(CMAKE_EXE_LINKER_FLAGS "-static")

set(CMAKE_EXE_LINKER_FLAGS "-static")

add_executable(Minecraft-Toos main.cpp cmake-build-debug/app.rc)