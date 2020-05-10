//
// Created by mw on 18.01.20.
//

#ifndef IOTCOMMONS_PERIODIC_TASK_H
#define IOTCOMMONS_PERIODIC_TASK_H

#include <Task.h>
#include <functional>
#include <Log64.h>

class PeriodicTask : public Task {
private:
  const unsigned long interval_millis;
  unsigned long ts_last_run;
  const std::function<void()> periodic_function;
  static logger_t logger;

public:
  PeriodicTask(const long intervalMillis, const std::function<void()> &periodic_function) :
      interval_millis(intervalMillis), ts_last_run(0), periodic_function(periodic_function) {}

  void setup() override;

  void run() override;
};


#endif //IOTCOMMONS_PERIODIC_TASK_H
