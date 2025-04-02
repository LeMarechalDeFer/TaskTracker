cmake_minimum_required(VERSION 3.31)

project(TaskTrackerCLI LANGUAGES CXX)

find_package(fmt CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(CLI11 CONFIG REQUIRED)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)
file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS include/*.hpp)
add_executable(TaskTrackerCLI ${SOURCES})


target_include_directories(TaskTrackerCLI PRIVATE include)

target_link_libraries(TaskTrackerCLI PRIVATE 
    nlohmann_json::nlohmann_json
    fmt::fmt
    CLI11::CLI11
    )

target_compile_features(TaskTrackerCLI PRIVATE cxx_std_20)
