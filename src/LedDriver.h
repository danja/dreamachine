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
    Waveform form = Waveform::SINE;
    void setWaveform(Waveform form);
    void setLevel(float sineLevel, float squareLevel);
    void registerCallback(Dispatcher<float, float> &dispatcher)
    {
        using namespace std::placeholders;
        dispatcher.addCallback(std::bind(&LedDriver::setLevel, this, _1, _2));
    }

private:
};
#endif
