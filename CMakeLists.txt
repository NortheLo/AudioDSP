cmake_minimum_required(VERSION 3.31)
project(AudioDSP)

set(CMAKE_CXX_STANDARD 20)

# Create a library from your core code
add_library(core STATIC
        src/add.cpp
        include/add.h
        include/SinGenerator.h
        src/SinGenerator.cpp
        include/WavReader.h
        src/WavReader.cpp
        include/WavHeader.h
        include/NoiseGenerator.h
        src/NoiseGenerator.cpp
)

# Make headers visible to anything linking to this library
target_include_directories(core PUBLIC ${CMAKE_SOURCE_DIR}/include)

# Main executable
add_executable(AudioDSP main.cpp
        include/WavReader.h
        src/WavReader.cpp
        include/WavHeader.h
        src/NoiseGenerator.cpp)
target_link_libraries(AudioDSP PRIVATE core)

# Add tests
add_subdirectory(Catch_tests)

