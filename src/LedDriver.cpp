#include <Arduino.h>
#include <LedDriver.h>
#include <Dispatcher.hpp>

const int LED_L = 32;
const int LED_R = 33;

// PWM properties
const int pwmFreq = 5000;
const int ledChannel = 0;
const int resolution = 8;

LedDriver::LedDriver()
{
    // set up LEDs
    ledcSetup(ledChannel, pwmFreq, resolution);

    // attach the channel to the GPIO to be controlled
    ledcAttachPin(LED_L, ledChannel);
    ledcAttachPin(LED_R, ledChannel);
}

void LedDriver::setWaveform(Waveform form)
{
    this->form = form;
}

void LedDriver::setLevel(float sineLevel, float squareLevel)
{
    if (form == Waveform::SINE)
    {
        ledcWrite(ledChannel, sineLevel);
    }
    if (form == Waveform::SQUARE)
    {
        ledcWrite(ledChannel, squareLevel);
    }
}