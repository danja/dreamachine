#ifndef _LFO_h
#define _LFO_h

#include <dispatcher.hpp>

class LFO
{
public:
    LFO();
    Dispatcher<float> dispatcher;

    void setFrequency(float freq);

    void checkTimer();
    void killTimer();

private:
    void makeWaves(uint32_t step);
    enum waveform
    {
        square,
        sine
    };
    float frequency;
    int period;
};
#endif
