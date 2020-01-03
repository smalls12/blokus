#pragma once

#include "Task.hpp"

#include <atomic>
#include <thread>

class TaskProcessor
{
    public:
        TaskProcessor(Task task);
        ~TaskProcessor();

        bool Start();
        void Stop();

    private:
        std::atomic<bool>   mRunning;
        Task                mTask;
        std::thread         mThread;
};