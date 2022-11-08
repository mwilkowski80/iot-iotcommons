#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#define DOCTEST_CONFIG_SUPER_FAST_ASSERTS
#include "doctest.h"
#include "CollectPublishTask.h"
#include "MockedTimer.h"
#include <memory>
#include <array>

struct TestCase {
    long timer_counter;
    CollectResult<long> collect_result;
    bool publish_result;
    int collect_counter;
    int publish_counter;
};

class CollectPublishTaskMock {
private:
    MockedTimer timer;
    long collect_func_counter = 0L;
    long publish_func_counter = 0L;
    bool publish_func_result = false;
    CollectResult<long> collect_func_result;
    std::function<CollectResult<long>()> collect_func;
    std::function<bool(long)> publish_func;
    std::function<long()> get_millis_func;
    std::unique_ptr<CollectPublishTask<long>> collect_task;

public:
    CollectPublishTaskMock(long collect_threshold, long collect_attempt_threshold,
                           long publish_threshold) :
            timer(0L, 0L),
            collect_func_result({CollectResult<long>::SUCCESS, 0L}) {

        collect_func = [this]() -> CollectResult<long> {
            collect_func_counter++;
            return collect_func_result;
        };
        publish_func = [this](long l) -> bool {
            publish_func_counter++;
            return publish_func_result;
        };
        get_millis_func = timer.get_func();
        collect_task.reset(
                new CollectPublishTask<long>(
                        collect_func, publish_func, get_millis_func,
                        collect_threshold, publish_threshold, collect_attempt_threshold));
    }

    void set_timer(long timer_counter) {
        timer.set_counter(timer_counter);
    }

    void maybe_collect() {
        collect_task->maybe_collect();
    }

    void maybe_publish() {
        collect_task->maybe_publish();
    }

    void setup() {
        collect_task->setup();
    }

    long get_collect_func_counter() {
        return collect_func_counter;
    }

    long get_publish_func_counter() {
        return publish_func_counter;
    }

    void set_publish_func_result(bool publish_func_result) {
        this->publish_func_result = publish_func_result;
    }

    void set_collect_func_result(CollectResult<long> collect_func_result) {
        this->collect_func_result = collect_func_result;
    }

};

template<std::size_t case_count>
void test_cases(std::array<TestCase, case_count> cases,
                long collect_threshold, long collect_attempt_threshold, long publish_threshold) {
    CollectPublishTaskMock mock{collect_threshold, collect_attempt_threshold, publish_threshold};
    mock.setup();

    for (auto test_case: cases) {
        mock.set_timer(test_case.timer_counter);
        mock.set_collect_func_result(test_case.collect_result);
        mock.set_publish_func_result(test_case.publish_result);
        mock.maybe_collect();
        mock.maybe_publish();
        CHECK(mock.get_collect_func_counter() == test_case.collect_counter);
        CHECK(mock.get_publish_func_counter() == test_case.publish_counter);
    }
}

TEST_CASE("test collect 1") {
    test_cases(std::array<TestCase, 1>{
            { 100L, {CollectResult<long>::SUCCESS, 1L}, true, 1, 1},
        }, 300L, 100L, 1000L);
}

TEST_CASE("test collect 2") {
    test_cases(std::array<TestCase, 3>{
            TestCase{ 100L, {CollectResult<long>::OTHER_ERROR, 1L}, true, 1, 0},
            TestCase{ 110L, {CollectResult<long>::OTHER_ERROR, 1L}, true, 1, 0},
            TestCase{ 120L, {CollectResult<long>::SUCCESS, 1L}, true, 1, 0}
    }, 300L, 100L, 1000L);
}

TEST_CASE("test collect 3") {
    test_cases(std::array<TestCase, 20>{
            TestCase{ 100L, {CollectResult<long>::OTHER_ERROR, 1L}, true, 1, 0},
            TestCase{ 110L, {CollectResult<long>::OTHER_ERROR, 1L}, true, 1, 0},
            TestCase{ 210L, {CollectResult<long>::OTHER_ERROR, 1L}, true, 2, 0},
            TestCase{ 220L, {CollectResult<long>::SUCCESS, 1L}, true, 2, 0},
            TestCase{ 230L, {CollectResult<long>::SUCCESS, 1L}, true, 2, 0},
            TestCase{ 320L, {CollectResult<long>::SUCCESS, 1L}, false, 3, 1},
            TestCase{ 330L, {CollectResult<long>::SUCCESS, 1L}, true, 3, 2},
            TestCase{ 340L, {CollectResult<long>::SUCCESS, 1L}, true, 3, 2},
            TestCase{ 430L, {CollectResult<long>::SUCCESS, 1L}, true, 3, 2},
            TestCase{ 630L, {CollectResult<long>::OTHER_ERROR, 1L}, true, 4, 2},
            TestCase{ 640L, {CollectResult<long>::OTHER_ERROR, 1L}, true, 4, 2},
            TestCase{ 740L, {CollectResult<long>::OTHER_ERROR, 1L}, true, 5, 2},
            TestCase{ 800L, {CollectResult<long>::OTHER_ERROR, 1L}, true, 5, 2},
            TestCase{ 850L, {CollectResult<long>::SUCCESS, 1L}, true, 6, 2},
            TestCase{ 1500L, {CollectResult<long>::SUCCESS, 1L}, true, 7, 3},
            TestCase{ 1810L, {CollectResult<long>::SUCCESS, 1L}, true, 8, 3},
            TestCase{ 2120L, {CollectResult<long>::SUCCESS, 2L}, false, 9, 4},
            TestCase{ 2130L, {CollectResult<long>::SUCCESS, 2L}, false, 9, 5},
            TestCase{ 2140L, {CollectResult<long>::SUCCESS, 2L}, true, 9, 6},
            TestCase{ 2150L, {CollectResult<long>::SUCCESS, 2L}, false, 9, 6},
    }, 300L, 100L, 1000L);
}
