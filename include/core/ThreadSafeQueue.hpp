#pragma once

#include <condition_variable>
#include <mutex>
#include <optional>
#include <queue>

template <typename T>
class ThreadSafeQueue {

private:
    std::queue<T> queue_;
    mutable std::mutex mutex_;
    std::condition_variable condition_;
    bool closed_ = false;

public:

    void push(T value) {

        {
            std::lock_guard<std::mutex> lock(mutex_);

            if (closed_) {
                return;
            }

            queue_.push(std::move(value));
        }

        condition_.notify_one();
    }

    std::optional<T> waitAndPop() {

        std::unique_lock<std::mutex> lock(mutex_);

        condition_.wait(lock, [this]() {
            return !queue_.empty() || closed_;
        });

        if (queue_.empty()) {
            return std::nullopt;
        }

        T value = std::move(queue_.front());
        queue_.pop();

        return value;
    }

    void close() {

        {
            std::lock_guard<std::mutex> lock(mutex_);
            closed_ = true;
        }

        condition_.notify_all();
    }

    bool empty() const {

        std::lock_guard<std::mutex> lock(mutex_);

        return queue_.empty();
    }
};