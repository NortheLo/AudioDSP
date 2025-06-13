//
// Created by louis on 08/06/25.
//

#pragma once

#include "IAudioSource.h"

template<typename SampleType, size_t BufferSize>
class NoiseGenerator : public IAudioSource<SampleType, BufferSize> {
public:
    NoiseGenerator(const float mean = 0.f, const float stdDev = 1.f) :
                    IAudioSource<SampleType, BufferSize>(), mean(mean), stdDev(stdDev) {};

    void getSamples(std::array<SampleType, BufferSize>& buffer) override;
    void addNoise(std::array<SampleType, BufferSize>& buffer);

private:
    float mean;
    float stdDev;
};