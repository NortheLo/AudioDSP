//
// Created by louis on 02/06/25.
//

#pragma once

#pragma pack(push, 1)
typedef struct {
    uint8_t  RIFF[4];           // "RIFF"
    uint32_t fileSize;
    uint8_t  WAVE[4];           // "WAVE"
    uint8_t  fmt[4];            // "fmt "
    uint32_t subchunksize;
    uint16_t audioFormat;
    uint16_t channels;
    uint32_t samplingRate;
    uint32_t bytesPerSec;
    uint16_t blockAlign;
    uint16_t bitsPerSample;
    uint8_t  dataBlocID[4];     // "data"
    uint32_t dataSize;
} wavHeader;
#pragma pack(pop)
