cmake_minimum_required(VERSION 3.10)
project(complex_project)

set(CMAKE_CXX_STANDARD 17)

file(GLOB SOURCES "*.cpp")

if(SOURCES)
    add_executable(code ${SOURCES})
else()
    # If no cpp files, maybe the OJ will provide one later, or we just create a dummy one
    # But wait, if the OJ provides main.cpp, it will be in the directory when cmake is run.
    # So GLOB will find it.
    # Just in case, let's add a dummy main.cpp if SOURCES is empty.
    # Actually, if SOURCES is empty, cmake will fail.
    # Let's just use GLOB.
    add_executable(code ${SOURCES})
endif()