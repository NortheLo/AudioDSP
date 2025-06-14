//
// Created by louis on 10/06/25.
//

#pragma once

#include "IDSPProcessor.h"

/*
 * This module is only used for testing the pipeline
 */

template<typename SampleType>
class SimpleDSPProcessor : public IDSPProcessor<SampleType> {
public:
    void process(const SampleType* input, SampleType* output, size_t numSamples) override;
    void process(const SampleType* inputR, const SampleType* inputL,
                SampleType* outputR, SampleType* outputL,
                size_t numSamples) override;
};
