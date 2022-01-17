#include <Arduino.h>
#include "TSC2046.h"
#include <SPI.h>
#include <unity.h>

TSC2046 theTouchController(20);

// #######################################
// ### UnitTest SetUp() and TearDown() ###
// #######################################

void setUp(void) {
    SPI.begin();
}

void tearDown(void) {
}


// #######################################
// ### UnitTests                       ###
// #######################################

void test_getTemperature(void) {
    TEST_ASSERT_EQUAL(0.0F, theTouchController.getTemperature());
}


// #######################################
// ### TestRunner Framework            ###
// #######################################

void setup() {
    delay(2000);
    UNITY_BEGIN();
    RUN_TEST(test_getTemperature);
    UNITY_END();
}

void loop() {
// Do nothing, as tests only run once
}
