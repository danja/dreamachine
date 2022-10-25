#include <iostream>
#include <sstream>

#include <Mode.h>
#include <Arduino.h>

using namespace std;

Mode::Mode() {}

// string _label,

void Mode::init(int index, string label, float currentValue, float minValue, float maxValue, float stepSize, bool invert, bool circleValues)
{
    this->modeMessage.index = index;
    this->label = label;
    this->currentValue = currentValue;
    this->minValue = minValue;
    this->maxValue = maxValue;
    this->stepSize = stepSize;
    this->invert = invert;
    this->circleValues = circleValues;
}

// hmm, doubling up variables..?
void Mode::setValue(float value)
{
    this->modeMessage.value = value;
    this->currentValue = value;
}

float Mode::getValue()
{
    return this->modeMessage.value;
}

string Mode::valueToString(float value)
{
    stringstream stream;
    stream << value;
    string s = stream.str();
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