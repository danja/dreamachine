#ifndef _LFO_h
#define _LFO_h

#include <dispatcher.hpp>

class LFO
{
public:
    LFO();
    void checkTimer();
    void setFrequency(float freq);
    Dispatcher<float> dispatcher;

private:
    enum waveform
    {
        square,
        sine
    };
    float frequency;
    int period;
    // void setup();
    // void loop();
    //   void IRAM_ATTR onTimer(); // ARDUINO_ISR_ATTR
};
#endif
