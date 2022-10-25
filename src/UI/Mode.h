#ifndef _MODE_H
#define _MODE_H

#include <iostream>
#include <Arduino.h>

using namespace std;

typedef struct ModeMessage
{
    int index = 0;
    float value = 0;
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
    float currentValue = 0;
    float minValue = 0;
    float maxValue = 100;
    float stepSize = 1;
    bool invert = false;
    bool circleValues = true;

    void init(int index, string label, float currentValue, float minValue, float maxValue, float stepSize, bool invert, bool circleValues);

    virtual string getValueString()
    {
        return "none";
    };

    static string valueToString(float value);
    void setValue(float value);
    float getValue();

private:
    // float previousValue = 0;
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