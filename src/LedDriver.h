#ifndef _LEDDRIVER_h
#define _LEDDRIVER_h

#include <Dispatcher.hpp>
#include <iostream>

using namespace std;

enum Waveform
{
    SINE,
    SQUARE
};

class LedDriver
{
public:
    LedDriver();

    void setWaveform(Waveform form);
    void setBrightness(float brightness);
    void setValue(float sineLevel, float squareLevel);
    void registerCallback(Dispatcher<float, float> &dispatcher)
    {
        using namespace std::placeholders;
        dispatcher.addCallback(std::bind(&LedDriver::setValue, this, _1, _2));
    }

private:
    Waveform form = Waveform::SINE;
    float brightness = 0.5;
};
#endif
