
#include <DreamachineUI.h>
#include <DreamachineWaves.h>
#include <EncoderReader.h>
#include <Dreamachine.h>
#include <Mode.h>
#include <Q.h>

#include <iostream>

using namespace std;

const int queueItemSize = sizeof(AModeMessage); // Q
const int queueLength = 1;                      // Q
QueueHandle_t queue;                            // Q

DreamachineUI ui;
// Mode aMode;
Mode *modes[2];

// DreamachineWaves waves;

Dreamachine::Dreamachine()
{
    queue = xQueueCreate(queueLength, queueItemSize);
    if (queue == NULL)
    {
        Serial.println("Error creating the queue");
    }

    ui.attachEncoder(*this);
    loadModes();

    DreamachineWaves waves; // if this is placed up there ^^ it kills the encoder input

    // waves.setQueue(queue);
}

void Dreamachine::loadModes()
{
    //   char *labels[9] = {"Brightness", "Light <->", "Frequency", "Light Wave", "Light /\\/", "Volume", "Audio <->", "Sound Wave", "Audio /\\/"};

    modes[0] = new BrightnessMode();
    modes[0]->init("Brightness", 10, 100, 100, true, false);

    modes[1] = new LightPhaseMode();
    modes[1]->init("Light /\\/", 0, 360, 10, true, false);
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

void Dreamachine::update()
{
    //  waves.setLightFrequency(modes[mode]->value); needs a semaphore???????
    xQueueSend(queue, &modes[mode]->modeMessage, portMAX_DELAY);

    ui.updateDisplay(modes[mode]->modeMessage.label, modes[mode]->getValueString());
}

void Dreamachine::onEncoderClick(ButtonEventEnum button)
{
    // Serial.print("in Dreamachine button event ");
    // Serial.println(button);
    if (button == BUTTON_1_EVENT)
    {
        mode = 0;
        update();
    }
    if (button == BUTTON_2_EVENT)
    {

        nextMode();
        update();
    }
}

void Dreamachine::onEncoderRotate(EncoderEventEnum encoder, float value)
{
    // Serial.print("in Dreamachine encoder event ");

    if (encoder == ENCODER_1_EVENT)
    {
        mode = 0;
        update();
    }
    if (encoder == ENCODER_2_EVENT)
    {
        modes[mode]->setValue(value);
        update();
    }
}
