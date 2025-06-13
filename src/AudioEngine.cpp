//
// Created by louis on 09/06/25.
//
#include <iostream>
#include <algorithm>

#include "AudioEngine.h"
#include "SupportedFormats.h"

template<typename SampleType, size_t BufferSize>
void AudioEngine<SampleType, BufferSize>::processNextBlock(SampleType* outputBuffer) {
    if(!source_) return;

     source_->getSamples(frontBuffer);

    for (auto& proc : processors_) {
        proc->process(frontBuffer.data(), backBuffer.data(), BufferSize);
        std::swap(frontBuffer, backBuffer);
    }

    // update all sinks e.g. GUIs, plotting function etc
    for (auto& sink : sink_) {
        sink->update(frontBuffer.data(), frontBuffer.size());
    }

    std::copy_n(frontBuffer.begin(), frontBuffer.size(), outputBuffer);
}

template class AudioEngine<float, BUFFERSIZE_64>;
template class AudioEngine<float, BUFFERSIZE_128>;
template class AudioEngine<float, BUFFERSIZE_256>;

template class AudioEngine<uint32_t, BUFFERSIZE_64>;
template class AudioEngine<uint32_t, BUFFERSIZE_128>;
template class AudioEngine<uint32_t, BUFFERSIZE_256>;