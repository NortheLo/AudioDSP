//
// Created by louis on 01/06/25.
//

#pragma once

#include "IAudioSource.h"

template<typename SampleType>

class SinGenerator : public IAudioSource<SampleType> {
public:
    SinGenerator(const SampleType amplitude, const float frequency, const size_t nSamples) :
                _amplitude(amplitude), _frequency(frequency), IAudioSource<SampleType>(nSamples) { };

    std::vector<SampleType> getSamples() override;

private:
    SampleType _amplitude;
    float _frequency;
};
