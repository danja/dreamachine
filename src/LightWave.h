#ifndef _LIGHTWAVE_h
#define _LIGHTWAVE_h

#include <Arduino.h>

#define BTN_STOP_ALARM 17

class LightWave
{
public:
    LightWave();
    void checkTimer();
    void setFrequency(float freq);

private:
    float frequency;
    int period;
    // void setup();
    // void loop();
    //   void IRAM_ATTR onTimer(); // ARDUINO_ISR_ATTR
};
#endif
