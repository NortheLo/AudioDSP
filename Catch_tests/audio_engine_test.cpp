//
// Created by louis on 10/06/25.
//
#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_all.hpp>

#include "AudioEngine.h"
#include "AudioEngineMono.h"
#include "SimpleDSPProcessor.h"
#include "SinGenerator.h"
#include "SupportedFormats.h"

TEST_CASE("Process_Sin_w_Offset") {
    auto engine = AudioEngine<float, BUFFERSIZE_128>::create(BufferFormat::Mono);
    auto engine_mono = dynamic_cast<AudioEngineMono<float, BUFFERSIZE_128>*>(engine.get());
    float ampl = 2.f;
    float freq = 440.f;
    auto sinGen = std::make_shared<SinGenerator<float, BUFFERSIZE_128>>(ampl, freq);

    auto processor = std::make_shared<SimpleDSPProcessor<float>>();

    std::array<float, BUFFERSIZE_128> res{};
    engine_mono->setSource(sinGen);
    engine_mono->addProcessor(processor);
    engine_mono->processNextBlock(res.data());

    REQUIRE(res.size() == BUFFERSIZE_128);
    REQUIRE(res[0] == 1.f);

    // all test values from sin test just + 1
    REQUIRE(res[1] == Catch::Approx(0.125296652 + 1.f));
    REQUIRE(res[28] == Catch::Approx(1.96605396270751953 + 1.f));
    REQUIRE(res[75] == Catch::Approx(-1.9998858 + 1.f));
}

TEST_CASE("Process_Two_Modules") {
    auto engine = AudioEngine<float, BUFFERSIZE_128>::create(BufferFormat::Mono);
    auto engine_mono = dynamic_cast<AudioEngineMono<float, BUFFERSIZE_128>*>(engine.get());
    float ampl = 2.f;
    float freq = 440.f;
    auto sinGen = std::make_shared<SinGenerator<float, BUFFERSIZE_128>>(ampl, freq);

    auto processor = std::make_shared<SimpleDSPProcessor<float>>();
    auto secondprocessor = std::make_shared<SimpleDSPProcessor<float>>();


    std::array<float, BUFFERSIZE_128> res{};
    engine_mono->setSource(sinGen);
    engine_mono->addProcessor(processor);
    engine_mono->addProcessor(secondprocessor);
    engine_mono->processNextBlock(res.data());

    REQUIRE(res.size() == BUFFERSIZE_128);
    REQUIRE(res[0] == 2.f);

    // all test values from sin test just + 1
    REQUIRE(res[1] == Catch::Approx(2.125296652));
    REQUIRE(res[28] == Catch::Approx(3.96605396270751953));
    REQUIRE(res[75] == Catch::Approx(0.000114202499));
}


TEST_CASE("Process_wo_Processor") {
    auto engine = AudioEngine<float, BUFFERSIZE_128>::create(BufferFormat::Mono);
    auto engine_mono = dynamic_cast<AudioEngineMono<float, BUFFERSIZE_128>*>(engine.get());

    auto sinGen = std::make_shared<SinGenerator<float, BUFFERSIZE_128>>(2.f, 440.f);

    auto processor = std::make_shared<SimpleDSPProcessor<float>>();

    std::array<float, BUFFERSIZE_128> res{};
    engine_mono->setSource(sinGen);
    engine_mono->processNextBlock(res.data());

    REQUIRE(res[1] == Catch::Approx(0.125296652));
    REQUIRE(res[28] == Catch::Approx(1.96605396270751953));
    REQUIRE(res[75] == Catch::Approx(-1.9998858));

    engine_mono->addProcessor(processor);
    engine_mono->processNextBlock(res.data());


    REQUIRE(res.size() == BUFFERSIZE_128);
    REQUIRE(res[0] == 1.f);

    // all test values from sin test just + 1
    REQUIRE(res[1] == Catch::Approx(0.125296652 + 1.f));
    REQUIRE(res[28] == Catch::Approx(1.96605396270751953 + 1.f));
    REQUIRE(res[75] == Catch::Approx(-1.9998858 + 1.f));
};