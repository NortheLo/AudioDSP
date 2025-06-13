//
// Created by louis on 08/06/25.
//
#include <iostream>
#include <random>

#include "NoiseGenerator.h"
#include "SupportedFormats.h"

template<typename SampleType, size_t BufferSize>
void NoiseGenerator<SampleType, BufferSize>::getSamples(std::array<SampleType, BufferSize>& buffer) {
    std::default_random_engine engine(std::random_device{}());
    std::normal_distribution<SampleType> dist(mean, stdDev);

    for (auto& sample : buffer) {
        sample = dist(engine);
    }
}

template <typename SampleType, size_t BufferSize>
void NoiseGenerator<SampleType, BufferSize>::addNoise(std::array<SampleType, BufferSize>& buffer) {
    std::array<SampleType, BufferSize> noise{};
    getSamples(noise);

    size_t idx = 0;
    for (auto& sample : noise) {
        buffer[idx++] += sample;
    }
}


template class NoiseGenerator<float, BUFFERSIZE_64>;
template class NoiseGenerator<float, BUFFERSIZE_128>;
template class NoiseGenerator<float, BUFFERSIZE_256>;