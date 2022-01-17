#include <Arduino.h>
#include "TSC2046.h"
#include <SPI.h>

constexpr uint32_t chipSelectPin{32U};        // On our hardware, this is GPIO 32, maybe different on other hardware setups
TSC2046 theTouchScreen(chipSelectPin);        // create a global object holding the driver data

void setup() {
    Serial.begin(115200);
    Serial.flush();
    Serial.println("Testing TSC2046");

    SPI.begin();
}

void loop() {
    theTouchScreen.sample();

    if (theTouchScreen.getIsTouched()) {
        uint32_t x = theTouchScreen.getX();
        uint32_t y = theTouchScreen.getY();
        Serial.print("touched on x = ");
        Serial.print(x);
        Serial.print(", y = ");
        Serial.println(y);
    } else {
        Serial.println("not touched");
    }

    delay(500);
}