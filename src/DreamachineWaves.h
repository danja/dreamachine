#ifndef _DREAMACHINEWAVES_h
#define _DREAMACHINEWAVES_h

// #include <Arduino.h>
#include <Dreamachine.h>

class DreamachineWaves
{
public:
    DreamachineWaves();
    static void Waves(void *pvParameter);
    void setDreamachine(Dreamachine dreamachine);

private:
    Dreamachine dreamachine;
};
#endif
