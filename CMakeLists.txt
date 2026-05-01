cmake_minimum_required(VERSION 3.10)
project(InfectionSim)

set(CMAKE_CXX_STANDARD 17)

find_package(nlohmann_json REQUIRED)

include_directories(include)

add_executable(InfectionSim src/main.cpp)

target_link_libraries(InfectionSim nlohmann_json::nlohmann_json)