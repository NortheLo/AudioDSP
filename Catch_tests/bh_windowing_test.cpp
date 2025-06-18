//
// Created by louis on 19/06/25.
//
#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_all.hpp>


#include "BlackmanHarrisWindow.h"
#include "SupportedFormats.h"
#include "Data/bh_window_ref.h"

TEST_CASE("BH_Win_Test") {
    auto win = BlackmanHarrisWindowing<float, BUFFERSIZE_256>();
    std::array<float, BUFFERSIZE_256> buffer;
    buffer.fill(1.f);

    std::array<float, BUFFERSIZE_256> res;
    win.process(buffer.data(), res.data(), buffer.size());

    for (size_t i = 0; i < BUFFERSIZE_256; i++) {
        REQUIRE(std::isfinite(res[i]));
        REQUIRE(Catch::Approx(res[i]).margin(1e-6) == ref_window[i]);
    }
}

TEST_CASE("BH_Win_Stereo_Test") {
    auto win = BlackmanHarrisWindowing<float, BUFFERSIZE_256>();
    std::array<float, BUFFERSIZE_256> bufferR;
    bufferR.fill(1.f);

    auto bufferL = bufferR;

    std::array<float, BUFFERSIZE_256> resR;
    std::array<float, BUFFERSIZE_256> resL;
    win.process(bufferR.data(),bufferL.data(), resR.data(), resL.data(), bufferR.size());

    for (size_t i = 0; i < BUFFERSIZE_256; i++) {
        REQUIRE(std::isfinite(resR[i]));
        REQUIRE(Catch::Approx(resR[i]).margin(1e-6) == ref_window[i]);
        REQUIRE(resL[i] == resR[i]);
    }
}