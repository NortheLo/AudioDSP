//
// Created by louis on 17/06/25.
//

#pragma once

template<typename SampleType>
class IGuiElement {
public:
    virtual ~IGuiElement() = default;

    virtual void draw(const SampleType*, size_t numSamples) = 0;
};