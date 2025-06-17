//
// Created by louis on 18/06/25.
//
#include <cstdint>
#include "PulseGenerator.h"
#include "SupportedFormats.h"

template<typename SampleType, size_t BufferSize>
void PulseGenerator<SampleType, BufferSize>::getSamples(std::array<SampleType, BufferSize>& buffer) {
    buffer.fill(0);

    if (!alreadyTriggered) {
        buffer[0] = 1;
        alreadyTriggered = true;
    }
}

template<typename SampleType, size_t BufferSize>
void PulseGenerator<SampleType, BufferSize>::getSamples(std::array<SampleType, BufferSize>& bufferR,
                        std::array<SampleType, BufferSize>& bufferL) {

    bufferR.fill(0);
    bufferL.fill(0);

    if (!alreadyTriggered) {
        bufferR[0] = 1;
        bufferL[0] = 1;
        alreadyTriggered = true;
    }
}

template class PulseGenerator<float, BUFFERSIZE_64>;
template class PulseGenerator<float, BUFFERSIZE_128>;
template class PulseGenerator<float, BUFFERSIZE_256>;

template class PulseGenerator<uint32_t, BUFFERSIZE_64>;
template class PulseGenerator<uint32_t, BUFFERSIZE_128>;
template class PulseGenerator<uint32_t, BUFFERSIZE_256>;