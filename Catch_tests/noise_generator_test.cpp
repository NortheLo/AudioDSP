//
// Created by louis on 08/06/25.
//
#include <vector>
#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_all.hpp>
#include "NoiseGenerator.h"

TEST_CASE("Test_Samples") {
    size_t nSamples = 1000;
    float ref_mean = 0.f;
    float stddev = 0.5f;
    NoiseGenerator<float> cut = NoiseGenerator<float>(nSamples, ref_mean, stddev);
    std::vector<float> res = cut.getSamples();

    REQUIRE(res.size() == 1000);

    double sum = 0.0;
    double sum_sq = 0.0;
    for (float x : res) {
        REQUIRE(std::isfinite(x));  // No NaNs or infinities
        sum += x;
        sum_sq += x * x;
    }

    double mean = sum / nSamples;
    double variance = (sum_sq / nSamples) - (mean * mean);
    double computed_stddev = std::sqrt(variance);

    REQUIRE(mean < 0.2);  // Mean should be ~0
    REQUIRE(mean > -0.2);  // Mean should be ~0

    REQUIRE(computed_stddev > 0.45);  // Stddev within tolerance
    REQUIRE(computed_stddev < 0.55);
}

TEST_CASE("Add_AWGN_to_Signal") {
    size_t nSamples = 1000;
    float ref_mean = 0.f;
    float stddev = 0.5f;
    NoiseGenerator<float> cut = NoiseGenerator<float>(nSamples, ref_mean, stddev);

    std::vector<float> signal(nSamples, 1.f);
    std::vector<float> res = cut.addNoise(signal);

    REQUIRE(res.size() == 1000);

    double sum = 0.0;
    double sum_sq = 0.0;
    for (float x : res) {
        REQUIRE(std::isfinite(x));  // No NaNs or infinities
        REQUIRE(x != 1.f);
        sum += x;
        sum_sq += x * x;
    }

    double mean = sum / nSamples;
    double variance = (sum_sq / nSamples) - (mean * mean);
    double computed_stddev = std::sqrt(variance);

    REQUIRE(mean < 1.2);  // Mean should be ~0
    REQUIRE(mean > 0.8);  // Mean should be ~0

    REQUIRE(computed_stddev > 0.45);  // Stddev within tolerance
    REQUIRE(computed_stddev < 0.55);
}
