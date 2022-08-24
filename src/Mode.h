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

 brightness,
            light_balance,
            frequency,
            light_wave,
            light_phase,
            volume,
            audio_balance,
            sound_wave,
            audio_phase
*/
#ifndef _MODE_H
#define _MODE_H

#include <iostream>
#include <Arduino.h>

using namespace std;

class Mode
{
public:
    Mode();

    void init(string _label, long _minValue, long _maxValue, long _steps, bool _invert, bool _circleValues);
    string label;
    long minValue;
    long maxValue;
    long steps;
    bool invert;
    bool circleValues;
    virtual string getValueString()
    {
        return "none";
    };

    void setValue(long value);
    long value;

private:
    // long previousValue = 0;
};

class BrightnessMode : public Mode
{
public:
    string getValueString() override;

private:
};

class LightPhaseMode : public Mode
{
public:
    string getValueString() override;

private:
};

#endif