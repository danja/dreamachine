#ifndef _DREAMACHINE_H
#define _DREAMACHINE_H

#include <Arduino.h>

#include <Dispatcher.hpp>
#include <iostream>

// #include <DreamachineUI.h>
// #include <DreamachineWaves.h>

#include <Mode.h>
// #include <Q.h>

#include <EncoderReader.h>

using namespace std;

class Dreamachine
{
public:
    Dreamachine();
    // Mode modes[2];

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

    // void nextMode();
    void setMode(int modeIndex);
    void update();

    void onEncoderClick(ButtonEventEnum button);
    void onEncoderRotate(EncoderEventEnum encoder, float value);

    void registerCallback(Dispatcher<ButtonEventEnum> &dispatcher)
    {
        using namespace std::placeholders;
        dispatcher.addCallback(std::bind(&Dreamachine::onEncoderClick, this, _1));
    }

    void registerCallback(Dispatcher<EncoderEventEnum, float> &dispatcher)
    {
        using namespace std::placeholders;
        dispatcher.addCallback(std::bind(&Dreamachine::onEncoderRotate, this, _1, _2));
    }

private:
    int modeIndex = 0;

    //  char *labels[9] = {"Brightness", "Light <->", "Frequency", "Light Wave", "Light /\\/", "Volume", "Audio <->", "Sound Wave", "Audio /\\/"};
};

#endif
