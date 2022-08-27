#ifndef _MODE_H
#define _MODE_H

#include <iostream>
#include <Arduino.h>

using namespace std;

typedef struct ModeMessage
{
    int index = 0;
    long value = 0;
} AModeMessage;

enum modeSelect
{
    BRIGHTNESS,    // 0
    FREQUENCY,     // 1
    LIGHT_WAVE,    // 2
    LIGHT_BALANCE, // 3
    LIGHT_PHASE,   // 4

    VOLUME,        // 5
    SOUND_WAVE,    // 7
    AUDIO_BALANCE, // 6
    AUDIO_PHASE    // 8
};

class Mode
{
public:
    Mode();
    ModeMessage modeMessage;

    // UI bits
    string label = "ABCDEFGHIJ"; // doesn't have to be passed around
    long minValue = 0;
    long maxValue = 0;
    long steps = 0;
    bool invert = false;
    bool circleValues = true;

    void init(int index, string _label, long _minValue, long _maxValue, long _steps, bool _invert, bool _circleValues);

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