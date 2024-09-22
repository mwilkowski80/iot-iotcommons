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
    HTTPClient http;
    WiFiClient wifi_client;

    http.begin(wifi_client, ping_url);
    if (token != "") {
        http.addHeader("Authorization", "Bearer " + token);
    }
    http.addHeader("Content-Type", "application/json");
    http.addHeader("Accept", "application/json");
    auto payload = generate_payload();

    logger("Sending ping to " + ping_url + ", payload: " + payload);
    auto result = http.POST(payload);
    logger("Ping error code: " + String(result));
    return result >= 200 && result < 300;
}

String PingTask::generate_payload() {
    return String("{\"state\": \"") + String(millis()) + "\"}";
}

void PingTask::setup() {

}
