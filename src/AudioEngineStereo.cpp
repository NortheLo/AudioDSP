//
// Created by louis on 15/06/25.
//
#include <algorithm>

#include "AudioEngineStereo.h"
#include "SupportedFormats.h"

template<typename SampleType, size_t BufferSize>
void AudioEngineStereo<SampleType, BufferSize>::processNextBlock(SampleType* outputBufferR, SampleType* outputBufferL) {
    if(!this->source_) return;

    this->source_->getSamples(frontBufferR, frontBufferL);

    for (auto& proc : this->processors_) {
        proc->process(frontBufferR.data(), frontBufferL.data(), backBufferR.data(),
                    backBufferL.data(), BufferSize);

        std::swap(frontBufferR, backBufferR);
        std::swap(frontBufferL, backBufferL);

    }

    // for now only plot the right channel
    for (auto& sink : this->sinks_) {
        sink->update(frontBufferR.data(), frontBufferR.size());
    }

    std::copy_n(frontBufferR.begin(), frontBufferR.size(), outputBufferR);
    std::copy_n(frontBufferL.begin(), frontBufferL.size(), outputBufferL);
}

template class AudioEngineStereo<float, BUFFERSIZE_64>;
template class AudioEngineStereo<float, BUFFERSIZE_128>;
template class AudioEngineStereo<float, BUFFERSIZE_256>;

template class AudioEngineStereo<uint32_t, BUFFERSIZE_64>;
template class AudioEngineStereo<uint32_t, BUFFERSIZE_128>;
template class AudioEngineStereo<uint32_t, BUFFERSIZE_256>;