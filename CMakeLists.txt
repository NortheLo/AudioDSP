cmake_minimum_required(VERSION 3.31)
project(AudioDSP)

include(cmake/imgui.cmake)
include(cmake/implot.cmake)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

set(CMAKE_CXX_STANDARD 20)

# Create a library from your core code
add_library(core STATIC
        include/SinGenerator.h
        src/SinGenerator.cpp
        include/WavReader.h
        src/WavReader.cpp
        include/WavHeader.h
        include/NoiseGenerator.h
        src/NoiseGenerator.cpp
        src/AudioEngine.cpp
        include/AudioEngine.h
        include/IDSPProcessor.h
        include/IAudioSink.h
)

# Make headers visible to anything linking to this library
target_include_directories(core PUBLIC ${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/external/imgui ${CMAKE_SOURCE_DIR}/external/implot)

# Main executable
add_executable(AudioDSP main.cpp
                        src/WavReader.cpp
                        src/NoiseGenerator.cpp
                        src/AudioEngine.cpp
                        src/SimpleDSPProcessor.cpp)

target_link_libraries(AudioDSP PRIVATE core  imgui implot glfw OpenGL::GL)

# Add tests
add_subdirectory(Catch_tests)