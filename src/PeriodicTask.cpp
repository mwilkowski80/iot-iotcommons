//
// Created by mw on 18.01.20.
//

#include "PeriodicTask.h"
#include <Arduino.h>
#include <Log64.h>

logger_t PeriodicTask::logger = LOGGER("PeriodicTask");

void PeriodicTask::setup() {

}

void PeriodicTask::run() {
  if (this->ts_last_run + this->interval_millis < millis()) {
    logger("PeriodicTask threshold passed. About to invoke periodic_function()");
    periodic_function();
    this->ts_last_run = millis();
  }
}
