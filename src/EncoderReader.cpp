#include <Arduino.h>
#include <Esp32RotaryEncoder.h>
#include <EncoderReader.h>
// #include <Dreamachine.h>

// GPIO ports for rotary encoders
const int ENCODER_1_CLK = 34;
const int ENCODER_1_DT = 35;
const int ENCODER_1_SW = 16;

const int ENCODER_2_CLK = 36;
const int ENCODER_2_DT = 39;
const int ENCODER_2_SW = 4;

const int ENCODER_1_STEPS = 10;
const int ENCODER_2_STEPS = 10;

Esp32RotaryEncoder encoder1 = Esp32RotaryEncoder(ENCODER_1_CLK, ENCODER_1_DT, ENCODER_1_SW); // brightness
Esp32RotaryEncoder encoder2 = Esp32RotaryEncoder(ENCODER_2_CLK, ENCODER_2_DT, ENCODER_2_SW); // everything else

// forward declarations
void IRAM_ATTR encoderEvent1();
void IRAM_ATTR buttonEvent1();
void IRAM_ATTR encoderEvent2();
void IRAM_ATTR buttonEvent2();

EncoderReader::EncoderReader()
{

    encoder1.setScale(0, 100, 1, true, true);
    encoder1.setup(encoderEvent1, buttonEvent1); // pass the callback functions (leave as-is)
    encoder2.setup(encoderEvent2, buttonEvent2); // pass the callback functions (leave as-is)
}

/*
void EncoderReader::setMachine(Dreamachine machine)
{
    this->machine = machine;
}
*/
void EncoderReader::operate()
{
    ////////////////////////////
    if (encoder1.buttonClicked()) // look at a flag
    {
        Serial.println("1 click!"); // do stuff
        encoder1.resetButton();     // reset the flag
    }

    if (encoder1.valueChanged()) // look at a flag
    {
        Serial.print("1 Value :"); // do stuff
        Serial.println(encoder1.getValue());
        encoder1.resetValue(); // reset the flag
    }

    if (encoder2.buttonClicked()) // look at a flag
    {
        Serial.println("2 click!"); // do stuff
                                    //      buttonDispatcher.broadcast(BUTTON_2_EVENT);
        //        this->machine.nextMode();
        encoder2.resetButton(); // reset the flag
    }

    if (encoder2.valueChanged()) // look at a flag
    {
        Serial.print("2 Value :"); // do stuff
        Serial.println(encoder2.getValue());
        encoder2.resetValue(); // reset the flag
    }
}

void IRAM_ATTR encoderEvent1()
{
    encoder1.updateValue();
}

void IRAM_ATTR buttonEvent1()
{
    encoder1.readButton_ISR();
}

void IRAM_ATTR encoderEvent2()
{
    encoder2.updateValue();
}

void IRAM_ATTR buttonEvent2()
{
    encoder2.readButton_ISR();
}