#include <iostream>
#include <sstream>

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

void Mode::setValue(long value)
{
    this->value = value;
}

string BrightnessMode::getValueString()
{
    stringstream stream;
    stream << value;
    string s = stream.str();
    Serial.print("Value = ");
    Serial.println(value);
    Serial.print("String = ");
    Serial.println(s.c_str());
    return s;
}

string LightPhaseMode::getValueString()
{
    return "lpalue";
}
