//
// Created by louis on 11/06/25.
//
#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_all.hpp>

#include "AudioEngine.h"
#include "SinGenerator.h"
#include "SimplePlot.h"


TEST_CASE("Simple_Plot") {
    AudioEngine<float> engine;

    float ampl = 2.f;
    float freq = 440.f;
    size_t nSamples = 1e3;
    auto sinGen = std::make_shared<SinGenerator<float>>(ampl, freq, nSamples);
    auto plot = std::make_shared<SimplePlot<float>>(nSamples);

    std::vector<float> res(nSamples);
    engine.setSource(sinGen);
    engine.setSink(plot);
    engine.processNextBlock(res.data());
    REQUIRE(res.size() == nSamples);
}