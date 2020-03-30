//
// Created by mw on 30.03.2020.
//

#ifndef IOTCOMMONS_PERIODICRESTART_H
#define IOTCOMMONS_PERIODICRESTART_H


#include <Arduino.h>
#include "Task.h"

class PeriodicRestart: public Task {
private:
  unsigned long ts_timer_threshold;
  const unsigned long timer_period_millis;

public:
  PeriodicRestart(const unsigned long timer_period_millis) : timer_period_millis(timer_period_millis) {}

  void setup() override {
    reset();
  }

  void reset() {
    ts_timer_threshold = millis() + timer_period_millis;
  }

  void run() override {
    if (millis() > ts_timer_threshold)
      ESP.restart();
  }
};


#endif //IOTCOMMONS_PERIODICRESTART_H
