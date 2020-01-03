#pragma once

#include "spdlog/spdlog.h"

#include <functional>

class Task
{
    public:
        Task(std::function<void()> func);
        ~Task();

        // overload function call
        void operator()()
        {
            spdlog::get("console")->debug("TaskProcessor::operator() - Start.");
            mFunc();
            spdlog::get("console")->debug("TaskProcessor::operator() - Done.");

            return;
        }

    private:
        std::function<void()> mFunc;
};