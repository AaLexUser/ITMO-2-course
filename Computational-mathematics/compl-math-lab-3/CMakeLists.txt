cmake_minimum_required(VERSION 3.24)
project(ComplMath3)

set(CMAKE_CXX_STANDARD 23)

# Add the src directory and all its subdirectories to the list of source directories
file(GLOB_RECURSE SOURCES "src/*.c" "src/*.cpp" "src/*.cxx")

# Create the executable from the sources
add_executable(${PROJECT_NAME} ${SOURCES})

