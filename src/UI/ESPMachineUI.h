#ifndef _DREAMACHINEUI_h
#define _DREAMACHINEUI_h

// #include <Q.h>
#include <iostream>
#include <Arduino.h>
#include <ESPMachine.h>

using namespace std;

class ESPMachineUI
{
public:
    ESPMachineUI();
    static void UI(void *pvParameter);

    void attachEncoder(ESPMachine dreamachine); // should probably extract interface

    void updateDisplay(string label, string value);

    void initEncoder1(long currentValue, long minValue, long maxValue, long steps, boolean invert, bool circleValues);
    void initEncoder2(long currentValue, long minValue, long maxValue, long steps, boolean invert, bool circleValues);

private:
};

#endif