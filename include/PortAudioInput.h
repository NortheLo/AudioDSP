//
// Created by louis on 15/06/25.
//

#pragma once

#include <array>
#include <atomic>
#include <thread>
#include <mutex>
#include <condition_variable>

#include <portaudio.h>

#include "IAudioSource.h"

template<typename SampleType, size_t BufferSize>
class PortAudioInput: public IAudioSource<SampleType, BufferSize> {
public:
    PortAudioInput() {
        Pa_Initialize();
        openStream();
    }

    ~PortAudioInput() override {
        running = false;
        if (streamThread.joinable()) streamThread.join();
        Pa_StopStream(stream);
        Pa_CloseStream(stream);
        Pa_Terminate();
    }

    void getSamples(std::array<SampleType, BufferSize>& buffer) override;
    void getSamples(std::array<SampleType, BufferSize>&, std::array<SampleType, BufferSize>&) override;

private:
    PaStream* stream = nullptr;
    std::array<SampleType, BufferSize> internalBuffer;
    std::mutex mutex;
    std::condition_variable dataReady;
    std::atomic<bool> running = true;
    std::atomic<bool> newDataAvailable = false;
    std::thread streamThread;

    static int paCallback(const void* input, void*,
                          unsigned long framesPerBuffer,
                          const PaStreamCallbackTimeInfo*,
                          PaStreamCallbackFlags,
                          void* userData);

    void openStream();
};
