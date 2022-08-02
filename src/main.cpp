#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "AiEsp32RotaryEncoder.h"
#include "AiEsp32RotaryEncoderNumberSelector.h"

#include <TinyDisplay.h>

const int LED_L = 32;
const int LED_R = 33;

// PWM properties
const int freq = 5000;
const int ledChannel = 0;
const int resolution = 8;

const int ENCODER_1_CLK = 34;
const int ENCODER_1_DT = 35;
const int ENCODER_1_SW = 16;

const int ENCODER_2_CLK = 36;
const int ENCODER_2_DT = 39;
const int ENCODER_2_SW = 4;

const int ENCODER_1_STEPS = 10;
const int ENCODER_2_STEPS = 10;

AiEsp32RotaryEncoder *encoder1 = new AiEsp32RotaryEncoder(ENCODER_1_CLK, ENCODER_1_DT, ENCODER_1_SW, -1, ENCODER_1_STEPS);
AiEsp32RotaryEncoder *encoder2 = new AiEsp32RotaryEncoder(ENCODER_2_CLK, ENCODER_2_DT, ENCODER_2_SW, -1, ENCODER_2_STEPS);
AiEsp32RotaryEncoderNumberSelector numberSelector1 = AiEsp32RotaryEncoderNumberSelector();
AiEsp32RotaryEncoderNumberSelector numberSelector2 = AiEsp32RotaryEncoderNumberSelector();

TinyDisplay tinyDisplay = TinyDisplay();

// forward declarations
void IRAM_ATTR readEncoderISR_1();
void IRAM_ATTR readEncoderISR_2();

void setup()
{
    Serial.begin(115200);

    tinyDisplay.init();

    tinyDisplay.drawLabel("Starting...");
    tinyDisplay.drawValue("0%");
    delay(500);
    tinyDisplay.drawValue("100%");
    delay(500);
    tinyDisplay.drawLabel("Working");
    //////////////////////////////////////////////

    ledcSetup(ledChannel, freq, resolution);

    // attach the channel to the GPIO to be controlled
    ledcAttachPin(LED_L, ledChannel);
    ledcAttachPin(LED_R, ledChannel);

    ////////////////////////////////
    pinMode(ENCODER_1_CLK, INPUT);
    pinMode(ENCODER_1_DT, INPUT);
    pinMode(ENCODER_1_SW, INPUT);

    pinMode(ENCODER_2_CLK, INPUT);
    pinMode(ENCODER_2_DT, INPUT);
    pinMode(ENCODER_2_SW, INPUT);

    encoder1->begin();
    encoder1->setup(readEncoderISR_1);
    numberSelector1.attachEncoder(encoder1);

    numberSelector1.setRange(0.0, 100.0, 1, false, 0);
    numberSelector1.setValue(25);

    encoder2->begin();
    encoder2->setup(readEncoderISR_2);
    numberSelector2.attachEncoder(encoder2);

    numberSelector2.setRange(0.0, 100.0, 1, false, 0);
    numberSelector2.setValue(25);
}

void loop()
{
    // increase the LED brightness
    for (int dutyCycle = 0; dutyCycle <= 255; dutyCycle++)
    {
        //  Serial.print(dutyCycle);
        // changing the LED brightness with PWM
        ledcWrite(ledChannel, dutyCycle);
        delay(3);
    }
    ////////////////////////////

    if (encoder1->encoderChanged())
    {
        Serial.print(numberSelector1.getValue());
        float value1 = numberSelector1.getValue();
        Serial.println(" 1 ");
        String value1String = String(value1, 0);
        tinyDisplay.drawValue(value1String);
    }

    if (encoder1->isEncoderButtonClicked())
    {
        Serial.print("1 Selected value is ");
        Serial.print(numberSelector1.getValue(), 1);
        Serial.println(" ***********************");
    }
    if (encoder2->encoderChanged())
    {
        Serial.println(" 2 ");
        Serial.print(numberSelector2.getValue());
        Serial.println(" ");
    }

    if (encoder2->isEncoderButtonClicked())
    {
        Serial.print("Selected 2 value is ");
        Serial.print(numberSelector2.getValue(), 1);
        Serial.println(" ***********************");
    }
}

void IRAM_ATTR readEncoderISR_1()
{
    encoder1->readEncoder_ISR();
}

void IRAM_ATTR readEncoderISR_2()
{
    encoder2->readEncoder_ISR();
}