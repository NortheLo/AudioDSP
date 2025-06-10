//
// Created by louis on 09/06/25.
//

#pragma once

#include <cstddef>

template<typename SampleType>
class IDSPProcessor {
    public:
        virtual ~IDSPProcessor() = default;

        virtual void process(const SampleType* input, SampleType* output, size_t numSamples) = 0;
};

