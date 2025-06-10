//
// Created by louis on 01/06/25.
//

#pragma once
#include <vector>

template<typename SampleType>

class IAudioSource {
public:
    IAudioSource(size_t bufferSize) : bufferSize(bufferSize) { };
    virtual ~IAudioSource() = default;

    virtual std::vector<SampleType> getSamples() = 0;

    void setSampleRate(unsigned int rate) { sampleRate = rate; }
    size_t getBufferSize() { return bufferSize; }
    unsigned int getSampleRate() { return sampleRate; }
protected:
    size_t bufferSize;
    unsigned int sampleRate = 44100;
};