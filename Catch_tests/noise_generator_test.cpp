//
// Created by louis on 08/06/25.
//
#include <vector>
#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_all.hpp>
#include "NoiseGenerator.h"
#include "SupportedFormats.h"

TEST_CASE("Test_Samples") {
    float ref_mean = 0.f;
    float stddev = 0.5f;
    auto cut = NoiseGenerator<float, BUFFERSIZE_256>(ref_mean, stddev);
    std::array<float, BUFFERSIZE_256> res{};
    cut.getSamples(res);

    REQUIRE(res.size() == BUFFERSIZE_256);

    double sum = 0.0;
    double sum_sq = 0.0;
    for (float x : res) {
        REQUIRE(std::isfinite(x));  // No NaNs or infinities
        sum += x;
        sum_sq += x * x;
    }

    double mean = sum / BUFFERSIZE_256;
    double variance = (sum_sq / BUFFERSIZE_256) - (mean * mean);
    double computed_stddev = std::sqrt(variance);

    REQUIRE(mean < 0.2);  // Mean should be ~0
    REQUIRE(mean > -0.2);  // Mean should be ~0

    REQUIRE(computed_stddev > 0.45);  // Stddev within tolerance
    REQUIRE(computed_stddev < 0.55);
}

TEST_CASE("Add_AWGN_to_Signal") {
    float ref_mean = 0.f;
    float stddev = 0.5f;
    auto cut = NoiseGenerator<float, BUFFERSIZE_256>(ref_mean, stddev);

    std::array<float, BUFFERSIZE_256> res{};
    res.fill(1.f);
    cut.addNoise(res);

    REQUIRE(res.size() == BUFFERSIZE_256);

    double sum = 0.0;
    double sum_sq = 0.0;
    for (float x : res) {
        REQUIRE(std::isfinite(x));  // No NaNs or infinities
        REQUIRE(x != 1.f);
        sum += x;
        sum_sq += x * x;
    }

    double mean = sum / BUFFERSIZE_256;
    double variance = (sum_sq / BUFFERSIZE_256) - (mean * mean);
    double computed_stddev = std::sqrt(variance);

    REQUIRE(mean < 1.2);
    REQUIRE(mean > 0.8);

    REQUIRE(computed_stddev > 0.45);  // Stddev within tolerance
    REQUIRE(computed_stddev < 0.55);
}
