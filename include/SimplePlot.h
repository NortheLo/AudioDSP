//
// Created by louis on 11/06/25.
//

#pragma once

#include "IGuiElement.h"
#include "implot.h"
#include <vector>

template<typename SampleType>
class SimplePlot : public IGuiElement<SampleType> {
public:
    SimplePlot() { }
    ~SimplePlot() override = default;

    void draw(const SampleType* data, size_t numSamples) override {
        if (ImPlot::BeginPlot("Audio Signal")) {
            std::vector<float> x(numSamples);
            for (size_t i = 0; i < numSamples; ++i) {
                x[i] = static_cast<float>(i);
            }

            ImPlot::PlotLine("Signal", x.data(), data, static_cast<int>(numSamples));
            ImPlot::EndPlot();
        }
    }
};
