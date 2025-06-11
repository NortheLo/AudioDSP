find_package(Catch2 3 REQUIRED)

add_executable(Catch_tests_run add_test.cpp
        sin_generator_test.cpp
        wav_reader_test.cpp
        ../src/NoiseGenerator.cpp
        noise_generator_test.cpp
        ../src/AudioEngine.cpp
        ../src/SimpleDSPProcessor.cpp
        audio_engine_test.cpp
        simple_plot_test.cpp
)

target_link_libraries(Catch_tests_run PRIVATE Catch2::Catch2WithMain core)

# Add path to FakeIt headers
include_directories(${CMAKE_SOURCE_DIR}/external/FakeIt/single_header)

# Include path is already set via 'core' if needed
include(Catch)
catch_discover_tests(Catch_tests_run)

# Add Path to to Data so we can use it with relative paths
target_compile_definitions(Catch_tests_run PRIVATE
        TEST_DATA_DIR="${CMAKE_SOURCE_DIR}/Catch_tests/Data"
)
