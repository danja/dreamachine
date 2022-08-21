#ifndef _DREAMACHINEUI_h
#define _DREAMACHINEUI_h

#include <Arduino.h>

// #include <Dreamachine.h>

class DreamachineUI
{
public:
    DreamachineUI();
    static void UI(void *pvParameter);
    //  void setDreamachine(Dreamachine dreamachine);

    void updateDisplay(String label, int value);
    void updateDisplay(String label, String value);

private:
    // Dreamachine dreamachine;
    /*
    Brightness : 0-100%
Light Balance : L% : R%
Frequency : 1-50 Hz
Wave : sine/square
Light Phase : 0-359°

Volume : 0-100%
Audio Balance : L% : R%
Noise : white/pink
Audio Phase : 0-359°
*/
};

#endif