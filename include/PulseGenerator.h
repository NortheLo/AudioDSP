//
// Created by louis on 18/06/25.
//

#pragma once

#include "IAudioSource.h"

template<typename SampleType, size_t BufferSize>
class PulseGenerator : public IAudioSource<SampleType, BufferSize> {
    public:
        void resetTrigger() { alreadyTriggered = false; }
        void getSamples(std::array<SampleType, BufferSize>& buffer) override;
        void getSamples(std::array<SampleType, BufferSize>& bufferR,
                                std::array<SampleType, BufferSize>& bufferL) override;

    private:
        bool alreadyTriggered = false;
};