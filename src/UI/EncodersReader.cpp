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

RotaryEncoder encoder1;
RotaryEncoder encoder2;

EncodersReader::EncodersReader()
{
}

void EncodersReader::init()
{
    encoder1.init(ENCODER_1_CLK, ENCODER_1_DT, ENCODER_1_SW);
    encoder2.init(ENCODER_2_CLK, ENCODER_2_DT, ENCODER_2_SW);
}

void EncodersReader::showConfig(RotaryEncoder encoder)
{
    Serial.print("minValue : ");
    Serial.println(encoder.minValue);
    Serial.print("maxValue : ");
    Serial.println(encoder.maxValue);
    Serial.print("stepSize : ");
    Serial.println(encoder.stepSize);
    Serial.print("invert : ");
    Serial.println(encoder.invert);
    Serial.print("circleValues : ");
    Serial.println(encoder.circleValues);
}

void EncodersReader::operate()
{
    if (encoder1.readButton())
    {
        Serial.println("\nButton 1");
        // showConfig(encoder1);
        buttonDispatcher.broadcast(BUTTON_1_EVENT);
    }
    if (encoder2.readButton())
    {
        Serial.println("\nButton 2");
        // showConfig(encoder2);
        buttonDispatcher.broadcast(BUTTON_2_EVENT);
    }

    if (RotaryEncoder::moved)
    {
        int8_t rotationValue1 = encoder1.readEncoder();
        int8_t rotationValue2 = encoder2.readEncoder();

        // If valid movement, do something
        if (rotationValue1 != 0)
        {
            Serial.print("Encoder 1 : ");
            Serial.println(encoder1.value());
            encoderDispatcher.broadcast(ENCODER_1_EVENT, encoder1.value());
        }

        // If valid movement, do something
        if (rotationValue2 != 0)
        {
            Serial.print("Encoder 2 : ");
            Serial.println(encoder2.value());
            encoderDispatcher.broadcast(ENCODER_2_EVENT, encoder2.value());
        }
    }
}

void EncodersReader::configure1(float startValue, float minValue, float maxValue, float stepSize, bool invert, bool circleValues)
{
    encoder1.configure(startValue, minValue, maxValue, stepSize, invert, circleValues);
}

void EncodersReader::configure2(float startValue, float minValue, float maxValue, float stepSize, bool invert, bool circleValues)
{
    encoder2.configure(startValue, minValue, maxValue, stepSize, invert, circleValues);
}
