//
// Created by louis on 09/06/25.
//

#pragma once

#include <cstddef>

template<typename SampleType>
class IDSPProcessor {
    public:
        virtual ~IDSPProcessor() = default;

        // mono signal
        virtual void process(const SampleType* input, SampleType* output, size_t numSamples) = 0;
        // stereo
        virtual void process(const SampleType* inputR, const SampleType* inputL,
                            SampleType* outputR, SampleType* outputL,
                            size_t numSamples) = 0;
};