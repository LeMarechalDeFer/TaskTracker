cmake_minimum_required(VERSION 3.31)

project(task LANGUAGES CXX)

find_package(fmt CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(CLI11 CONFIG REQUIRED)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)
file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS include/*.hpp)
add_executable(task ${SOURCES})


target_include_directories(task PRIVATE include)

target_link_libraries(task PRIVATE 
    nlohmann_json::nlohmann_json
    fmt::fmt
    CLI11::CLI11
    )

target_compile_features(task PRIVATE cxx_std_20)
