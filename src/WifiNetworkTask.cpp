//
// Created by mw on 30.06.19.
//

#include "../include/WifiNetworkTask.h"

logger_t WifiNetworkTask::logger = LOGGER("WifiNetworkTask");

void WifiNetworkTask::setup() {
  WiFi.mode(WIFI_STA);
  connectToWifiNetworkIfNeeded();
}

void WifiNetworkTask::run() {
  connectToWifiNetworkIfNeeded();

  bool connectedStatus = isConnected();
  for (auto &listener: listeners)
    listener->onStatus(connectedStatus);
}

void WifiNetworkTask::connectToWifiNetworkIfNeeded() {
  if (!isConnected() && connectIsTimedout())
    connect();
}

WifiNetworkTask::WifiNetworkTask(const std::string &ssid, const std::string password, const long maxConnectMillis)
    : ssid(ssid),
      password(password), maxConnectMillis(maxConnectMillis) {}

WifiNetworkTask::WifiNetworkTask(const std::string &ssid, const std::string password, const long maxConnectMillis,
                                 NetConfig config)
    : ssid(ssid),
      password(password), maxConnectMillis(maxConnectMillis),
      config(new NetConfig(config)) {}

bool WifiNetworkTask::connectIsTimedout() {
  return tsLastAttemptOrLastConnected == 0 || tsLastAttemptOrLastConnected + maxConnectMillis < millis();
}

void WifiNetworkTask::connect() {
  logger("New attempt to connect to Wifi network");
  configure();
  WiFi.begin(ssid.c_str(), password.c_str());
  tsLastAttemptOrLastConnected = millis();
}
