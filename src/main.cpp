#include <Arduino.h>

#include "lor.h"

void setup()
{
    LOR::Serial.begin(/* baud = */ 19200);

    // blast of heartbeats to establish initial connections
    for (uint8_t i = 0; i < 10; i++)
        LOR::WriteHeartbeat(/* now = */ true);
}

void loop()
{
    LOR::WriteHeartbeat();

    constexpr auto circuit = LOR::Circuit{
        /* unit = */ 0x01, /* channel = */ 0x01
    };

    // set to full brightness for 250ms
    WriteIntensity(circuit, 1.0F);
    delay(250);

    // ramp 0 to 50% in remaining 0.25 seconds
    WriteFade(circuit, 0.0F, 0.5F, 0.25F);
    delay(250);
}
