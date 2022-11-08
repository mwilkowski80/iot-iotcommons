//
// Created by mw on 08.11.22.
//

#ifndef IOT_IOTCOMMONS_ARDUINO_NATIVE_H
#define IOT_IOTCOMMONS_ARDUINO_NATIVE_H

#ifdef _PIO_ENV_NATIVE_

#include <chrono>

inline long millis() {
  using namespace std::chrono;
  return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

#endif // _PIO_ENV_NATIVE_

#endif //IOT_IOTCOMMONS_ARDUINO_NATIVE_H
