//
// Created by mw on 30.06.19.
//

#ifndef TEMP_WIFI_CLIENT_BLINKINGLED_H
#define TEMP_WIFI_CLIENT_BLINKINGLED_H

#include "Task.h"
#include "WifiNetworkTask.h"

enum class LedStatus {
  ON, OFF
};

typedef struct {
  LedStatus exit;
  long exitMillis;
  long onInterval;
  long offInterval;
} BlinkingLedConfig;

class BlinkingLed : public Task {
private:
  const int ledNum;
  LedStatus currentStatus = LedStatus::OFF;
  long tsLastSwitch = 0;
  constexpr static BlinkingLedConfig DEFAULT_CONFIG = {LedStatus::ON, 0, 0, 0};
  BlinkingLedConfig currentConfig = DEFAULT_CONFIG;

  void setLedStatus(LedStatus status);

  void maybeSwitch();

  bool shouldSwitch();

  void switchLed();

public:
  BlinkingLed(const int ledNum);

  void setup() override;

  void run() override;

  void setConfig(const BlinkingLedConfig &param);
};


#endif //TEMP_WIFI_CLIENT_BLINKINGLED_H
