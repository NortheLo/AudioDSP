//
// Created by louis on 08/06/25.
//
#include <cstdint>
#include <random>
#include "NoiseGenerator.h"

template<typename SampleType>
std::vector<SampleType> NoiseGenerator<SampleType>::getSamples() {
    std::vector<SampleType> noise(this->bufferSize);

    std::default_random_engine engine(std::random_device{}());
    std::normal_distribution<SampleType> dist(mean, stdDev);

    for (auto& sample : noise) {
        sample = dist(engine);
    }
    return noise;
}

template class NoiseGenerator<float>;
template class NoiseGenerator<double>;