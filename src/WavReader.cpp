//
// Created by louis on 02/06/25.
//
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <algorithm>

#include "WavReader.h"
#include "SupportedFormats.h"

template<typename SampleType, size_t BufferSize>
void WavReader<SampleType, BufferSize>::setFileSize() {
    fileSize = std::filesystem::file_size(pathWav);
    if (fileSize < headerSize) {
        std::cerr << "File too small to be .wav" << std::endl;
    }
}

template<typename SampleType, size_t BufferSize>
void WavReader<SampleType, BufferSize>::readHeader(std::ifstream& file) {
    file.seekg(0, std::ios::beg);

    char chunkId[4];
    uint32_t chunkSize;

    // Read RIFF header
    file.read(chunkId, 4); // "RIFF"
    if (std::memcmp(chunkId, "RIFF", 4) != 0) throw std::runtime_error("Not a RIFF file");

    file.read(reinterpret_cast<char*>(&header.fileSize), sizeof(uint32_t));

    file.read(chunkId, 4); // "WAVE"
    if (std::memcmp(chunkId, "WAVE", 4) != 0) throw std::runtime_error("Not a WAVE file");

    // Look for the "fmt " chunk
    while (file.read(chunkId, 4)) {
        file.read(reinterpret_cast<char*>(&chunkSize), sizeof(uint32_t));

        if (std::memcmp(chunkId, "fmt ", 4) == 0) {
            // Read the rest of the fmt chunk
            file.read(reinterpret_cast<char*>(&header.audioFormat), 16); // assuming standard fmt chunk size
            break;
        } else {
            file.seekg(chunkSize, std::ios::cur); // skip unknown chunk
        }
    }

    // Look for the "data" chunk
    while (file.read(chunkId, 4)) {
        file.read(reinterpret_cast<char*>(&chunkSize), sizeof(uint32_t));

        if (std::memcmp(chunkId, "data", 4) == 0) {
            header.dataSize = chunkSize;
            break;
        } else {
            file.seekg(chunkSize, std::ios::cur); // skip fact, PEAK, etc.
        }
    }

    // Store current position (start of data)
    startPositionData = file.tellg();

    // Print for debug
    std::cout << "Audio Format:\t" << header.audioFormat <<
                 "\nSample Rate:\t" << header.samplingRate <<
                 "\nChannels:\t" << header.channels <<
                 "\nData Size:\t" << header.dataSize << "\n";
}


template<typename SampleType, size_t BufferSize>
int WavReader<SampleType, BufferSize>::getNumberSamples(unsigned int fileSize) {
    std::div_t numberSamples = std::div(static_cast<int>(fileSize - startPositionData), static_cast<int>(sizeof(SampleType)));
    if (numberSamples.rem != 0) {
        std::cerr << "Incomplete number of samples. Aborting..." << std::endl;
        return 0;
    }
    return numberSamples.quot;
}

template<typename SampleType, size_t BufferSize>
void WavReader<SampleType, BufferSize>::getSamples(std::array<SampleType, BufferSize>& buffer) {
    size_t remaining = (lastIdx < allSamples.size()) ? (allSamples.size() - lastIdx) : 0;
    size_t toCopy = (remaining > BufferSize) ? BufferSize : remaining;

    std::copy_n(allSamples.begin() + lastIdx, toCopy, buffer.begin());
    std::fill(buffer.begin() + toCopy, buffer.end(), SampleType{0});

    lastIdx += toCopy;
}


template <typename SampleType, size_t BufferSize>
void WavReader<SampleType, BufferSize>::loadAllSamples() {
    std::ifstream file(pathWav, std::ios::binary);

    readHeader(file);

    int numberSamples = getNumberSamples(fileSize);
    if (numberSamples == 0) {
        std::cerr << "No samples to load!" << std::endl;
    }

    allSamples.resize(numberSamples);
    file.seekg(startPositionData, std::ios::beg);  // Skip header data

    if (startPositionData > fileSize) {
        std::cerr << "Seek operation failed!" << std::endl;
    }

    // Read only the actual audio data (not including the header)
    file.read(reinterpret_cast<char *>(allSamples.data()), numberSamples * sizeof(SampleType));

    std::cout << fileSize << " Bytes loaded from " << pathWav.string() << std::endl;
}


template class WavReader<float, BUFFERSIZE_64>;
template class WavReader<float, BUFFERSIZE_128>;
template class WavReader<float, BUFFERSIZE_256>;
