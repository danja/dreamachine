#ifndef _DREAMACHINEWAVES_h
#define _DREAMACHINEWAVES_h

// #include <Arduino.h>
// #include <Dreamachine.h>
#include <LFO.h>

class DreamachineWaves
{
public:
    DreamachineWaves();
    static void Waves(void *pvParameter);

private:
    //  static void updateFrequency(long value);
    // static void updateLightWave(long value);
};
#endif
