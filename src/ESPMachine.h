#ifndef _DREAMACHINE_H
#define _DREAMACHINE_H

#include <Arduino.h>

#include <Dispatcher.hpp>
#include <iostream>

// #include <ESPMachineUI.h>
// #include <ESPMachineWaves.h>

#include <Mode.h>
// #include <Q.h>

#include <EncodersReader.h>

using namespace std;

class ESPMachine
{
public:
    ESPMachine();

    void loadModes();

    int brightnessValue = 0;
    int light_balanceValue = 50;
    float frequencyValue = 10;
    int light_waveValue = 0;
    int light_phaseValue = 0;

    int volumeValue = 0;
    int audio_balanceValue = 50;
    int sound_typeValue = 0;
    int audio_phaseValue = 0;

    Mode *currentMode;

    void setMode(int modeIndex);
    void update();

    void onEncoderClick(ButtonEventEnum button);
    void onEncoderRotate(EncoderEventEnum encoder, float value);

    void registerCallback(Dispatcher<ButtonEventEnum> &dispatcher)
    {
        using namespace std::placeholders;
        dispatcher.addCallback(std::bind(&ESPMachine::onEncoderClick, this, _1));
    }

    void registerCallback(Dispatcher<EncoderEventEnum, float> &dispatcher)
    {
        using namespace std::placeholders;
        dispatcher.addCallback(std::bind(&ESPMachine::onEncoderRotate, this, _1, _2));
    }

private:
    int modeIndex = 0;

    //  char *labels[9] = {"Brightness", "Light <->", "Frequency", "Light Wave", "Light /\\/", "Volume", "Audio <->", "Sound Wave", "Audio /\\/"};
};

#endif
