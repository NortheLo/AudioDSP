//
// Created by louis on 09/06/25.
//

#pragma once

#include "vector"
#include "memory"

#include "IDSPProcessor.h"
#include "IAudioSource.h"

template<typename SampleType>
class AudioEngine {
public:
    void setSource(std::shared_ptr<IAudioSource<SampleType>> source) {
        source_ = source;
    }

    void addProcessor(std::shared_ptr<IDSPProcessor<SampleType>> processor) {
        processors_.push_back(processor);
    }

    void processNextBlock(SampleType* outputBuffer);


private:
    std::shared_ptr<IAudioSource<SampleType>> source_;
    std::vector<std::shared_ptr<IDSPProcessor<SampleType>>> processors_;
    std::vector<SampleType> tempBuffer_;
};