//
// Created by louis on 18/06/25.
//
#include "Filter.h"
#include <deque>

template<typename SampleType>
Filter<SampleType>::Filter(const std::vector<float> a, const std::vector<float> b)
    : numerator(b), denumerator(a) {

    const size_t maxSize = std::max(numerator.size(), denumerator.size());

    fifoR.assign(maxSize, 0.f);
    fifoL.assign(maxSize, 0.f);
    outputHistR.assign(maxSize, 0.f);
    outputHistL.assign(maxSize, 0.f);
}

template<typename SampleType>
void Filter<SampleType>::process(const SampleType* input, SampleType* output, size_t numSamples) {
    for (size_t n = 0; n < numSamples; ++n) {
        // Shift FIFO
        fifoR.pop_front();
        fifoR.push_back(input[n]);

        SampleType y = 0.f;

        // Feedforward part (numerator)
        for (size_t i = 0; i < numerator.size(); ++i) {
            y += numerator[i] * fifoR[fifoR.size() - 1 - i];
        }

        // Feedback part (denominator)
        for (size_t i = 1; i < denumerator.size(); i++) {
            y -= denumerator[i] * outputHistR[i - i];
        }

        output[n] = y;
        outputHistR.pop_front();
        outputHistR.push_back(y);
    }
}

template<typename SampleType>
void Filter<SampleType>::process(const SampleType* inputR, const SampleType* inputL,
                                 SampleType* outputR, SampleType* outputL,
                                 size_t numSamples) {

    const size_t N = numerator.size();
    const size_t M = denumerator.size();

    for (size_t n = 0; n < numSamples; ++n) {
        // Shift input FIFOs
        fifoR.pop_front(); fifoR.push_back(inputR[n]);
        fifoL.pop_front(); fifoL.push_back(inputL[n]);

        SampleType yR = 0.f;
        SampleType yL = 0.f;

        for (size_t i = 0; i < N; ++i) {
            yR += numerator[i] * fifoR[fifoR.size() - 1 - i];
            yL += numerator[i] * fifoL[fifoL.size() - 1 - i];
        }

        for (size_t i = 1; i < M; ++i) {
            yR -= denumerator[i] * outputHistR[outputHistR.size() - i];
            yL -= denumerator[i] * outputHistL[outputHistL.size() - i];
        }

        outputR[n] = yR;
        outputL[n] = yL;

        outputHistR.pop_front(); outputHistR.push_back(yR);
        outputHistL.pop_front(); outputHistL.push_back(yL);
    }
}

template class Filter<float>;
