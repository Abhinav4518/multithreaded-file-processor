#pragma once

#include "ThreadSafeQueue.hpp"

#include <atomic>
#include <cstddef>
#include <functional>
#include <future>
#include <memory>
#include <stdexcept>
#include <thread>
#include <type_traits>
#include <utility>
#include <vector>

class ThreadPool {

private:

    ThreadSafeQueue<std::function<void()>> tasks_;

    std::vector<std::thread> workers_;

    std::atomic<bool> stopping_{false};

    void workerLoop() {

        while (true) {

            auto task = tasks_.waitAndPop();

            if (!task.has_value()) {
                return;
            }

            try {
                (*task)();
            }
            catch (...) {
                // Exceptions are captured by std::promise/std::future
                // when submit() is used.
            }
        }
    }

public:

    explicit ThreadPool(std::size_t numberOfThreads) {

        if (numberOfThreads == 0) {
            throw std::invalid_argument(
                "Thread count must be greater than zero"
            );
        }

        workers_.reserve(numberOfThreads);

        for (std::size_t i = 0; i < numberOfThreads; ++i) {

            workers_.emplace_back(
                [this]() {
                    workerLoop();
                }
            );
        }
    }

    template <typename Function, typename... Args>
    auto submit(Function&& function, Args&&... args)
        -> std::future<std::invoke_result_t<Function, Args...>>
    {

        using ReturnType =
            std::invoke_result_t<Function, Args...>;

        auto task =
            std::make_shared<
                std::packaged_task<ReturnType()>
            >(
                std::bind(
                    std::forward<Function>(function),
                    std::forward<Args>(args)...
                )
            );

        std::future<ReturnType> result =
            task->get_future();

        tasks_.push(
            [task]() {
                (*task)();
            }
        );

        return result;
    }

    void shutdown() {

        if (stopping_.exchange(true)) {
            return;
        }

        tasks_.close();

        for (auto& worker : workers_) {

            if (worker.joinable()) {
                worker.join();
            }
        }
    }

    ~ThreadPool() {
        shutdown();
    }

    ThreadPool(const ThreadPool&) = delete;
    ThreadPool& operator=(const ThreadPool&) = delete;
};