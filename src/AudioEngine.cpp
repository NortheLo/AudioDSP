//
// Created by louis on 09/06/25.
//

#include <algorithm>

#include "AudioEngine.h"

#include <iostream>

template<typename SampleType>
void AudioEngine<SampleType>::processNextBlock(SampleType* outputBuffer) {
    if(!source_) return;

    // Temporary buffer to hold source data
    tempBuffer_.resize(source_->getBufferSize());
    tempBuffer_ = source_->getSamples();

    if(tempBuffer_.size() != source_->getBufferSize()) {
        std::cerr << "Mismatch of received vector and desired length" << std::endl;
        return ;
    };

    // Apply all processors in sequence
    std::vector<SampleType> inputBuffer = tempBuffer_;
    for(auto& proc : processors_) {
        proc->process(inputBuffer.data(), tempBuffer_.data(), source_->getBufferSize());
        inputBuffer = tempBuffer_;  // chain output to next processor input
    }

    std::copy_n(tempBuffer_.begin(), source_->getBufferSize(), outputBuffer);
}

template class AudioEngine<float>;
template class AudioEngine<double>;
template class AudioEngine<uint16_t>;
template class AudioEngine<uint32_t>;