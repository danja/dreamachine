#include <Arduino.h>
#include <LedDriver.h>
#include <dispatcher.hpp>

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

void LedDriver::setLevel(float level)
{
    ledcWrite(ledChannel, level);
    // Serial.println(level);
}