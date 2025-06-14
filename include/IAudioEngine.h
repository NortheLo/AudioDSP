//
// Created by louis on 15/06/25.
//

#pragma once

#include "memory"
#include "vector"

#include "IDSPProcessor.h"
#include "IAudioSource.h"
#include "IAudioSink.h"

template<typename SampleType, size_t BufferSize>
class IAudioEngine {
public:
    virtual ~IAudioEngine() = default;

    void setSource(std::shared_ptr<IAudioSource<SampleType, BufferSize>> source) {
        source_ = source;
    }

    void addProcessor(std::shared_ptr<IDSPProcessor<SampleType>> processor) {
        processors_.push_back(processor);
    }

    void addSink(std::shared_ptr<IAudioSink<SampleType>> sink) {
        sinks_.push_back(sink);
    }

protected:
    std::shared_ptr<IAudioSource<SampleType, BufferSize>> source_;
    std::vector<std::shared_ptr<IDSPProcessor<SampleType>>> processors_;
    std::vector<std::shared_ptr<IAudioSink<SampleType>>> sinks_;
};
