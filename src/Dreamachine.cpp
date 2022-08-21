
#include <DreamachineUI.h>
#include <DreamachineWaves.h>
#include <EncoderReader.h>
#include <Dreamachine.h>

DreamachineUI ui;

Dreamachine::Dreamachine()
{
    ui.attachEncoder(*this);
    DreamachineWaves waves;
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
    Serial.print("Mode :");
    Serial.println(this->getLabel());
}

String Dreamachine::getLabel()
{
    return this->labels[this->mode];
}

void Dreamachine::onEncoderClick(ButtonEventEnum button)
{
    Serial.print("in Dreamachine button event ");
    Serial.println(button);
    if (button == BUTTON_1_EVENT)
    {
        Serial.println("zero");
        ui.updateDisplay("zero", 0);
    }
}

void Dreamachine::onEncoderRotate(EncoderEventEnum encoder, float value)
{
    Serial.print("in Dreamachine encoder event ");
    Serial.println(encoder);
    Serial.println(value);
}
