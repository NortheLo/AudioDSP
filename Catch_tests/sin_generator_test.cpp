//
// Created by louis on 01/06/25.
//
#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_all.hpp>

#include "SinGenerator.h"
#include "SupportedFormats.h"

TEST_CASE("Float_Sin") {
    float ampl = 2.f;
    float freq = 440.f;
    auto sinGen = SinGenerator<float, BUFFERSIZE_128>(ampl, freq);
    std::array<float, BUFFERSIZE_128> res{};
    sinGen.getSamples(res);

    REQUIRE(res.size() == BUFFERSIZE_128);
    REQUIRE(res[0] == 0.f);
    REQUIRE(res[1] == Catch::Approx(0.125296652));
    REQUIRE(res[28] == Catch::Approx(1.96605396270751953));
    REQUIRE(res[75] == Catch::Approx(-1.9998858));
}

TEST_CASE("Get_Sample_Rate") {
    auto sinGen = SinGenerator<float, BUFFERSIZE_128>(1.f, 44.f);

    unsigned int fs = sinGen.getSampleRate();
    REQUIRE(fs == 44100);
}

TEST_CASE("Set_Sample_Rate") {
    auto sinGen = SinGenerator<float, BUFFERSIZE_128>(1.f, 44.f);

    unsigned int new_fs = 48e3;
    sinGen.setSampleRate(new_fs);
    unsigned int fs = sinGen.getSampleRate();
    REQUIRE(fs == 48000);
}