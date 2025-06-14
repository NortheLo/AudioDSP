//
// Created by louis on 15/06/25.
//

#pragma once
#include "IAudioEngine.h"

template<typename SampleType, size_t BufferSize>
class AudioEngineMono : public IAudioEngine<SampleType, BufferSize> {
public:
    void processNextBlock(SampleType* outputBuffer);

private:
    std::array<SampleType, BufferSize> frontBuffer;
    std::array<SampleType, BufferSize> backBuffer;

};
