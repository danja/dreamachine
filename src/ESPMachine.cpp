
#include <ESPMachineUI.h>
#include <ESPMachineWaves.h>
#include <EncoderReader.h>
#include <ESPMachine.h>
#include <Mode.h>
#include <Q.h>

#include <iostream>

using namespace std;

QueueHandle_t intercoreQueue;

const int N_MODES = 9;

ESPMachineUI ui;

Mode *modes[N_MODES];

ESPMachine::ESPMachine()
{
    intercoreQueue = xQueueCreate(QUEUE_LENGTH, QUEUE_ITEM_SIZE);
    if (intercoreQueue == NULL)
    {
        Serial.println("Error creating the intercoreQueue");
    }

    loadModes();

    ui.attachEncoder(*this); // attaches callbacks

    ESPMachineWaves waves; // if this is placed up there ^^ it kills the encoder input

    //
    // update();
}

void ESPMachine::loadModes()
{
    modes[modeSelect::BRIGHTNESS] = new BrightnessMode();
    modes[modeSelect::BRIGHTNESS]->init(modeSelect::BRIGHTNESS, "Brightness", 0, 100, 100, true, false);

    modes[modeSelect::FREQUENCY] = new FrequencyMode();
    modes[modeSelect::FREQUENCY]->init(modeSelect::FREQUENCY, "Frequency ", 1, 11, 10, true, false);

    modes[modeSelect::LIGHT_PHASE] = new LightPhaseMode();
    modes[modeSelect::LIGHT_PHASE]->init(modeSelect::LIGHT_PHASE, "Light /-\\ ", 0, 360, 10, true, false);

    modes[modeSelect::LIGHT_BALANCE] = new LightBalanceMode();
    modes[modeSelect::LIGHT_BALANCE]->init(modeSelect::LIGHT_BALANCE, "Light <-> ", 0, 100, 10, true, false);

    modes[modeSelect::LIGHT_WAVE] = new LightWaveMode();
    modes[modeSelect::LIGHT_WAVE]->init(modeSelect::LIGHT_WAVE, "Light Wave", 0, 1, 10, true, false);

    modes[modeSelect::VOLUME] = new VolumeMode();
    modes[modeSelect::VOLUME]->init(modeSelect::VOLUME, "Volume    ", 0, 100, 10, true, false);

    modes[modeSelect::AUDIO_BALANCE] = new AudioBalanceMode();
    modes[modeSelect::AUDIO_BALANCE]->init(modeSelect::AUDIO_BALANCE, "Audio <-> ", 0, 100, 10, true, false);

    modes[modeSelect::AUDIO_PHASE] = new AudioPhaseMode();
    modes[modeSelect::AUDIO_PHASE]->init(modeSelect::AUDIO_PHASE, "Audio /-\\ ", 0, 360, 10, true, false);

    modes[modeSelect::SOUND_WAVE] = new SoundWaveMode();
    modes[modeSelect::SOUND_WAVE]->init(modeSelect::SOUND_WAVE, "Sound Wave", 0, 1, 10, true, false);

    this->currentMode = modes[modeSelect::FREQUENCY];
    // delay(500);
    // update();
    delay(1000);

    //   ui.updateDisplay(currentMode->label, currentMode->getValueString());
}

void ESPMachine::setMode(int modeIndex)
{
    this->modeIndex = modeIndex;
    if (this->modeIndex >= N_MODES)
    {
        this->modeIndex = 0;
    }
    this->currentMode = modes[modeIndex];
}

/*
void ESPMachine::nextMode()
{
    this->modeIndex++;

    this->currentMode = modes[modeIndex];
}
*/

void ESPMachine::update()
{
    xQueueSend(intercoreQueue, &currentMode->modeMessage, QUEUE_SEND_DELAY);

    // currentMode->modeMessage.maxValue = 7;
    /*
        Serial.print("----ALabel : ");
        Serial.println(currentMode->modeMessage.maxValue);
        Serial.println(currentMode->label.c_str());
        Serial.print("Value : ");
        Serial.println(currentMode->getValueString().c_str());
    */
    ui.updateDisplay(currentMode->label, currentMode->getValueString());

    /*
        Serial.print("BLabel : ");
        Serial.println(currentMode->modeMessage.maxValue);
        Serial.println(currentMode->label.c_str());
        Serial.print("Value : ");
        Serial.println(currentMode->getValueString().c_str());
    */
}

void ESPMachine::onEncoderClick(ButtonEventEnum button)
{
    if (button == BUTTON_1_EVENT)
    {
        setMode(modeSelect::BRIGHTNESS);
        // modeIndex = modeSelect::BRIGHTNESS;
        //   this->currentMode = modes[modeIndex];
        currentMode->modeMessage.value = 0;
        Serial.println("..............");
        Serial.println(currentMode->modeMessage.index);
        Serial.println(currentMode->modeMessage.value);
        update();
    }
    if (button == BUTTON_2_EVENT)
    {
        setMode(++modeIndex);
        update();
    }
}

void ESPMachine::onEncoderRotate(EncoderEventEnum encoder, float value)
{
    if (encoder == ENCODER_1_EVENT)
    {
        setMode(modeSelect::BRIGHTNESS);
        currentMode->setValue(value);
        update();
    }
    if (encoder == ENCODER_2_EVENT)
    {
        //   Serial.println("---");
        // Serial.println(currentMode->label.c_str());
        currentMode->setValue(value);
        // Serial.println(currentMode->label.c_str());
        update();
        // Serial.println(currentMode->label.c_str());
    }
}
