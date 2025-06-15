//
// Created by louis on 15/06/25.
//

#pragma once

#include <vector>
#include <mutex>
#include <atomic>
#include <iostream>

#include <portaudio.h>
#include "IAudioSink.h"

template<typename SampleType>
class PortAudioOutput : public IAudioSink<SampleType> {
public:
    PortAudioOutput()
        : stream(nullptr), isRunning(false) {
        PaError err = Pa_Initialize();
        if (err != paNoError) {
            std::cerr << "PortAudio init failed: " << Pa_GetErrorText(err) << "\n";
        }
    }

    ~PortAudioOutput() override {
        stop();
        Pa_Terminate();
    }

    bool start();
    void stop();
    void update(const SampleType* data, size_t numSamples) override;

private:
    PaStream* stream;
    std::mutex mutex;
    std::mutex audioMutex;
    std::vector<SampleType> audioBuffer;
    std::atomic<bool> isRunning;

    static int paCallback(const void* /*inputBuffer*/,
                          void* outputBuffer,
                          unsigned long framesPerBuffer,
                          const PaStreamCallbackTimeInfo* /*timeInfo*/,
                          PaStreamCallbackFlags /*statusFlags*/,
                          void* userData);
};
