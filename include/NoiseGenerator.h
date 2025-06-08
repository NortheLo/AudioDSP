//
// Created by louis on 08/06/25.
//

#pragma once

#include "IAudioSource.h"

template<typename SampleType>

class NoiseGenerator : public IAudioSource<SampleType> {
public:
    NoiseGenerator(const size_t nSamples, const float mean = 0.f, const float stdDev = 1.f) :
                    IAudioSource<SampleType>(nSamples), mean(mean), stdDev(stdDev) {};

    std::vector<SampleType> getSamples() override;
    std::vector<SampleType> addNoise(std::vector<SampleType> signal);

private:
    float mean;
    float stdDev;
};