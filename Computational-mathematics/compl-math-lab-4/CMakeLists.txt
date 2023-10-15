cmake_minimum_required(VERSION 3.24)
project(ComplMath4)

set(CMAKE_CXX_STANDARD 23)
# Add the src directory and all its subdirectories to the list of source directories
file(GLOB_RECURSE SOURCES "src/*.c" "src/*.cpp" "src/*.cxx")

# Create the executable from the sources
add_executable(${PROJECT_NAME} ${SOURCES})

include_directories(/usr/local/include)
find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})
find_package(PythonLibs REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} sfml-system sfml-window sfml-graphics sfml-audio sfml-network ${PYTHON_LIBRARIES})

