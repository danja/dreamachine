#include <Arduino.h>
#include <RotaryEncoder.h>
#include <EncodersReader.h>

// GPIO ports for rotary encoders
const int ENCODER_1_CLK = 34;
const int ENCODER_1_DT = 35;
const int ENCODER_1_SW = 4;

const int ENCODER_2_CLK = 36;
const int ENCODER_2_DT = 39;
const int ENCODER_2_SW = 16;

// const int ENCODER_1_STEPS = 10;
// const int ENCODER_2_STEPS = 10;

// Esp32RotaryEncoder encoder1 = Esp32RotaryEncoder(ENCODER_1_CLK, ENCODER_1_DT, ENCODER_1_SW); // brightness
// Esp32RotaryEncoder encoder2 = Esp32RotaryEncoder(ENCODER_2_CLK, ENCODER_2_DT, ENCODER_2_SW); // everything else

RotaryEncoder encoder1;
RotaryEncoder encoder2;

EncodersReader::EncodersReader()
{

    //  encoder1.setup(encoderEvent1, buttonEvent1); // pass the callback functions (leave as-is)
    //  encoder2.setup(encoderEvent2, buttonEvent2); // pass the callback functions (leave as-is)
}

void EncodersReader::init()
{
    encoder1.init(ENCODER_1_CLK, ENCODER_1_DT, ENCODER_1_SW);
    encoder2.init(ENCODER_2_CLK, ENCODER_2_DT, ENCODER_2_SW);
}

void EncodersReader::operate()
{
    if (encoder1.readButton())
    {
        Serial.println("Button 1");
        buttonDispatcher.broadcast(BUTTON_1_EVENT);
    }
    if (encoder2.readButton())
    {
        Serial.println("Button 2");
        buttonDispatcher.broadcast(BUTTON_2_EVENT);
    }

    if (RotaryEncoder::moved)
    {
        int8_t rotationValue1 = encoder1.readEncoder();
        int8_t rotationValue2 = encoder2.readEncoder();

        // If valid movement, do something
        if (rotationValue1 != 0)
        {

            encoderDispatcher.broadcast(ENCODER_1_EVENT, encoder1.value());
        }

        // If valid movement, do something
        if (rotationValue2 != 0)
        {
            encoderDispatcher.broadcast(ENCODER_2_EVENT, encoder2.value());
        }
    }

    /*
    if (encoder1.buttonClicked()) // look at a flag
    {
        buttonDispatcher.broadcast(BUTTON_1_EVENT);
        encoder1.resetButton(); // reset the flag
    }

    if (encoder1.valueChanged()) // look at a flag
    {
        encoderDispatcher.broadcast(ENCODER_1_EVENT, encoder1.getValue());
        encoder1.resetValue(); // reset the flag
    }

    if (encoder2.buttonClicked()) // look at a flag
    {
        buttonDispatcher.broadcast(BUTTON_2_EVENT);
        encoder2.resetButton(); // reset the flag
    }

    if (encoder2.valueChanged()) // look at a flag
    {
        encoderDispatcher.broadcast(ENCODER_2_EVENT, encoder2.getValue());
        encoder2.resetValue(); // reset the flag
    }
    */
}

void EncodersReader::setScale1(float minValue, float maxValue, float stepSize, boolean invert, bool circleValues)
{
    encoder1.setScale(minValue, maxValue, stepSize, invert, circleValues);
}

void EncodersReader::setScale2(float minValue, float maxValue, float stepSize, boolean invert, bool circleValues)
{
    encoder2.setScale(minValue, maxValue, stepSize, invert, circleValues);
}
