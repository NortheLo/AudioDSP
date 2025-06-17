//
// Created by louis on 11/06/25.
//

#pragma once

#include "IGuiElement.h"
#include "implot.h"
#include <algorithm>
#include <vector>

template<typename SampleType>
class SimplePlot : public IGuiElement<SampleType> {
public:
    SimplePlot() { }
    ~SimplePlot() override = default;
    void draw(const SampleType* data, size_t numSamples) override {
        if (numSamples == 0) return;

        auto [minIt, maxIt] = std::minmax_element(data, data + numSamples);
        float newMin = static_cast<float>(*minIt);
        float newMax = static_cast<float>(*maxIt);

        // Add padding
        float padding = (newMax - newMin) * 0.1f;
        if (padding == 0.0f) padding = 0.01f;
        newMin -= padding;
        newMax += padding;

        if (!initialized) {
            currentMinY = newMin;
            currentMaxY = newMax;
            initialized = true;
        } else {
            currentMinY = smoothing * newMin + (1.0f - smoothing) * currentMinY;
            currentMaxY = smoothing * newMax + (1.0f - smoothing) * currentMaxY;
        }

        // Prepare X-axis values
        std::vector<float> x(numSamples);
        for (size_t i = 0; i < numSamples; ++i)
            x[i] = static_cast<float>(i);

        // Set axis limits
        ImPlot::SetNextAxesLimits(0, static_cast<float>(numSamples), currentMinY, currentMaxY, ImGuiCond_Always);

        if (ImPlot::BeginPlot("Audio Signal")) {
            ImPlot::PlotLine("Time-Domain Plot", x.data(), data, static_cast<int>(numSamples));
            ImPlot::EndPlot();
        }
    }


private:
    float currentMinY = 0.f;
    float currentMaxY = 2.0f;
    bool initialized = false;
    const float smoothing = 0.8f;

};
