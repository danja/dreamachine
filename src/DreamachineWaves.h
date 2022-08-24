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
    //   void setDreamachine(Dreamachine dreamachine);
    void setLightFrequency(int frequency);
    //  LFO lightwave;

private:
    //  Dreamachine dreamachine;
};
#endif
