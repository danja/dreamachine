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

const int N_MODES = 2;

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

    void nextMode();
    void setMode(int mode);
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
    int mode = 0;

    /*
        enum modes
        {
            brightness,
            light_balance,
            frequency,
            light_wave,
            light_phase,
            volume,
            audio_balance,
            sound_wave,
            audio_phase
        } mode;
    */

    //  char *labels[9] = {"Brightness", "Light <->", "Frequency", "Light Wave", "Light /\\/", "Volume", "Audio <->", "Sound Wave", "Audio /\\/"};
    // String labels[9] =

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
