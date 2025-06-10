//
// Created by louis on 10/06/25.
//
#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_all.hpp>

#include "AudioEngine.h"
#include "SimpleDSPProcessor.h"
#include "SinGenerator.h"

TEST_CASE("Process_Sin_w_Offset") {
    AudioEngine<float> engine;

    float ampl = 2.f;
    float freq = 440.f;
    size_t nSamples = 1e3;
    auto sinGen = std::make_shared<SinGenerator<float>>(ampl, freq, nSamples);

    auto processor = std::make_shared<SimpleDSPProcessor<float>>();

    std::vector<float> res(nSamples);
    engine.setSource(sinGen);
    engine.addProcessor(processor);
    engine.processNextBlock(res.data());

    REQUIRE(res.size() == nSamples);
    REQUIRE(res[0] == 1.f);

    // all test values from sin test just + 1
    REQUIRE(res[1] == Catch::Approx(0.125296652 + 1.f));
    REQUIRE(res[28] == Catch::Approx(1.96605396270751953 + 1.f));
    REQUIRE(res[75] == Catch::Approx(-1.9998858 + 1.f));
}
