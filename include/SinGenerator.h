//
// Created by louis on 01/06/25.
//

#pragma once

#include "IAudioSource.h"

template<typename SampleType, size_t BufferSize>

class SinGenerator : public IAudioSource<SampleType, BufferSize> {
public:
    SinGenerator(const SampleType amplitude, const float frequency) :
                _amplitude(amplitude), _frequency(frequency), IAudioSource<SampleType, BufferSize>() { };

    void getSamples(std::array<SampleType, BufferSize>& buffer) override;

private:
    SampleType _amplitude;
    float _frequency;
};
