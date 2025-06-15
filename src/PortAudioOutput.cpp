//
// Created by louis on 15/06/25.
//
#include "PortAudioOutput.h"

template<typename SampleType>
bool PortAudioOutput<SampleType>::start() {
    std::lock_guard<std::mutex> lock(mutex);

    PaStreamParameters outputParams{};
    outputParams.device = Pa_GetDefaultOutputDevice();
    if (outputParams.device == paNoDevice) {
        std::cerr << "No default output device.\n";
        return false;
    }

    outputParams.channelCount = 1;
    outputParams.sampleFormat = paFloat32;
    outputParams.suggestedLatency =
        Pa_GetDeviceInfo(outputParams.device)->defaultLowOutputLatency;
    outputParams.hostApiSpecificStreamInfo = nullptr;

    PaError err = Pa_OpenStream(
        &stream,
        nullptr, // no input
        &outputParams,
        44100, // sample rate
        paFramesPerBufferUnspecified,
        paNoFlag,
        &PortAudioOutput::paCallback,
        this
    );
    if (err != paNoError) {
        std::cerr << "Failed to open output stream: " << Pa_GetErrorText(err) << "\n";
        return false;
    }

    err = Pa_StartStream(stream);
    if (err != paNoError) {
        std::cerr << "Failed to start stream: " << Pa_GetErrorText(err) << "\n";
        return false;
    }

    isRunning.store(true);
    return true;
}

template<typename SampleType>
void PortAudioOutput<SampleType>::stop() {
    std::lock_guard<std::mutex> lock(mutex);
    if (stream) {
        Pa_StopStream(stream);
        Pa_CloseStream(stream);
        stream = nullptr;
    }
    isRunning.store(false);
}

template<typename SampleType>
void PortAudioOutput<SampleType>::update(const SampleType* data, size_t numSamples) {
    std::lock_guard<std::mutex> lock(audioMutex);
    audioBuffer.assign(data, data + numSamples);
}

template<typename SampleType>
int PortAudioOutput<SampleType>::paCallback(const void* /*inputBuffer*/,
                          void* outputBuffer,
                          unsigned long framesPerBuffer,
                          const PaStreamCallbackTimeInfo* /*timeInfo*/,
                          PaStreamCallbackFlags /*statusFlags*/,
                          void* userData) {
    auto* self = static_cast<PortAudioOutput*>(userData);
    auto* out = static_cast<SampleType*>(outputBuffer);

    std::lock_guard<std::mutex> lock(self->audioMutex);

    if (self->audioBuffer.empty()) {
        std::memset(out, 0, framesPerBuffer * sizeof(SampleType));
    } else {
        size_t copyCount = std::min<size_t>(framesPerBuffer, self->audioBuffer.size());
        std::memcpy(out, self->audioBuffer.data(), copyCount * sizeof(SampleType));

        if (copyCount < framesPerBuffer) {
            std::memset(out + copyCount, 0, (framesPerBuffer - copyCount) * sizeof(SampleType));
        }

        // Clear buffer after use
        self->audioBuffer.clear();
    }

    return paContinue;
}

template class PortAudioOutput<float>;
template class PortAudioOutput<float>;
template class PortAudioOutput<float>;