cmake_minimum_required(VERSION 3.5)
project(qttest C CXX)
file(GLOB_RECURSE SRC_FILES ./*.cpp)
set( CMAKE_EXPORT_COMPILE_COMMANDS 1 )

# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Warnings
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
        set(CMAKE_CXX_FLAGS "-Weverything -Wno-c++98-compat -Wno-padded")
else()
        set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic -Wshadow")
endif()

# Qt deps
find_package(Qt5Core)
find_package(Qt5Network)

# Target definition
add_executable(${PROJECT_NAME} ${SRC_FILES})
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 14)

target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Network)

