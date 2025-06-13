//
// Created by louis on 01/06/25.
//
#include <cstdint>
#include <cmath>

#include "SinGenerator.h"
#include "SupportedFormats.h"

template<typename SampleType, size_t BufferSize>
void SinGenerator<SampleType, BufferSize>::getSamples(std::array<SampleType, BufferSize>& buffer) {
    const double omega = 2.0 * M_PI * this->_frequency;
    const double deltaT = 1.0 / static_cast<double>(this->sampleRate);

    for (size_t i = 0; i < BufferSize; ++i) {
        double t = static_cast<double>(i) * deltaT;
        buffer[i] = static_cast<SampleType>(this->_amplitude * std::sin(omega * t));
    }
}

template class SinGenerator<float, BUFFERSIZE_64>;
template class SinGenerator<float, BUFFERSIZE_128>;
template class SinGenerator<float, BUFFERSIZE_256>;

template class SinGenerator<uint32_t, BUFFERSIZE_64>;
template class SinGenerator<uint32_t, BUFFERSIZE_128>;
template class SinGenerator<uint32_t, BUFFERSIZE_256>;