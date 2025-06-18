//
// Created by louis on 19/06/25.
//

#pragma once

#include <array>

#include "IDSPProcessor.h"

template<typename SampleType, size_t BufferSize>
class BlackmanHarrisWindowing : public IDSPProcessor<SampleType>{
    public:
        BlackmanHarrisWindowing() {
            calculateWeights();
        }

        void process(const SampleType* input, SampleType* output, size_t numSamples) override ;
        void process(const SampleType* inputR, const SampleType* inputL,
                     SampleType* outputR, SampleType* outputL, size_t numSamples) override;
    private:
        void calculateWeights();

        size_t length;
        std::array<SampleType, BufferSize> weights{};
};
