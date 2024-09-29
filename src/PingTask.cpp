//
// Created by mw on 07.09.24.
//

#include <ESP8266HTTPClient.h>
#include "PingTask.h"

logger_t PingTask::logger = LOGGER("PingTask");

void PingTask::run() {
    if (wifi_network_task->isConnected() && (ts_last_ping == 0 || millis() - ts_last_ping > ping_interval)) {
        ts_last_ping = millis();
        if (ping()) {
            on_success();
        } else {
            on_error();
        }
    }
}

bool PingTask::ping() {
    auto payload = generate_payload();
    return HomeAssistant::isSuccess(homeAssistant.setState(pingSensorEntityId, payload));
}

String PingTask::generate_payload() {
    return String("{\"state\": \"") + String(millis()) + "\"}";
}

void PingTask::setup() {

}
