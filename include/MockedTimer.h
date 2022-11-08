//
// Created by mw on 08.11.22.
//

#ifndef IOT_IOTCOMMONS_MOCKEDTIMER_H
#define IOT_IOTCOMMONS_MOCKEDTIMER_H

#include <string>
#include <functional>

class MockedTimer {
private:
    long counter;
    long step;

public:
    MockedTimer(long counter, long step): counter(counter), step(step) {}

    inline std::function<long()> get_func() {
        return [this]() -> long {
            long curr_value = counter;
            counter += step;
            return curr_value;
        };
    }

    inline void set_counter(long counter) {
        this->counter = counter;
    }
};

#endif //IOT_IOTCOMMONS_MOCKEDTIMER_H
