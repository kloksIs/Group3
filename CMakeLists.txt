cmake_minimum_required(VERSION 3.10)
project(InfectionSim)

set(CMAKE_CXX_STANDARD 17)

find_package(nlohmann_json REQUIRED)

include_directories(include)

file(GLOB_RECURSE SOURCES src/*.cpp)
add_definitions(-DPROJECT_SOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}")
add_executable(InfectionSim ${SOURCES})


target_link_libraries(InfectionSim nlohmann_json::nlohmann_json)