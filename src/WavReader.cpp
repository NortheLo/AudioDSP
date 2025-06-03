//
// Created by louis on 02/06/25.
//
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>

#include "WavReader.h"

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
    file.read(reinterpret_cast<char*>(&header), headerSize);
    std::cout << "Audio Format:\t" << header.audioFormat <<
                "\nSample Rate:\t" << header.samplingRate <<
                    "\nChannels:\t" << header.channels << "\n";
}

template<typename SampleType>
int WavReader<SampleType>::getNumberSamples(unsigned int fileSize) {
    std::div_t numberSamples = std::div((int) (fileSize - headerSize), (int) sizeof(SampleType));
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
    file.seekg(headerSize, std::ios::beg);  // Skip header data

    if (file.tellg() != headerSize) {
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
