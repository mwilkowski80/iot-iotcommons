//
// Created by mw on 01.07.19.
//

#ifndef TEMP_WIFI_CLIENT_WIFIBLINKLED_H
#define TEMP_WIFI_CLIENT_WIFIBLINKLED_H


#include "BlinkingLed.h"

class WifiBlinkLed : public WifiNetworkListener {
private:
  BlinkingLed *const led;
  bool connected = false;

public:
  WifiBlinkLed(BlinkingLed *aLed) : led(aLed) {}

  virtual void onStatus(bool connected);

  void applyBlinkingStatus();
};


#endif //TEMP_WIFI_CLIENT_WIFIBLINKLED_H
