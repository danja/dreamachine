#ifndef _ENCODERREADER_H
#define _ENCODERREADER_H

#include <Dispatcher.hpp>
#include <RotaryEncoder.h>

enum ButtonEventEnum
{
    BUTTON_1_EVENT,
    BUTTON_2_EVENT
};

enum EncoderEventEnum
{
    ENCODER_1_EVENT,
    ENCODER_2_EVENT
};

class EncodersReader
{
public:
    EncodersReader();
    void init();
    void configure1(float startValue, float minValue, float maxValue, float stepSize, bool invert, bool circleValues);
    void configure2(float startValue, float minValue, float maxValue, float stepSize, bool invert, bool circleValues);

    void operate();

    void showConfig(RotaryEncoder encoder);

    Dispatcher<ButtonEventEnum> buttonDispatcher;
    Dispatcher<EncoderEventEnum, float> encoderDispatcher;

private:
};

#endif