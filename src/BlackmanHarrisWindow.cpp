//
// Created by louis on 19/06/25.
//
#include <cmath>
#include <iostream>
#include <bits/ostream.tcc>

#include "BlackmanHarrisWindow.h"
#include "SupportedFormats.h"


template<typename SampleType, size_t BufferSize>
void BlackmanHarrisWindowing<SampleType, BufferSize>::process(const SampleType* input, SampleType* output, size_t numSamples) {
    if (numSamples != BufferSize) {
        std::cerr << "Number of inputs must be equal to the number of outputs" << std::endl;
    }

    for (size_t i = 0; i < numSamples; i++) {
        output[i] = input[i] * weights[i];
    }
}

template<typename SampleType, size_t BufferSize>
void BlackmanHarrisWindowing<SampleType, BufferSize>::process(const SampleType* inputR, const SampleType* inputL,
    SampleType* outputR, SampleType* outputL, size_t numSamples) {
    if (numSamples != BufferSize) {
        std::cerr << "Number of inputs must be equal to the number of outputs" << std::endl;
    }

    for (size_t i = 0; i < numSamples; i++) {
        outputR[i] = inputR[i] * weights[i];
        outputL[i] = inputL[i] * weights[i];
    }
}

template<typename SampleType, size_t BufferSize>
void BlackmanHarrisWindowing<SampleType, BufferSize>::calculateWeights() {
    constexpr SampleType a0 = 0.35875;
    constexpr SampleType a1 = 0.48829;
    constexpr SampleType a2 = 0.14128;
    constexpr SampleType a3 = 0.01168;
    const SampleType pi = static_cast<SampleType>(M_PI);

    for (size_t n = 0; n < BufferSize; ++n) {
        SampleType x = static_cast<SampleType>(n) / (BufferSize - 1);
        weights[n] = a0
                  - a1 * std::cos(2 * pi * x)
                  + a2 * std::cos(4 * pi * x)
                  - a3 * std::cos(6 * pi * x);
    }
}

template class BlackmanHarrisWindowing<float, BUFFERSIZE_64>;
template class BlackmanHarrisWindowing<float, BUFFERSIZE_128>;
template class BlackmanHarrisWindowing<float, BUFFERSIZE_256>;