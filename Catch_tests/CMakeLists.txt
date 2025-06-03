find_package(Catch2 3 REQUIRED)

add_executable(Catch_tests_run add_test.cpp
        sin_generator_test.cpp
        wav_reader_test.cpp
)

target_link_libraries(Catch_tests_run PRIVATE Catch2::Catch2WithMain core)

# Include path is already set via 'core' if needed
include(Catch)
catch_discover_tests(Catch_tests_run)
