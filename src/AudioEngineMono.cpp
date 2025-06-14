//
// Created by louis on 15/06/25.
//
#include <algorithm>

#include "AudioEngineMono.h"
#include "SupportedFormats.h"

template<typename SampleType, size_t BufferSize>
void AudioEngineMono<SampleType, BufferSize>::processNextBlock(SampleType* outputBuffer) {
    if(!this->source_) return;

    this->source_->getSamples(frontBuffer);

    for (auto& proc : this->processors_) {
        proc->process(frontBuffer.data(), backBuffer.data(), BufferSize);
        std::swap(frontBuffer, backBuffer);
    }

    // update all sinks e.g. GUIs, plotting function etc
    for (auto& sink : this->sinks_) {
        sink->update(frontBuffer.data(), frontBuffer.size());
    }

    std::copy_n(frontBuffer.begin(), frontBuffer.size(), outputBuffer);
}

template class AudioEngineMono<float, BUFFERSIZE_64>;
template class AudioEngineMono<float, BUFFERSIZE_128>;
template class AudioEngineMono<float, BUFFERSIZE_256>;

template class AudioEngineMono<uint32_t, BUFFERSIZE_64>;
template class AudioEngineMono<uint32_t, BUFFERSIZE_128>;
template class AudioEngineMono<uint32_t, BUFFERSIZE_256>;