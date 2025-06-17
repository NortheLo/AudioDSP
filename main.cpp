#include "AudioEngine.h"
#include "SinGenerator.h"
#include "NoiseGenerator.h"
#include "PortAudioInput.h"
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

    //auto src = std::make_shared<SinGenerator<float, BUFFERSIZE_128>>(2.f, 440.f);
    //auto src = std::make_shared<NoiseGenerator<float, BUFFERSIZE_128>>();
    auto src = std::make_shared<PortAudioInput<float, BUFFERSIZE_128>>();
    auto proc = std::make_shared<SimpleDSPProcessor<float>>();
    auto guiBridge = std::make_shared<GuiBridgeSink<float, BUFFERSIZE_128>>();
    std::array<float, BUFFERSIZE_128> res{};
    engine_mono->setSource(src);
    engine_mono->addProcessor(proc);
    engine_mono->addSink(guiBridge);


    auto running = std::make_shared<std::atomic<bool>>(true);

    std::thread guiThread([&](){
        auto gui = Gui<float, BUFFERSIZE_128>(guiBridge, running);
        auto plot = std::make_shared<SimplePlot<float>>();
        gui.addElement(plot);
        gui.loop();
    });

    /* start audio loop here */
    while (*running) {
        engine_mono->processNextBlock(res.data());
    }

    guiThread.join();
    return EXIT_SUCCESS;
}
