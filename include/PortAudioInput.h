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
class PortAudioInputSource : public IAudioSource<SampleType, BufferSize> {
public:
    PortAudioInputSource() {
        Pa_Initialize();
        openStream();
    }

    ~PortAudioInputSource() override {
        running = false;
        if (streamThread.joinable()) streamThread.join();
        Pa_StopStream(stream);
        Pa_CloseStream(stream);
        Pa_Terminate();
    }

    void getSamples(std::array<SampleType, BufferSize>& buffer) override {
        std::unique_lock<std::mutex> lock(mutex);
        dataReady.wait(lock, [this] { return newDataAvailable; });

        buffer = internalBuffer;  // copy buffered data
        newDataAvailable = false;
    }

    void getSamples(std::array<SampleType, BufferSize>&, std::array<SampleType, BufferSize>&) override {
        // No stereo support for now
        throw std::runtime_error("Stereo input not supported in PortAudioInputSource.");
    }

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
                          void* userData) {
        auto* self = static_cast<PortAudioInputSource*>(userData);
        const SampleType* in = static_cast<const SampleType*>(input);

        {
            std::lock_guard<std::mutex> lock(self->mutex);
            std::copy(in, in + BufferSize, self->internalBuffer.begin());
            self->newDataAvailable = true;
        }

        self->dataReady.notify_one();
        return paContinue;
    }

    void openStream() {
        PaStreamParameters inputParams;
        inputParams.device = Pa_GetDefaultInputDevice();
        inputParams.channelCount = 1; // mono
        inputParams.sampleFormat = paFloat32; // use float as default
        inputParams.suggestedLatency = Pa_GetDeviceInfo(inputParams.device)->defaultLowInputLatency;
        inputParams.hostApiSpecificStreamInfo = nullptr;

        Pa_OpenStream(&stream,
                      &inputParams, nullptr,
                      this->sampleRate, BufferSize,
                      paClipOff,
                      &PortAudioInputSource::paCallback,
                      this);

        Pa_StartStream(stream);

        streamThread = std::thread([this]() {
            while (running) {
                Pa_Sleep(10);
            }
        });
    }
};
