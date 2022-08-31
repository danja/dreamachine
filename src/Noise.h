#ifndef _NOISEGEN_H
#define _NOISEGEN_H

#include <Dispatcher.hpp>
#include <iostream>

using namespace std;

const int DAC_1 = 25;
const int DAC_2 = 26;

const int NOISE_TIMER = 1;     // 2 of 4
const int NOISE_PRESCALE = 80; // was 80
const int NOISE_PERIOD = 25;   // 25;   // microseconds

class Noise
{
public:
    Noise();
    //  void outputNextValue();
    void checkTimer();
    void setAmplitude(float sine, float square);

    void registerCallback(Dispatcher<float, float> &dispatcher)
    {
        using namespace std::placeholders;
        dispatcher.addCallback(std::bind(&Noise::setAmplitude, this, _1, _2));
    }

private:
    // int period = 1; // 3906;
    float amplitude = 1;
};

#endif