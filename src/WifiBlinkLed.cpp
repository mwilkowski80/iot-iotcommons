//
// Created by mw on 01.07.19.
//

#include "../include/WifiBlinkLed.h"
#include <Arduino.h>
#include <Log64.h>

logger_t WifiBlinkLed::logger = LOGGER("WifiBlinkLed");

void WifiBlinkLed::onStatus(bool connected) {
  if (this->connected != connected) {
    LOG64_SET(String("Wifi connected: ") + connected);
    LOG64_NEW_LINE;
  }
  this->connected = connected;
  if (!connected)
    applyBlinkingStatus();
}

void WifiBlinkLed::applyBlinkingStatus() {
  led->setConfig({LedStatus::ON, millis() + 600, 200, 200});
}
