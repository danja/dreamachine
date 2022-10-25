
#include <ESPMachineUI.h>
#include <ESPMachineWaves.h>
#include <EncodersReader.h>
#include <ESPMachine.h>
#include <Mode.h>
#include <Q.h>

#include <iostream>

using namespace std;

TaskHandle_t uiHandle = NULL;
TaskHandle_t wavesHandle = NULL;

QueueHandle_t intercoreQueue;

const int N_MODES = 9;

ESPMachineUI ui;
ESPMachineWaves waves;

Mode *modes[N_MODES];

/**
 * Sets up serial port and creates an instance of ESPMachine
 */
void setup()
{
    Serial.begin(115200);
    ESPMachine dreamachine;
}

/**
 * Does nothing, periodically
 */
void loop()
{
    delay(100);
}

ESPMachine::ESPMachine()
{
    ui.attachEncoder(*this); // attaches callbacks

    /* Creating a task that runs the ESPMachineWaves::Waves function. */
    xTaskCreatePinnedToCore(
        ESPMachineWaves::Waves,
        "ESPMachineWaves",
        4096, // was 2048, 4096
        NULL,
        2,            // 1 | portPRIVILEGE_BIT,
        &wavesHandle, // was &AudioTask,
        1);

    /* It creates a task that runs the ESPMachineUI::UI function. */
    xTaskCreatePinnedToCore(
        ESPMachineUI::UI,
        "ESPMachineUI",
        4096, // stack size, was 4096, 64000 // high 97004
        NULL,
        2, // priority
        &uiHandle,
        0); // core

    intercoreQueue = xQueueCreate(QUEUE_LENGTH, QUEUE_ITEM_SIZE);
    if (intercoreQueue == NULL)
    {
        Serial.println("Error creating the intercoreQueue");
    }

    loadModes();
}

void ESPMachine::loadModes()
{
    // RotaryEncoder::configure(float startValue, float minValue, float maxValue, float stepSize, bool invert, bool circleValues)
    modes[modeSelect::BRIGHTNESS] = new BrightnessMode();
    modes[modeSelect::BRIGHTNESS]->init(modeSelect::BRIGHTNESS, "Brightness", 10, 0, 100, 1, false, false);

    modes[modeSelect::FREQUENCY] = new FrequencyMode();
    modes[modeSelect::FREQUENCY]->init(modeSelect::FREQUENCY, "Frequency ", 2, 1, 100, 0.25, false, false);

    modes[modeSelect::LIGHT_PHASE] = new LightPhaseMode();
    modes[modeSelect::LIGHT_PHASE]->init(modeSelect::LIGHT_PHASE, "Light /-\\ ", 0, 0, 360, 10, false, true);

    modes[modeSelect::LIGHT_BALANCE] = new LightBalanceMode();
    modes[modeSelect::LIGHT_BALANCE]->init(modeSelect::LIGHT_BALANCE, "Light <-> ", 50, 0, 100, 10, false, false);

    modes[modeSelect::LIGHT_WAVE] = new LightWaveMode();
    modes[modeSelect::LIGHT_WAVE]->init(modeSelect::LIGHT_WAVE, "Light Wave", 0, 0, 1, 1, false, true);

    modes[modeSelect::VOLUME] = new VolumeMode();
    modes[modeSelect::VOLUME]->init(modeSelect::VOLUME, "Volume    ", 50, 0, 100, 1, false, false);

    modes[modeSelect::AUDIO_BALANCE] = new AudioBalanceMode();
    modes[modeSelect::AUDIO_BALANCE]->init(modeSelect::AUDIO_BALANCE, "Audio <-> ", 50, 0, 100, 10, false, false);

    modes[modeSelect::AUDIO_PHASE] = new AudioPhaseMode();
    modes[modeSelect::AUDIO_PHASE]->init(modeSelect::AUDIO_PHASE, "Audio /-\\ ", 0, 0, 360, 10, false, true);

    modes[modeSelect::SOUND_WAVE] = new SoundWaveMode();
    modes[modeSelect::SOUND_WAVE]->init(modeSelect::SOUND_WAVE, "Sound Wave", 0, 0, 1, 1, false, true);

    ui.configureEncoder1(modes[modeSelect::BRIGHTNESS]->currentValue, modes[modeSelect::BRIGHTNESS]->minValue, modes[modeSelect::BRIGHTNESS]->maxValue, modes[modeSelect::BRIGHTNESS]->stepSize, modes[modeSelect::BRIGHTNESS]->invert, modes[modeSelect::BRIGHTNESS]->circleValues);

    this->currentMode = modes[modeSelect::FREQUENCY];

    //     ui.configureEncoder2(currentMode->minValue, currentMode->maxValue, currentMode->steps, currentMode->invert, currentMode->circleValues);

    delay(1000);
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

void ESPMachine::update()
{
    // void EncodersReader::configure1(currentValue, long minValue, long maxValue, long steps, bool invert, bool circleValues)
    ui.configureEncoder2(currentMode->currentValue, currentMode->minValue, currentMode->maxValue, currentMode->stepSize, currentMode->invert, currentMode->circleValues);

    xQueueSend(intercoreQueue, &currentMode->modeMessage, QUEUE_SEND_DELAY);

    // update encoders

    ui.updateDisplay(currentMode->label, currentMode->getValueString());
}

void ESPMachine::onEncoderClick(ButtonEventEnum button)
{
    if (button == BUTTON_1_EVENT)
    {
        setMode(modeSelect::BRIGHTNESS);
        currentMode->modeMessage.value = 0;
        //  Serial.println("..............");
        // Serial.println(currentMode->modeMessage.index);
        // Serial.println(currentMode->modeMessage.value);
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
