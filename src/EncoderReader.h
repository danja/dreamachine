#ifndef _ENCODERREADER_H
#define _ENCODERREADER_H

#include <Dispatcher.hpp>
#include <Esp32RotaryEncoder.h>

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

class EncoderReader
{
public:
    EncoderReader();
    //   void setMachine(Dreamachine machine);
    void operate();

    Dispatcher<ButtonEventEnum> buttonDispatcher;
    Dispatcher<EncoderEventEnum, float> encoderDispatcher;

private:
    //  Dreamachine machine;
};

#endif