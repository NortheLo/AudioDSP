#include "AudioEngine.h"
#include "SinGenerator.h"
#include "SimpleDSPProcessor.h"
#include "GuiBridgeSink.h"
#include "gui.h"
#include "SimplePlot.h"
#include <SupportedFormats.h>



#include <iostream>
#include <thread>
#include <unistd.h>

int main() {
    auto engine = AudioEngine<float, BUFFERSIZE_128>::create(BufferFormat::Mono);

    auto engine_mono = dynamic_cast<AudioEngineMono<float, BUFFERSIZE_128>*>(engine.get());
    float ampl = 2.f;
    float freq = 440.f;

    auto sinGen = std::make_shared<SinGenerator<float, BUFFERSIZE_128>>(ampl, freq);
    auto proc = std::make_shared<SimpleDSPProcessor<float>>();
    auto guiBridge = std::make_shared<GuiBridgeSink<float, BUFFERSIZE_128>>();
    std::array<float, BUFFERSIZE_128> res{};
    engine_mono->setSource(sinGen);
    engine_mono->addProcessor(proc);
    engine_mono->addSink(guiBridge);



    std::thread guiThread([&](){
        auto gui = Gui<float, BUFFERSIZE_128>(guiBridge);
        auto plot = std::make_shared<SimplePlot<float>>();
        gui.addElement(plot);
        gui.loop();
    });

    /* start audio loop here */
    while (true) {
        engine_mono->processNextBlock(res.data());
    }

    guiThread.join();
    return EXIT_SUCCESS;
}
