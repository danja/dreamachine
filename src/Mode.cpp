#include <iostream>
#include <sstream>

#include <Mode.h>
#include <Arduino.h>

using namespace std;

Mode::Mode() {}

// string _label,

void Mode::init(string _label, long _minValue, long _maxValue, long _steps, bool _invert, bool _circleValues)
{
    this->modeMessage.label = _label;
    this->modeMessage.minValue = _minValue;
    this->modeMessage.maxValue = _maxValue;
    this->modeMessage.steps = _steps;
    this->modeMessage.invert = _invert;
    this->modeMessage.circleValues = _circleValues;
    /*
    this->label = _label;
    //    Serial.print("A");

    // Serial.println(this->_minValue);
    minValue = _minValue;
    this->maxValue = _maxValue;
    this->steps = _steps;
    this->invert = _invert;
    this->circleValues = _circleValues;
    */
}

void Mode::setValue(long value)
{
    this->modeMessage.value = value;
}

long Mode::getValue()
{
    return this->modeMessage.value;
}

string BrightnessMode::getValueString()
{
    stringstream stream;
    stream << modeMessage.value;
    // stream << value;
    string s = stream.str();
    Serial.print("Value = ");
    Serial.println(modeMessage.value);
    Serial.print("String = ");
    Serial.println(s.c_str());
    return s;
}

string LightPhaseMode::getValueString()
{
    return "lpalue";
}
