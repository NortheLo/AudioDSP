//
// Created by louis on 15/06/25.
//

#include "portaudio.h"

#include "SupportedFormats.h"
#include "PortAudioInput.h"

template<typename SampleType, size_t BufferSize>
void PortAudioInput<SampleType, BufferSize>::getSamples(std::array<SampleType, BufferSize>& buffer) override {
    std::unique_lock<std::mutex> lock(mutex);
    dataReady.wait(lock, [this] { return newDataAvailable; });

    buffer = internalBuffer;  // copy buffered data
    newDataAvailable = false;
}

template<typename SampleType, size_t BufferSize>
void PortAudioInput<SampleType, BufferSize>::getSamples(std::array<SampleType, BufferSize>&, std::array<SampleType, BufferSize>&) override {
    throw std::runtime_error("Stereo input not supported in PortAudioInput.");
}

template<typename SampleType, size_t BufferSize>
int PortAudioInput<SampleType, BufferSize>::paCallback(const void* input, void*,
                                                              unsigned long framesPerBuffer,
                                                              const PaStreamCallbackTimeInfo*,
                                                              PaStreamCallbackFlags,
                                                              void* userData) {
    auto* self = static_cast<PortAudioInput*>(userData);
    const SampleType* in = static_cast<const SampleType*>(input);

    {
        std::lock_guard<std::mutex> lock(self->mutex);
        std::copy(in, in + BufferSize, self->internalBuffer.begin());
        self->newDataAvailable = true;
    }

    self->dataReady.notify_one();
    return paContinue;
}

template<typename SampleType, size_t BufferSize>
void PortAudioInput<SampleType, BufferSize>::openStream() {
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
                      &PortAudioInput::paCallback,
                      this);

        Pa_StartStream(stream);

        streamThread = std::thread([this]() {
            while (running) {
                Pa_Sleep(10);
            }
        });
}

template class PortAudioInput<float, BUFFERSIZE_64>;
template class PortAudioInput<float, BUFFERSIZE_128>;
template class PortAudioInput<float, BUFFERSIZE_256>;