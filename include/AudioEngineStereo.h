//
// Created by louis on 15/06/25.
//

#pragma once

#include "IAudioEngine.h"

template<typename SampleType, size_t BufferSize>
class AudioEngineStereo : public IAudioEngine<SampleType, BufferSize> {
public:
    void processNextBlock(SampleType* outputBufferR, SampleType* outputBufferL);

private:
    std::array<SampleType, BufferSize> frontBufferR;
    std::array<SampleType, BufferSize> backBufferR;
    std::array<SampleType, BufferSize> frontBufferL;
    std::array<SampleType, BufferSize> backBufferL;
};
