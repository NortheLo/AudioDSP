//
// Created by louis on 08/06/25.
//
#include <cstdint>
#include <random>
#include "NoiseGenerator.h"

#include <iostream>

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

template <typename SampleType>
std::vector<SampleType> NoiseGenerator<SampleType>::addNoise(std::vector<SampleType> signal) {
    std::vector<SampleType> noise = getSamples();

    if (signal.size() != this->bufferSize) {
        std::cerr << "Mismatch of signal and noise vectors" << std::endl;
        return signal;
    }

    size_t idx = 0;
    for (auto& sample : noise) {
        signal[idx++] += sample;
    }
    return signal;
}


template class NoiseGenerator<float>;
template class NoiseGenerator<double>;