//
// Created by mw on 30.06.19.
//

#ifndef TEMP_WIFI_CLIENT_WIFINETWORKTASK_H
#define TEMP_WIFI_CLIENT_WIFINETWORKTASK_H


#include <string>
#include "Task.h"
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Log64.h>

struct NetConfig {
    IPAddress ip;
    IPAddress gateway;
    IPAddress subnet;
};

class WifiNetworkTask : public Task {
private:
    const std::unique_ptr<NetConfig> config;
    const std::string ssid;
    const std::string password;
    unsigned long tsLastAttemptOrLastConnected = 0;
    const unsigned long maxConnectMillis;
    std::vector<std::function<void(bool)>> statusListeners;
    std::vector<std::function<void(bool)>> statusChangedListeners;
    bool last_connected_status = false;

    static logger_t logger;

    void connectToWifiNetworkIfNeeded();

    bool connectIsTimedout();

    void connect();

public:
    WifiNetworkTask(const std::string &ssid, const std::string password, const long maxConnectMillis);

    WifiNetworkTask(const std::string &ssid, const std::string password, const long maxConnectMillis,
                    NetConfig netConfig);

    void setup() override;

    void run() override;

    void addStatusListener(std::function<void(bool)> &listener) {
        statusListeners.push_back(listener);
    }

    void addStatusChangedListener(std::function<void(bool)> &listener) {
        statusChangedListeners.push_back(listener);
    }

    bool isConnected() const {
        return WiFi.isConnected();
    }

    void configure() {
        if (config)
            WiFi.config(config->ip, config->gateway, config->subnet);
    }
};


#endif //TEMP_WIFI_CLIENT_WIFINETWORKTASK_H
