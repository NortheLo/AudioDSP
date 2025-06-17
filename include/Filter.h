//
// Created by louis on 18/06/25.
//

#pragma once

#include <vector>
#include <deque>

#include <IDSPProcessor.h>

/*
    Filter Structure: https://vru.vibrationresearch.com/wp-content/uploads/2021/04/iir_order2_df1_ab.png
    Feedback path only in IIR Mode
*/
template<typename SampleType>
class Filter {
public:
    Filter(std::vector<float> a, std::vector<float> b);

    void process(const SampleType* input, SampleType* output, size_t numSamples);
    void process(const SampleType* inputR, const SampleType* inputL,
                 SampleType* outputR, SampleType* outputL, size_t numSamples);

private:
    std::vector<float> numerator;
    std::vector<float> denumerator;

    std::deque<SampleType> fifoR;
    std::deque<SampleType> fifoL;

    std::deque<SampleType> outputHistR;
    std::deque<SampleType> outputHistL;
};
