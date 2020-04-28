//
// Created by mw on 27.04.2020.
//

#ifndef PIR_COLLECTPUBLISHTASK_H
#define PIR_COLLECTPUBLISHTASK_H

#include <Arduino.h>
#include <Task.h>

class CollectPublishTask : public Task {
private:
  const std::function<String()> collect;
  const std::function<bool(String)> publish;

  const unsigned long ts_collect_threshold;
  const unsigned long ts_publish_threshold;
  String sensor_data;
  unsigned long ts_last_collect = 0;
  unsigned long ts_last_publish = 0;
  bool dirty = false;

public:
  CollectPublishTask(const std::function<String()> collect, const std::function<bool(String)> publish,
                     const unsigned long ts_collect_threshold, const unsigned long ts_publish_threshold) : collect(
      collect), publish(publish), ts_collect_threshold(ts_collect_threshold), ts_publish_threshold(
      ts_publish_threshold) {}

  void setup() override {
  }

  void run() override {
    maybe_collect();
    maybe_publish();
  }

  void maybe_publish() {
    if (ts_last_publish == 0 || dirty || ts_last_publish + ts_publish_threshold < millis()) {
      if (publish(sensor_data)) {
        ts_last_publish = millis();
        dirty = false;
      }
    }
  }

  void maybe_collect() {
    if (ts_last_collect == 0 || ts_last_collect + ts_collect_threshold < millis()) {
      String new_sensor_data = collect();
      ts_last_collect = millis();

      if (new_sensor_data != sensor_data)
        dirty = true;
      sensor_data = new_sensor_data;
    }
  }
};


#endif //PIR_COLLECTPUBLISHTASK_H
