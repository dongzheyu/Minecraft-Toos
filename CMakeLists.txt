cmake_minimum_required(VERSION 4.0.2)
project(Minecraft-Toos)

set(CMAKE_CXX_STANDARD 20)

add_definitions(-DUNICODE -D_UNICODE)

set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")

set(CMAKE_EXE_LINKER_FLAGS "-static")

set(CMAKE_EXE_LINKER_FLAGS "-static")

set_source_files_properties(resources.rc PROPERTIES LANGUAGE RC)

add_executable(Minecraft-Toos main.cpp cmake-build-debug/app.rc cmake-build-debug/resource.rc
        cpp.h
)

target_link_libraries(Minecraft-Toos PRIVATE curl)

if(MINGW OR MINGW32 OR MINGW64)
    set_source_files_properties(resources.rc PROPERTIES LANGUAGE RC)
    enable_language(RC)
endif()