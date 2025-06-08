//
// Created by louis on 02/06/25.
//
#include <filesystem>
#include <vector>
#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_all.hpp>
#include <catch/fakeit.hpp>

#include "WavReader.h"

TEST_CASE("Test_SetFileSize") {
    /*
     * We have to find a Mocking Framework (e.g. FakeIT)
     */
}

TEST_CASE("Number_of_Samples") {
    std::filesystem::path pathToWav = std::filesystem::path(TEST_DATA_DIR) / "test_f32_chirp.wav";

    class Test_WavReader : public WavReader<float> {
    public:
        Test_WavReader(std::filesystem::path wavPath) : WavReader<float>(wavPath) {}
        int getNumberSamplesW(unsigned int fileSize) {
            return getNumberSamples(fileSize);
        }
    };

    unsigned int fileSize = 100;
    int expectedNumSamples = (fileSize - 44) / sizeof(float);

    Test_WavReader rdr(pathToWav);
    int res = rdr.getNumberSamplesW(fileSize);
    REQUIRE(res == expectedNumSamples);
}

TEST_CASE("Read_WAV_Samples") {
    std::filesystem::path pathToWav = std::filesystem::path(TEST_DATA_DIR) / "test_f32_chirp.wav";
    auto rdr = WavReader<float>(pathToWav);

    std::vector<float> samples = rdr.getSamples();
    REQUIRE(samples.size() == 2000000);

    REQUIRE(samples[0] == 0);
    REQUIRE(samples[1] == 0.0626482964);
}