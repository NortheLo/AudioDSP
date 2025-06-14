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

template <typename SampleType>
void SimpleDSPProcessor<SampleType>::process(const SampleType* inputR, const SampleType* inputL,
                                            SampleType* outputR, SampleType* outputL, size_t numSamples) {
    for (size_t i = 0; i < numSamples; i++) {
        outputR[i] = inputR[i] + 1;
        outputL[i] = inputL[i] + 1;
    }
}


template class SimpleDSPProcessor<float>;
template class SimpleDSPProcessor<uint32_t>;