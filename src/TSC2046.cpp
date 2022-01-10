#include "TSC2046.h"

TSC2046::TSC2046(uint32_t theChipSelectPin) : chipSelectPin(theChipSelectPin) {
    pinMode(chipSelectPin, OUTPUT);
}

void TSC2046::sample() {
    digitalWrite(chipSelectPin, LOW);
    SPI.beginTransaction(SPISettings(2000000U, MSBFIRST, SPI_MODE0));        // set the SPI in the correct mode

    // First, take a number of samples to measure temperature and determine if we have touch
    SPI.transfer(getTemperatureRaw);                                     //
    tRaw  = static_cast<uint32_t>(SPI.transfer16(getZ1Raw));             // I don't need temp, but I do it as a sort of warming up / stabilizing of the AD convertor
    z1Raw = static_cast<uint32_t>(SPI.transfer16(getZ2Raw));             //
    z2Raw = static_cast<uint32_t>(SPI.transfer16(endConversion));        //

    // 1. Filter noisy measurements if any
    if (z1Raw < zRawThreshold) {
        z1Raw = 0U;
    }

    if (z2Raw > (32768U - zRawThreshold)) {
        z2Raw = 32768U;
    }

    // 2. Now debounce this touch, to avoid many fast presses and releases..
    isTouched = ((32768 - (z2Raw - z1Raw)) > touchThreshold);

    //if ((32768 - (z2Raw - z1Raw)) > touchThreshold) 
    // {
    //     if (debounceCounter < debounceCountMax) {
    //         debounceCounter++;
    //     } else {
    //         if (!isTouched) {
    //             isTouched = true;
    //             theLog.output(subSystems::display, loggingLevel::Debug, "press...");
    //         }
    //     }
    // } else {
    //     if (debounceCounter > 0) {
    //         debounceCounter--;
    //     } else {
    //         if (isTouched) {
    //             isTouched = false;
    //             theLog.output(subSystems::display, loggingLevel::Debug, "release...");
    //         }
    //     }
    // }

    // Then, if we have touch, it makes sense to sample X and Y as well

    if (isTouched) {
        SPI.transfer(getTemperatureRaw);                              //
        tRaw = static_cast<uint32_t>(SPI.transfer16(getXRaw));        // I don't need temp, but I do it as a sort of warming up / stabilizing of the AD convertor
        xRaw = static_cast<uint32_t>(SPI.transfer16(getYRaw));
        yRaw = static_cast<uint32_t>(SPI.transfer16(endConversion));

        // xRaw and yRaw have a range of 0.. 32768
        // on our display, yRaw runs right to left, io top to bottom
        // xRaw runs top to bottom io left to right
        // -> some transformation is needed
        lastX = 480 - (yRaw / 68);        // yRaw range is 0 - 32768. Reduce to 0 - 480 by dividing by 68. Swap left and right
        lastY = xRaw / 102;               // yRaw range is 0 - 32768. Reduce to 0 - 320 by dividing by 102.

    }
    SPI.endTransaction();        // stop SPI transmission
    digitalWrite(chipSelectPin, HIGH);
}

int16_t TSC2046::getX() {
    return lastX;
}

int16_t TSC2046::getY() {
    return lastY;
}

bool TSC2046::getIsTouched() {
    return isTouched;
}

float TSC2046::getTemperature() {
    return 0.0F;
}
