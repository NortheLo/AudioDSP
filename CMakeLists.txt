cmake_minimum_required(VERSION 3.31)
project(AudioDSP)

include(cmake/imgui.cmake)
include(cmake/implot.cmake)

add_subdirectory(external/portaudio)

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
        include/AudioEngine.h
        include/IDSPProcessor.h
        include/IAudioSink.h
        include/IAudioEngine.h
        src/AudioEngineMono.cpp
        include/AudioEngineMono.h
        src/AudioEngineStereo.cpp
        include/AudioEngineStereo.h
        include/PortAudioInput.h
)

# Make headers visible to anything linking to this library
target_include_directories(core PUBLIC ${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/external/imgui ${CMAKE_SOURCE_DIR}/external/implot, ${CMAKE_SOURCE_DIR}/external/portaudio)

# Main executable
add_executable(AudioDSP main.cpp
                        src/WavReader.cpp
                        src/NoiseGenerator.cpp
        src/SimpleDSPProcessor.cpp)

target_link_libraries(AudioDSP PRIVATE core imgui implot glfw OpenGL::GL portaudio)

# Add tests
add_subdirectory(Catch_tests)