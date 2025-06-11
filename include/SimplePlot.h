//
// Created by louis on 11/06/25.
//

#pragma once

#include "IAudioSink.h"
#include <vector>
#include "implot.h"

template<typename SampleType>
class SimplePlot : public IAudioSink<SampleType> {
public:
    SimplePlot(size_t maxSamples = 1024)
        : maxSamples_(maxSamples) {}

    void update(const SampleType* data, size_t numSamples) override {
        // Append new samples, truncate old ones
        if (buffer_.size() + numSamples > maxSamples_) {
            size_t excess = buffer_.size() + numSamples - maxSamples_;
            buffer_.erase(buffer_.begin(), buffer_.begin() + excess);
        }
        buffer_.insert(buffer_.end(), data, data + numSamples);
    }

    void drawPlot(const char* label = "Audio Signal") {
        if (ImPlot::BeginPlot(label)) {
            std::vector<float> x(buffer_.size());
            for (size_t i = 0; i < x.size(); ++i) x[i] = static_cast<float>(i);
            ImPlot::PlotLine("Signal", x.data(), buffer_.data(), static_cast<int>(buffer_.size()));
            ImPlot::EndPlot();
        }
    }

private:
    std::vector<SampleType> buffer_;
    size_t maxSamples_;
};

