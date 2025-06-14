//
// Created by louis on 01/06/25.
//

#pragma once
#include <array>

template<typename SampleType, size_t BufferSize>

class IAudioSource {
public:
    IAudioSource() = default;
    virtual ~IAudioSource() = default;

    virtual void getSamples(std::array<SampleType, BufferSize>& buffer) = 0;
    virtual void getSamples(std::array<SampleType, BufferSize>& bufferR,
                            std::array<SampleType, BufferSize>& bufferL) = 0;



    void setSampleRate(unsigned int rate) { sampleRate = rate; }
    size_t getBufferSize() { return BufferSize; }
    unsigned int getSampleRate() { return sampleRate; }
protected:
    unsigned int sampleRate = 44100;
};