//
// Created by louis on 10/06/25.
//
#include <cstdint>

#include "SimpleDSPProcessor.h"

template <typename SampleType>
void SimpleDSPProcessor<SampleType>::process(const SampleType* input, SampleType* output, size_t numSamples) {
    for (size_t i = 0; i < numSamples; i++) {
        output[i] = input[i] + 1;
    }
}

template class SimpleDSPProcessor<float>;
template class SimpleDSPProcessor<double>;
template class SimpleDSPProcessor<uint16_t>;
template class SimpleDSPProcessor<uint32_t>;