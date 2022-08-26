
#include <DreamachineUI.h>
#include <DreamachineWaves.h>
#include <EncoderReader.h>
#include <Dreamachine.h>
#include <Mode.h>
#include <Q.h>

#include <iostream>

using namespace std;

QueueHandle_t intercoreQueue;

const int N_MODES = 9;

DreamachineUI ui;

Mode *modes[N_MODES];

Dreamachine::Dreamachine()
{
    intercoreQueue = xQueueCreate(QUEUE_LENGTH, QUEUE_ITEM_SIZE);
    if (intercoreQueue == NULL)
    {
        Serial.println("Error creating the intercoreQueue");
    }

    loadModes();

    ui.attachEncoder(*this); // attaches callbacks

    DreamachineWaves waves; // if this is placed up there ^^ it kills the encoder input

    //  update();
}

void Dreamachine::loadModes()
{
    modes[modeSelect::BRIGHTNESS] = new BrightnessMode();
    modes[modeSelect::BRIGHTNESS]->init("Brightness", 0, 100, 100, true, false);

    modes[modeSelect::FREQUENCY] = new FrequencyMode();
    modes[modeSelect::FREQUENCY]->init("Frequency ", 1, 50, 10, true, false);

    modes[modeSelect::LIGHT_PHASE] = new LightPhaseMode();
    modes[modeSelect::LIGHT_PHASE]->init("Light /\\/ ", 0, 360, 10, true, false);

    modes[modeSelect::LIGHT_BALANCE] = new LightBalanceMode();
    modes[modeSelect::LIGHT_BALANCE]->init("Light <-> ", 0, 100, 10, true, false);

    modes[modeSelect::LIGHT_WAVE] = new LightWaveMode();
    modes[modeSelect::LIGHT_WAVE]->init("Light Wave", 0, 1, 10, true, false);

    modes[modeSelect::VOLUME] = new VolumeMode();
    modes[modeSelect::VOLUME]->init("Volume    ", 0, 100, 10, true, false);

    modes[modeSelect::AUDIO_BALANCE] = new AudioBalanceMode();
    modes[modeSelect::AUDIO_BALANCE]->init("Audio <-> ", 0, 100, 10, true, false);

    modes[modeSelect::AUDIO_PHASE] = new AudioPhaseMode();
    modes[modeSelect::AUDIO_PHASE]->init("Audio /\\/ ", 0, 360, 10, true, false);

    modes[modeSelect::SOUND_WAVE] = new SoundWaveMode();
    modes[modeSelect::SOUND_WAVE]->init("Sound Wave", 0, 1, 10, true, false);

    this->currentMode = modes[modeSelect::FREQUENCY];
    //    delay(1000);
    // update();
}

void Dreamachine::setMode(int modeIndex)
{
    this->modeIndex = modeIndex;
}

void Dreamachine::nextMode()
{
    this->modeIndex++;
    if (this->modeIndex >= N_MODES)
    {
        this->modeIndex = 0;
    }
    this->currentMode = modes[modeIndex];
}

void Dreamachine::update()
{
    xQueueSend(intercoreQueue, &currentMode->modeMessage, QUEUE_SEND_DELAY);
    /*
     Serial.print("Label : ");
     Serial.println(currentMode->modeMessage.label.c_str());
     Serial.print("Value : ");
     Serial.println(currentMode->getValueString().c_str());
     */
    ui.updateDisplay(currentMode->modeMessage.label, currentMode->getValueString());
}

void Dreamachine::onEncoderClick(ButtonEventEnum button)
{
    if (button == BUTTON_1_EVENT)
    {
        modeIndex = modeSelect::BRIGHTNESS;
        this->currentMode = modes[modeIndex];
        currentMode->modeMessage.value = 0;
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
    if (encoder == ENCODER_1_EVENT)
    {
        modeIndex = modeSelect::BRIGHTNESS;
        update();
    }
    if (encoder == ENCODER_2_EVENT)
    {
        currentMode->setValue(value);
        update();
    }
}
