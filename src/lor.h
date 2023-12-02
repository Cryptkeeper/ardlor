#ifndef LOR_H
#define LOR_H

#include "HardwareSerial.h"

namespace LOR
{
    enum class Command : unsigned char
    {
        SetIntensity = 0x03,
        Fade = 0x04,
    };

    static constexpr unsigned char STOP = 0;

    static constexpr HardwareSerial& Serial = Serial1;

    void Write(const unsigned char* msg);
    void WriteHeartbeat(bool now = false);

    struct Circuit
    {
        const unsigned char unit;
        const unsigned char channel;
    };

    void WriteIntensity(const Circuit& circuit, float intensity);
    void WriteFade(const Circuit& circuit, float start_intensity, float end_intensity, float seconds);
}

#endif //LOR_H
