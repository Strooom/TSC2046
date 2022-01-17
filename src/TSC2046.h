#pragma once
#include <Arduino.h>
#include <SPI.h>

class TSC2046 {
  public:
    TSC2046(uint32_t chipSelectPin);        // constructor with SPI ChipSelect pin - no further initialization is needed

    void sample();        // performs all Analog-to-Digital conversions. Call before callng getX, getY, isTouched or getTemperature

    int16_t getX();
    int16_t getY();
    bool getIsTouched();
    float getTemperature();
    uint32_t tRaw{};        // temperature

  private:
    uint32_t chipSelectPin{};
    
    static constexpr uint8_t getTemperatureRaw{0x85};
    static constexpr uint8_t getZ1Raw{0xB1};
    static constexpr uint8_t getZ2Raw{0xC1};
    static constexpr uint8_t getXRaw{0xD1};
    static constexpr uint8_t getYRaw{0x91};
    static constexpr uint8_t endConversion{0x00};
    uint32_t xRaw{};         // x-axis
    uint32_t yRaw{};         // y-axis
    uint32_t z1Raw{};        // z-axis ??
    uint32_t z2Raw{};        // z-axis ??

    static constexpr uint32_t zRawThreshold{200U};          // z1/z2 values lower than this are considered 'noise' and to be ignored
    static constexpr uint32_t touchThreshold{3000U};        // above this value we have 'touch'
    static constexpr uint32_t debounceCountMax{8U};         //
    uint32_t debounceCounter{0};

    int16_t lastX{0};
    int16_t lastY{0};
    bool isTouched{false};
};