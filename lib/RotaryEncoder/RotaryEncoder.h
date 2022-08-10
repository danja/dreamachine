
#ifndef RotaryEncoder_h
#define RotaryEncoder_h

#include "AiEsp32RotaryEncoder.h"
#include "AiEsp32RotaryEncoderNumberSelector.h"

class RotaryEncoder
{

public:
    //  RotaryEncoder();
    RotaryEncoder(const uint8_t clk, const uint8_t dt, const uint8_t sw, const uint8_t steps);

    // void init();
    void setup(void (*ISR_callback)(void));
    // void drawLabel(const String label);
    void IRAM_ATTR readEncoder_ISR();
    boolean changed();
    uint8_t getValue();

private:
    AiEsp32RotaryEncoder encoder;
    // AiEsp32RotaryEncoderNumberSelector numberSelector;

    void IRAM_ATTR readEncoder();
};

#endif