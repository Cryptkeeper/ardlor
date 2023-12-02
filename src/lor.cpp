#include "lor.h"

#include <Arduino.h>

void LOR::Write(const unsigned char* msg)
{
    Serial.write(0);

    // write msg until a stop (zero) byte is encountered
    unsigned char b;
    while ((b = *msg++) != STOP)
        Serial.write(b);

    Serial.write(0);
    Serial.flush();
}

void LOR::WriteHeartbeat(const bool now)
{
    static unsigned long last_ms = 0;
    const unsigned long ms = millis();

    // conditionally throttle sending heartbeats every 500ms vs every function invocation
    if (!now || ms - last_ms >= 500) return;

    last_ms = ms;

    const auto* msg = new unsigned char[4]{0xFF, 0x81, 0x56, STOP};

    // write heartbeat message to all units (0xFF)
    Write(msg);
    delete[] msg;
}

namespace LOR
{
    static unsigned char encodeIntensity(const float intensity)
    {
        return static_cast<unsigned char>(intensity * (0x01 - 0xF0) + 0xF0);
    }

    static unsigned short encodeDuration(const float seconds)
    {
        return static_cast<unsigned short>(roundf(5099 / (seconds / 0.1F)));
    }
}

void LOR::WriteIntensity(const Circuit& circuit, const float intensity)
{
    const auto* msg = new unsigned char[5]
    {
        circuit.unit,
        static_cast<unsigned char>(Command::SetIntensity),
        encodeIntensity(intensity),
        circuit.channel,
        STOP,
    };

    Write(msg);
    delete[] msg;
}

void LOR::WriteFade(const Circuit& circuit,
                    const float start_intensity,
                    const float end_intensity,
                    const float seconds)
{
    const unsigned short duration = encodeDuration(seconds);

    const auto* msg = new unsigned char [8]
    {
        circuit.unit,
        static_cast<unsigned char>(Command::Fade),
        encodeIntensity(start_intensity),
        encodeIntensity(end_intensity),
        static_cast<unsigned char>(duration >> 8),
        static_cast<unsigned char>(duration & 0xFF),
        circuit.channel,
        STOP,
    };

    Write(msg);
    delete[] msg;
}
