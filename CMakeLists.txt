cmake_minimum_required(VERSION 3.16)

project(
    MultithreadedFileProcessor
    VERSION 1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Threads REQUIRED)

add_executable(
    file_processor

    src/main.cpp

    src/processing/FileProcessor.cpp
    src/processing/SequentialProcessor.cpp
    src/processing/ParallelProcessor.cpp

    src/utils/FileUtils.cpp
)

target_include_directories(
    file_processor
    PRIVATE
    include
)

target_link_libraries(
    file_processor
    PRIVATE
    Threads::Threads
)

target_compile_options(
    file_processor
    PRIVATE
    -Wall
    -Wextra
    -Wpedantic
)