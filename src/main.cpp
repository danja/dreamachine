#include <Arduino.h>
#include <Dreamachine.h>
#include <DreamachineUI.h>
#include <DreamachineWaves.h>

void setup()
{
    //  delay(500);
    Serial.begin(115200);

    Dreamachine dreamachine;

    DreamachineUI ui;
    ui.setDreamachine(dreamachine);

    DreamachineWaves waves;
    waves.setDreamachine(dreamachine);
}

void loop()
{
}
