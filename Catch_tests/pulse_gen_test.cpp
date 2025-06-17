//
// Created by louis on 18/06/25.
//

#include <vector>
#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_all.hpp>
#include "PulseGenerator.h"
#include "SupportedFormats.h"

TEST_CASE("Test_Pulse_Float_Reset") {
    auto cut = PulseGenerator<float, BUFFERSIZE_256>();
    std::array<float, BUFFERSIZE_256> res{};

    int run = 0;
    while (run < 1)
    {
        cut.getSamples(res);

        REQUIRE( res.size() == BUFFERSIZE_256);

        for (int i = 0; i < res.size(); i++)
        {
            REQUIRE(std::isfinite(res[i]));
            if (i == 0) {
                REQUIRE( res[i] == 1);

            }
            else {
                REQUIRE( res[i] == 0);
            }
        }

        cut.getSamples(res);

        REQUIRE( res.size() == BUFFERSIZE_256);
        for (float x : res)
        {
            REQUIRE(std::isfinite(x));
            REQUIRE( x == 0.f);
        }

        cut.resetTrigger();
        run++;
    }
}


TEST_CASE("Test_Pulse_Float_Stereo") {
    auto cut = PulseGenerator<float, BUFFERSIZE_256>();
    std::array<float, BUFFERSIZE_256> resR{};
    std::array<float, BUFFERSIZE_256> resL{};

    cut.getSamples(resR, resL);

    REQUIRE( resR.size() == BUFFERSIZE_256);
    REQUIRE( resL.size() == BUFFERSIZE_256);

    for (int i = 0; i < resR.size(); i++)
    {
        REQUIRE(std::isfinite(resR[i]));
        REQUIRE(std::isfinite(resL[i]));

        if (i == 0) {
            REQUIRE( resR[i] == 1);
            REQUIRE( resL[i] == 1);

        }
        else {
            REQUIRE( resR[i] == 0);
            REQUIRE( resL[i] == 0);
        }
    }

    cut.getSamples(resR, resL);

    REQUIRE( resR.size() == BUFFERSIZE_256);
    REQUIRE( resL.size() == BUFFERSIZE_256);

    for (int i = 0; i < resR.size(); i++)
    {
        REQUIRE(std::isfinite(resR[i]));
        REQUIRE(std::isfinite(resL[i]));

        REQUIRE( resR[i] == 0.f);
        REQUIRE( resL[i] == 0.f);

    }
}

TEST_CASE("Test_Pulse_uint32_Reset") {
    auto cut = PulseGenerator<uint32_t, BUFFERSIZE_256>();
    std::array<uint32_t, BUFFERSIZE_256> res{};

    int run = 0;
    while (run < 1)
    {
        cut.getSamples(res);

        REQUIRE( res.size() == BUFFERSIZE_256);

        for (int i = 0; i < res.size(); i++) {
            if (i == 0) {
                REQUIRE( res[i] == 1);
            }
            else {
                REQUIRE( res[i] == 0);
            }
        }

        cut.getSamples(res);

        REQUIRE( res.size() == BUFFERSIZE_256);
        for (float x : res) {
            REQUIRE( x == 0);
        }

        cut.resetTrigger();
        run++;
    }
}
