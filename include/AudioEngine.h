//
// Created by louis on 09/06/25.
//

#pragma once

#include "vector"
#include "memory"

#include "IDSPProcessor.h"
#include "IAudioSource.h"
#include "IAudioSink.h"

template<typename SampleType, size_t BufferSize>
class AudioEngine {
public:
    void setSource(std::shared_ptr<IAudioSource<SampleType, BufferSize>> source) {
        source_ = source;
    }

    void addProcessor(std::shared_ptr<IDSPProcessor<SampleType>> processor) {
        processors_.push_back(processor);
    }

    void setSink(std::shared_ptr<IAudioSink<SampleType>> sink) {
        sink_.push_back(sink);
    }

    void processNextBlock(SampleType* outputBuffer);


private:
    std::shared_ptr<IAudioSource<SampleType, BufferSize>> source_;
    std::vector<std::shared_ptr<IDSPProcessor<SampleType>>> processors_;
    std::vector<std::shared_ptr<IAudioSink<SampleType>>> sink_;

    std::array<SampleType, BufferSize> frontBuffer;
    std::array<SampleType, BufferSize> backBuffer;
};