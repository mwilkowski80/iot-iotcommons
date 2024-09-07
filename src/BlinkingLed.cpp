//
// Created by mw on 30.06.19.
//

#include "../include/BlinkingLed.h"
#include <Log64.h>

logger_t BlinkingLed::logger = LOGGER("BlinkingLed");


void BlinkingLed::setup() {
    pinMode(ledNum, OUTPUT);
}

void BlinkingLed::run() {
    if (millis() >= currentConfig.exitMillis) {
        setLedStatus(currentConfig.exit);
    } else {
        maybeSwitch();
    }
}

void BlinkingLed::setLedStatus(LedStatus status) {
    currentStatus = status;
    digitalWrite(ledNum, status == LedStatus::OFF ? ledOffPinSignal : ledOnPinSignal);
}

void BlinkingLed::maybeSwitch() {
    if (shouldSwitch())
        switchLed();
}

bool BlinkingLed::shouldSwitch() {
    if (currentStatus == LedStatus::OFF) {
        unsigned long tsShouldSwitch = currentConfig.offInterval + tsLastSwitch;
        return millis() > tsShouldSwitch;
    } else {
        unsigned long tsShouldSwitch = currentConfig.onInterval + tsLastSwitch;
        return millis() > tsShouldSwitch;
    }
}

void BlinkingLed::switchLed() {
    setLedStatus(currentStatus == LedStatus::ON ? LedStatus::OFF : LedStatus::ON);
    tsLastSwitch = millis();
}

void BlinkingLed::setConfig(const BlinkingLedConfig &param) {
    currentConfig = param;
}
