#ifndef _NOISEGEN_H
#define _NOISEGEN_H

const int DAC_1 = 25;
const int DAC_2 = 26;

const int NOISE_TIMER = 1;     // 2 of 4
const int NOISE_PRESCALE = 80; // was 80
const int NOISE_PERIOD = 100;  // 25;   // microseconds
class Noise
{
public:
    Noise();
    //  void outputNextValue();
    void checkTimer();

private:
    // int period = 1; // 3906;
};

#endif