#ifndef _MODE_H
#define _MODE_H

#include <iostream>
#include <Arduino.h>

using namespace std;

typedef struct ModeMessage
{
    string label = "maximum label length maybe";
    long minValue = 0;
    long maxValue = 0;
    long steps = 0;
    bool invert = false;
    bool circleValues = true;
    long value = 0;
} AModeMessage;

enum modeSelect
{
    BRIGHTNESS,
    LIGHT_BALANCE,
    FREQUENCY,
    LIGHT_WAVE,
    LIGHT_PHASE,
    VOLUME,
    AUDIO_BALANCE,
    SOUND_WAVE,
    AUDIO_PHASE
};

class Mode
{
public:
    Mode();
    ModeMessage modeMessage;

    void init(string _label, long _minValue, long _maxValue, long _steps, bool _invert, bool _circleValues);

    virtual string getValueString()
    {
        return "none";
    };

    static string valueToString(long value);
    void setValue(long value);
    long getValue();

private:
    // long previousValue = 0;
};

class BrightnessMode : public Mode
{
public:
    string getValueString() override;

private:
};

class LightBalanceMode : public Mode
{
public:
    string getValueString() override;

private:
};

class FrequencyMode : public Mode
{
public:
    string getValueString() override;

private:
};

class LightWaveMode : public Mode
{
public:
    string getValueString() override;

private:
};

//   char *labels[9] = {"Brightness", "Light <->", "Frequency", "Light Wave", "Light /\\/", "Volume", "Audio <->", "Sound Wave", "Audio /\\/"};

class LightPhaseMode : public Mode
{
public:
    string getValueString() override;

private:
};

class VolumeMode : public Mode
{
public:
    string getValueString() override;

private:
};

class AudioBalanceMode : public Mode
{
public:
    string getValueString() override;

private:
};

class SoundWaveMode : public Mode
{
public:
    string getValueString() override;

private:
};

class AudioPhaseMode : public Mode
{
public:
    string getValueString() override;

private:
};

#endif