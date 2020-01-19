//
// Created by mw on 30.06.19.
//

#ifndef TEMP_WIFI_CLIENT_TASKMANAGER_H
#define TEMP_WIFI_CLIENT_TASKMANAGER_H

#include <vector>
#include <memory>
#include <algorithm>
#include "Task.h"

class TaskManager {
private:
  std::vector<std::unique_ptr<Task>> tasks;

public:
  TaskManager() {}
  TaskManager(std::vector<std::unique_ptr<Task>>&& atasks): tasks(std::move(atasks)) {}

  void setup() {
    for (auto& task: tasks)
      task->setup();
  }

  void run() {
    for (auto& task: tasks)
      task->run();
  }

  void push_back(Task* task) {
    tasks.push_back(std::unique_ptr<Task>(task));
  }
};


#endif //TEMP_WIFI_CLIENT_TASKMANAGER_H
