//
// Created by mw on 30.06.19.
//

#ifndef TEMP_WIFI_CLIENT_TASK_H
#define TEMP_WIFI_CLIENT_TASK_H

class Task {
public:
  virtual ~Task() {}
  virtual void setup() = 0;
  virtual void run() = 0;
};

#endif //TEMP_WIFI_CLIENT_TASK_H
