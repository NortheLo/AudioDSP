//
// Created by louis on 02/06/25.
//
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>

#include "WavReader.h"

#include <cstring>

template<typename SampleType>
void WavReader<SampleType>::setFileSize() {
    fileSize = std::filesystem::file_size(pathWav);
    if (fileSize < headerSize) {
        std::cerr << "File too small to be .wav" << std::endl;
    }
}

template<typename SampleType>
void WavReader<SampleType>::readHeader(std::ifstream& file) {
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


template<typename SampleType>
int WavReader<SampleType>::getNumberSamples(unsigned int fileSize) {
    std::div_t numberSamples = std::div((int) (fileSize - startPositionData), (int) sizeof(SampleType));
    if (numberSamples.rem != 0) {
        std::cerr << "Incomplete number of samples. Aborting..." << std::endl;
        return 0;
    }
    return numberSamples.quot;
}

template<typename SampleType>
std::vector<SampleType> WavReader<SampleType>::getSamples() {
    std::ifstream file(pathWav, std::ios::binary);

    readHeader(file);

    std::vector<SampleType> audioData;
    int numberSamples = getNumberSamples(fileSize);
    if (numberSamples == 0) {
        return audioData;
    }

    audioData.resize(numberSamples);
    file.seekg(startPositionData, std::ios::beg);  // Skip header data

    if (startPositionData > fileSize) {
        std::cerr << "Seek operation failed!" << std::endl;
        return audioData;
    }

    // Read only the actual audio data (not including the header)
    file.read(reinterpret_cast<char *>(audioData.data()), numberSamples * sizeof(SampleType));

    std::cout << fileSize << " Bytes loaded from " << pathWav.string() << std::endl;
    return audioData;
}

/* Right now only floats are supported */
template class WavReader<float>;
