//
// Created by louis on 01/06/25.
//
#include <cstdint>
#include <cmath>

#include "SinGenerator.h"

template<typename SampleType>

std::vector<SampleType> SinGenerator<SampleType>::getSamples() {
    std::vector<SampleType> samples(this->bufferSize);
    const double omega = 2.0 * M_PI * this->_frequency;
    const double deltaT = 1.0 / static_cast<double>(this->sampleRate);

    for (size_t i = 0; i < this->bufferSize; ++i) {
        double t = static_cast<double>(i) * deltaT;
        samples[i] = static_cast<SampleType>(this->_amplitude * std::sin(omega * t));
    }

    return samples;
}

template class SinGenerator<float>;
template class SinGenerator<double>;
template class SinGenerator<uint16_t>;
template class SinGenerator<uint32_t>;