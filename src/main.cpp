#include <Arduino.h>
#include <Dreamachine.h>
#include <DreamachineUI.h>
#include <DreamachineWaves.h>

void setup()
{

    Serial.begin(9600);

    // Serial.println("AAA");
    Dreamachine dreamachine;

    // Serial.println("BBB");

    // dreamachine.loadModes();
    // Serial.println("CCC");
    /*
        DreamachineUI ui;
        ui.setDreamachine(dreamachine);

        DreamachineWaves waves;
        waves.setDreamachine(dreamachine);
        */
}

void loop()
{
    delay(100);
}
