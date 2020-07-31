//
// Created by mw on 27.04.2020.
//

#ifndef PIR_COLLECTPUBLISHTASK_H
#define PIR_COLLECTPUBLISHTASK_H

#include <Arduino.h>
#include <Task.h>

template<class value_type>
class CollectPublishTask : public Task {
public:
  struct CollectResult {
    enum ErrorCode {
      SUCCESS,
      OTHER_ERROR
    };

    ErrorCode error_code;
    value_type value;
  };

private:
  const std::function<CollectResult()> collect;
  const std::function<bool(value_type)> publish;

  const unsigned long ts_attempt_threshold;
  const unsigned long ts_collect_threshold;
  const unsigned long ts_publish_threshold;
  value_type sensor_data;
  unsigned long ts_last_attempt = 0;
  unsigned long ts_last_collect = 0;
  unsigned long ts_last_publish = 0;
  bool dirty = false;

public:
  CollectPublishTask(const std::function<CollectResult()> collect, const std::function<bool(value_type)> publish,
                     const unsigned long ts_collect_threshold, const unsigned long ts_publish_threshold,
                     const unsigned long ts_attempt_threshold) : collect(
      collect), publish(publish), ts_collect_threshold(ts_collect_threshold), ts_publish_threshold(
      ts_publish_threshold), ts_attempt_threshold(ts_attempt_threshold) {}

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
    bool should_collect = ts_last_collect == 0 || ts_last_collect + ts_collect_threshold < millis();
    bool should_attempt_to_collect = ts_last_attempt == 0 || ts_last_attempt + ts_attempt_threshold < millis();
    if (should_collect && should_attempt_to_collect) {
      ts_last_attempt = millis();
      auto new_result = collect();
      if (new_result.error_code == CollectResult::SUCCESS) {
        ts_last_collect = millis();
        auto new_sensor_data = new_result.value;

        if (new_sensor_data != sensor_data)
          dirty = true;
        sensor_data = new_sensor_data;

      }
    }
  }
};


#endif //PIR_COLLECTPUBLISHTASK_H
