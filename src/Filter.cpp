//
// Created by louis on 18/06/25.
//
#include "Filter.h"

template<typename SampleType>
Filter<SampleType>::Filter(const std::vector<float> a, const std::vector<float> b) : numerator(a), denumerator(b) {
    // get longest delay line tap
    int len = a.size() >= b.size() ? a.size() : b.size();

    for (int i = 0; i < len; i++) {
        fifoR.push_front(0.f);
        fifoL.push_front(0.f);
    }
}

template<typename SampleType>
void Filter<SampleType>::process(const SampleType* input, SampleType* output, size_t numSamples)  {
    // Update the FIFO with the new input sample
    for (int i = 0; i < numSamples; i++){
        fifoR.push_back(input[i]);
        fifoR.pop_front();
    }

    for (size_t sample_idx = 0; sample_idx < numSamples; sample_idx++) {
        // Feedforward part (numerator)
        for (size_t i = 0; i < numerator.size(); i++) {
            output[sample_idx] += numerator[i] * fifoR[fifoR.size() - 1 - i];
        }

        // Feedback part (denominator)
        for (size_t i = 1; i < denumerator.size(); i++) {
            output[sample_idx] -= denumerator[i] * fifoR[i - 1];
        }
    }
}

template<typename SampleType>
void Filter<SampleType>::process(const SampleType* inputR, const SampleType* inputL,
                SampleType* outputR, SampleType* outputL, size_t numSamples)  {

    for (size_t i = 0; i < numSamples; i++) {
        fifoR.push_back(inputR[i]);
        fifoR.pop_front();

        fifoL.push_back(inputL[i]);
        fifoL.pop_front();
    }

    for (size_t sample_idx = 0; sample_idx < numSamples; sample_idx++) {
        // Feedforward part (numerator)
        for (size_t i = 0; i < numerator.size(); i++) {
            outputR[sample_idx] += numerator[i] * fifoR[fifoR.size() - 1 - i];
            outputL[sample_idx] += numerator[i] * fifoL[fifoL.size() - 1 - i];

        }

        // Feedback part (denominator)
        for (size_t i = 1; i < denumerator.size(); i++) {
            outputR[sample_idx] -= denumerator[i] * fifoR[i - 1];
            outputL[sample_idx] -= denumerator[i] * fifoL[i - 1];
        }
    }
}

template class Filter<float>;