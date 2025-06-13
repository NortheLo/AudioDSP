//
// Created by louis on 02/06/25.
//

#pragma once

#include <iostream>
#include <filesystem>
#include <vector>

#include "IAudioSource.h"
#include "WavHeader.h"

template<typename SampleType, size_t BufferSize>
class WavReader{
public:
        WavReader(const std::filesystem::path path) {
                if (std::filesystem::exists(path) && std::filesystem::is_regular_file(path)) {
                        pathWav = path;
                        setFileSize();
                } else {
                        std::cerr << "File is invalid or doesn't exist.\n";
                }

                loadAllSamples();
        };
        void setSampleRate(unsigned int rate) { };
        unsigned int getSampleRate() { return (unsigned int) header.samplingRate; }

        void getSamples(std::array<SampleType, BufferSize>& buffer);

protected:
        void readHeader(std::ifstream& file);
        void setFileSize();
        int getNumberSamples(unsigned int filesize);
        void loadAllSamples();

private:
        std::filesystem::path pathWav;
        wavHeader header;
        unsigned int headerSize = sizeof(wavHeader);
        unsigned int fileSize;
        unsigned int startPositionData; // in bytes

        size_t lastIdx = 0;
        std::vector<SampleType> allSamples;
};
