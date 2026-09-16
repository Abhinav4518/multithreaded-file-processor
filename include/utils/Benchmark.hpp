#pragma once

#include <chrono>
#include <utility>

class Benchmark {

public:

    template <typename Function>
    static auto measure(
        Function&& function
    ) {

        auto start =
            std::chrono::steady_clock::now();

        auto result =
            std::forward<Function>(function)();

        auto end =
            std::chrono::steady_clock::now();

        double milliseconds =
            std::chrono::duration<double, std::milli>(
                end - start
            ).count();

        return std::make_pair(
            std::move(result),
            milliseconds
        );
    }
};