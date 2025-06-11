//
// Created by louis on 11/06/25.
//

#pragma once

template<typename SampleType>
class IAudioSink {
    public:
        virtual ~IAudioSink() = default;
        virtual void update(const SampleType*, size_t numSamples);
};