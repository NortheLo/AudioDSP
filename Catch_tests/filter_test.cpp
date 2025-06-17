//
// Created by louis on 18/06/25.
//

#include <iostream>
#include <vector>

#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_all.hpp>


#include "Filter.h"
#include "SupportedFormats.h"
#include "PulseGenerator.h"

// max deviation from the reference MATLAB value
constexpr float abs_dev = 1e-6;

TEST_CASE("FIR_Filter_Test") {
    auto pulse = PulseGenerator<float, BUFFERSIZE_256>();
    std::array<float, BUFFERSIZE_256> pulse_buf;
    pulse.getSamples(pulse_buf);

    std::vector<float> a = {1, 0.2};
    std::vector<float> b = {1};

    auto filter = Filter<float>(a, b);

    std::array<float, BUFFERSIZE_256> res;

    filter.process(pulse_buf.data(), res.data(), res.size());

    // ref values are from eval_wav_writer.m; index gere + 1 -> MATLAB indices start with 1
    REQUIRE( res.size() == BUFFERSIZE_256);

    REQUIRE( abs(res[0] - 1.f) < abs_dev);
    REQUIRE( abs(res[1] - (-0.2f)) < abs_dev);
    REQUIRE( abs(res[2] - 0.04) < abs_dev);
    REQUIRE( abs(res[3] - (-0.008)) < abs_dev);
    REQUIRE( abs(res[4] - 0.0016) < abs_dev);
}

TEST_CASE("IIR_Filter_Test") {
    auto pulse = PulseGenerator<float, BUFFERSIZE_256>();
    std::array<float, BUFFERSIZE_256> pulse_buf;
    pulse.getSamples(pulse_buf);

    std::vector<float> a = {2, 3};
    std::vector<float> b = {1, 0.2};

    auto filter = Filter<float>(a, b);

    std::array<float, BUFFERSIZE_256> res;

    filter.process(pulse_buf.data(), res.data(), res.size());

     // ref values are from eval_wav_writer.m; index gere + 1 -> MATLAB indices start with 1
     REQUIRE( res.size() == BUFFERSIZE_256);

     REQUIRE( abs(res[0] - 2.f) < abs_dev);
     REQUIRE( abs(res[1] - 2.6) < abs_dev);
     REQUIRE( abs(res[2] - (-0.52)) < abs_dev);
     REQUIRE( abs(res[3] - 0.104) < abs_dev);
     REQUIRE( abs(res[4] - (-0.208)) < abs_dev);
     REQUIRE( abs(res[5] - (0.00416)) < abs_dev);
}