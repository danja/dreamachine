#include <iostream>
#include <Mode.h>
#include <Arduino.h>

using namespace std;

Mode::Mode() {}

// string _label,

void Mode::init(string _label, long _minValue, long _maxValue, long _steps, bool _invert, bool _circleValues)
{
    this->label = _label;
    //    Serial.print("A");

    // Serial.println(this->_minValue);
    minValue = _minValue;
    this->maxValue = _maxValue;
    this->steps = _steps;
    this->invert = _invert;
    this->circleValues = _circleValues;
}

string BrightnessMode::getValueString()
{
    return "bvalue";
}

string LightPhaseMode::getValueString()
{
    return "lpalue";
}
