//
// Created by louis on 16/06/25.
//

#pragma once

#include <vector>
#include <mutex>

#include "IAudioSink.h"

template<typename SampleType, size_t BufferSize>
class GuiBridgeSink : public IAudioSink<SampleType> {
public:
    void update(const SampleType* data, size_t size) override {
        std::lock_guard<std::mutex> lock(mutex_);
        buffer_.insert(buffer_.end(), data, data + size);


        if (buffer_.size() > maxSize) {
            buffer_.erase(buffer_.begin(), buffer_.begin() + (buffer_.size() - maxSize));
        }
    }

    std::vector<SampleType> getBufferCopy() {
        std::lock_guard<std::mutex> lock(mutex_);
        return buffer_;
    }

private:
    std::vector<SampleType> buffer_;
    std::mutex mutex_;
    const size_t maxSize = 2 * 8192;
};
