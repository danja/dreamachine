#ifndef _LFO_h
#define _LFO_h

#include <Dispatcher.hpp>

class LFO
{
public:
    LFO();
    Dispatcher<float, float> dispatcher;

    void setFrequency(float freq);
    // void setAmplitude(float amplitude);
    void IRAM_ATTR setPeriod(int period);

    void checkTimer();
    void killTimer();

private:
    void makeWaves(uint32_t step);
    enum waveform
    {
        square,
        sine
    };
    float frequency = 1;
    // float amplitude = 0.5;
    int period = 3906; //??
};
#endif
