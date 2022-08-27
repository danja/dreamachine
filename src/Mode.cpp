#include <iostream>
#include <sstream>

#include <Mode.h>
#include <Arduino.h>

using namespace std;

Mode::Mode() {}

// string _label,

void Mode::init(int index, string _label, long _minValue, long _maxValue, long _steps, bool _invert, bool _circleValues)
{
    this->modeMessage.index = index;
    this->label = _label;
    this->minValue = _minValue;
    this->maxValue = _maxValue;
    this->steps = _steps;
    this->invert = _invert;
    this->circleValues = _circleValues;
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

string Mode::valueToString(long value)
{
    stringstream stream;
    stream << value;
    // stream << value;
    string s = stream.str();
    // Serial.print("Value = ");
    // Serial.println(modeMessage.value);
    // Serial.print("String = ");
    // Serial.println(s.c_str());
    return s;
}

string BrightnessMode::getValueString()
{
    return Mode::valueToString(modeMessage.value);
}

string LightBalanceMode::getValueString()
{
    return Mode::valueToString(modeMessage.value);
}

string FrequencyMode::getValueString()
{
    return Mode::valueToString(modeMessage.value);
}

string LightWaveMode::getValueString()
{
    if (modeMessage.value > 0)
    {
        return "square";
    }
    return "sine";
}

string LightPhaseMode::getValueString()
{
    return Mode::valueToString(modeMessage.value);
}

string VolumeMode::getValueString()
{
    return Mode::valueToString(modeMessage.value);
}

string AudioBalanceMode::getValueString()
{
    return Mode::valueToString(modeMessage.value);
}

string SoundWaveMode::getValueString()
{
    return Mode::valueToString(modeMessage.value);
}

string AudioPhaseMode::getValueString()
{
    return Mode::valueToString(modeMessage.value);
}
//   char *labels[9] = {"Brightness", "Light <->", "Frequency", "Light Wave", "Light /\\/", "Volume", "Audio <->", "Sound Wave", "Audio /\\/"};