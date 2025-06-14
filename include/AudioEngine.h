//
// Created by louis on 09/06/25.
//

#pragma once

#include <memory>

#include "SupportedFormats.h"
#include "IAudioEngine.h"
#include "AudioEngineMono.h"
#include "AudioEngineStereo.h"

template<typename SampleType, size_t BufferSize>
class AudioEngine {
public:
    static std::unique_ptr<IAudioEngine<SampleType, BufferSize>>

    create(BufferFormat type) {
        switch (type) {
        case BufferFormat::Mono:
            return std::make_unique<AudioEngineMono<SampleType, BufferSize>>();
        case BufferFormat::Stereo:
            return std::make_unique<AudioEngineStereo<SampleType, BufferSize>>();
        default:
            return nullptr;
        }
    }
};
