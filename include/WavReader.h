//
// Created by louis on 02/06/25.
//

#pragma once

#include <iostream>
#include <filesystem>
#include <vector>

#include "IAudioSource.h"
#include "WavHeader.h"

template<typename SampleType>

class WavReader{
public:
        WavReader(const std::filesystem::path path) {
                if (std::filesystem::exists(path) && std::filesystem::is_regular_file(path)) {
                        pathWav = path;
                        setFileSize();
                } else {
                        std::cerr << "File is invalid or doesn't exist.\n";
                }
        };
        void setSampleRate(unsigned int rate) { };
        unsigned int getSampleRate() { return (unsigned int) header.dataSize; }

        std::vector<SampleType> getSamples();

protected:
        void readHeader(std::ifstream& file);
        void setFileSize();
        int getNumberSamples(unsigned int filesize);

private:
        std::filesystem::path pathWav;
        wavHeader header;
        unsigned int headerSize = sizeof(wavHeader);
        unsigned int fileSize;

};
