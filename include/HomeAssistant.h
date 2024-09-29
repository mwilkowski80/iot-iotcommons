//
// Created by mw on 27.09.24.
//

#ifndef IOT_HOME_TERMOMETER_HOMEASSISTANT_H
#define IOT_HOME_TERMOMETER_HOMEASSISTANT_H

#include <Arduino.h>
#include <Log64.h>

#include <utility>
#include <ESP8266HTTPClient.h>

class HomeAssistant {
private:
    const String token;
    const String baseUrl;
    logger_t logger;

public:
    HomeAssistant(String baseUrl, String token) :
            token(std::move(token)), baseUrl(std::move(baseUrl)), logger(LOGGER("HomeAssistant")) {}

    int setState(const String &entityId, const String &state);
    int getState(const String &entityId, String* output);

    int setInputNumber(const String &entityId, const float value);

    void addHeaders(HTTPClient& client) {
        if (token != "") {
            client.addHeader("Authorization", "Bearer " + token);
        }
        client.addHeader("Content-Type", "application/json");
        client.addHeader("Accept", "application/json");
    }

    static bool isSuccess(int errorCode) {
        return errorCode >= 200 && errorCode < 300;
    }
};


#endif //IOT_HOME_TERMOMETER_HOMEASSISTANT_H
