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

    void initEncoder1(float startValue, float minValue, float maxValue, float stepSize, bool invert, bool circleValues);
    void initEncoder2(float startValue, float minValue, float maxValue, float stepSize, bool invert, bool circleValues);

private:
};

#endif