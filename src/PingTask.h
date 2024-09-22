//
// Created by mw on 07.09.24.
//

#ifndef IOT_PUMP_RF_ALERT_RECEIVER_PINGTASK_H
#define IOT_PUMP_RF_ALERT_RECEIVER_PINGTASK_H


#include <Task.h>
#include <WifiNetworkTask.h>
#include <BlinkingLed.h>

class PingTask : public Task {
public:
    void run() override;

private:
    void setup() override;

public:

    PingTask(const ulong pingInterval, WifiNetworkTask *wifiNetworkTask, const String pingUrl, const String token,
             std::function<void()> on_error, std::function<void()> on_success)
            : ping_interval(pingInterval), wifi_network_task(wifiNetworkTask), ping_url(pingUrl), token(token),
                on_error(on_error), on_success(on_success) {}

private:
    ulong ts_last_ping = 0;
    const ulong ping_interval;
    WifiNetworkTask *wifi_network_task;
    const String ping_url;
    const String token;

    String generate_payload();

    bool ping();

    void handle_error();

    static logger_t logger;

    std::function<void()> on_error;
    std::function<void()> on_success;
};


#endif //IOT_PUMP_RF_ALERT_RECEIVER_PINGTASK_H
