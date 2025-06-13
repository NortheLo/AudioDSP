//
// Created by louis on 02/06/25.
//
#include <filesystem>
#include <vector>
#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_all.hpp>
#include <catch/fakeit.hpp>

#include "WavReader.h"
#include "SupportedFormats.h"

/* This test contains a chirp from audacity */
TEST_CASE("Read_WAV_Samples") {
    std::filesystem::path pathToWav = std::filesystem::path(TEST_DATA_DIR) / "test_f32_chirp.wav";
    auto rdr = WavReader<float, BUFFERSIZE_256>(pathToWav);

    std::array<float, BUFFERSIZE_256> samples{};
    rdr.getSamples(samples);
    REQUIRE(samples.size() == BUFFERSIZE_256);

    REQUIRE(samples[0] == 0);
    REQUIRE(samples[1] == 0.0626482964f);
    REQUIRE(samples[100] == Catch::Approx(-0.01393619459122419));

    // go to last sample
    unsigned int rounds = (2000000 - 1) / BUFFERSIZE_256;
    unsigned int sampleIndex = (2000000 - 1) % BUFFERSIZE_256;
    for (unsigned int i = 0; i < rounds; i++) {
        rdr.getSamples(samples);
    }
    REQUIRE(samples[sampleIndex] == Catch::Approx(0.09989974647760391));
    REQUIRE(samples[sampleIndex + 1] == 0.f);
    REQUIRE(samples[255] == 0.f);
}

/* This file reads a 440Hz sin from MATLAB */
TEST_CASE("Read_WAV_Samples2") {
    std::filesystem::path pathToWav = std::filesystem::path(TEST_DATA_DIR) / "test_f32_sin_440Hz.wav";
    auto rdr = WavReader<float, BUFFERSIZE_256>(pathToWav);

    std::array<float, BUFFERSIZE_256> samples{};
    rdr.getSamples(samples);
    REQUIRE(samples.size() == BUFFERSIZE_256);
    REQUIRE(samples[0] == 0.f);
    REQUIRE(samples[1] == 0.06264832615852356);
    REQUIRE(samples[2] == 0.12505053f);
    REQUIRE(samples[175] == -0.9996891617774963);


    unsigned int rounds = (1000 - 1) / BUFFERSIZE_256;
    unsigned int sampleIndex = (1000 - 1) % BUFFERSIZE_256;
    for (unsigned int i = 0; i < rounds; i++) {
        rdr.getSamples(samples);
    }

    REQUIRE(samples[sampleIndex] == Catch::Approx(-0.2037289291620255));
    REQUIRE(samples[sampleIndex + 1] == 0.f);
    REQUIRE(samples[255] == 0.f);
}