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

class LightPhaseMode : public Mode
{
public:
    string getValueString() override;

private:
};

#endif