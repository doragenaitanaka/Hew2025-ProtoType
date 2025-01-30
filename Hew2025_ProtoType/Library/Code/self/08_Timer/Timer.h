/**	@file 	Timer.h
*	@brief 	タイマー
*	@date	2025/01/30
*/
#pragma once
#include <chrono>

class Timer {
public:
    Timer() : startTime(std::chrono::steady_clock::now()) {}

    void Reset() {
        startTime = std::chrono::steady_clock::now();
    }

    double Elapsed() const {
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> duration = end - startTime;
        return duration.count();
    }

private:
    std::chrono::time_point<std::chrono::steady_clock> startTime;
};
