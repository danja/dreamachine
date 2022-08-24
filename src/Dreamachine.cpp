
#include <DreamachineUI.h>
#include <DreamachineWaves.h>
#include <EncoderReader.h>
#include <Dreamachine.h>
#include <Mode.h>

#include <iostream>

using namespace std;

DreamachineUI ui;
// Mode aMode;
Mode modes[2];

Dreamachine::Dreamachine()
{
    ui.attachEncoder(*this);
    loadModes();

    DreamachineWaves waves; // if this is placed up there ^^ it kills the encoder input
}

void Dreamachine::loadModes()
{
    //  aMode = Mode();
    //
    //   char *labels[9] = {"Brightness", "Light <->", "Frequency", "Light Wave", "Light /\\/", "Volume", "Audio <->", "Sound Wave", "Audio /\\/"};
    //  char *b = "Brightness";
    // modes[0].init("Brightness", 10, 100, 100, true, false);
    modes[0] = BrightnessMode();
    modes[0].init("Brightness", 10, 100, 100, true, false);

    modes[1] = LightPhaseMode();
    modes[1].init("Light /\\/", 0, 360, 10, true, false);
}

void Dreamachine::setMode(int mode)
{
    this->mode = mode;
}

void Dreamachine::nextMode()
{
    this->mode++;
    if (this->mode >= N_MODES)
    {
        this->mode = 0;
    }
}

void Dreamachine::onEncoderClick(ButtonEventEnum button)
{
    // Serial.print("in Dreamachine button event ");
    // Serial.println(button);
    if (button == BUTTON_1_EVENT)
    {
        mode = 0;
        ui.updateDisplay("zero", 0);
    }
    if (button == BUTTON_2_EVENT)
    {

        nextMode();
        Serial.print("Label : ");
        Serial.println(modes[mode].label.c_str());

        //            Serial.print("ALabel : ");
        //  Serial.println(getLabel().c_str());

        // aMode.minValue = 55;
        // Serial.println(aMode.label.c_str());
        // Serial.println(aMode.minValue);

        //   ui.updateDisplay(getLabel().c_str(), aMode.getValueString());
        ui.updateDisplay(modes[mode].label, "tttt");
    }
}

void Dreamachine::onEncoderRotate(EncoderEventEnum encoder, float value)
{
    // Serial.print("in Dreamachine encoder event ");

    if (encoder == ENCODER_1_EVENT)
    {
        Serial.print("encoder 1 event : ");
        Serial.println(value);
    }
    if (encoder == ENCODER_2_EVENT)
    {
        Serial.print("encoder 2 event : ");
        Serial.println(value);
    }
}
