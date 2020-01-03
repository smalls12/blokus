#include "TaskProcessor.hpp"

#include "spdlog/spdlog.h"

#include <iostream>

TaskProcessor::TaskProcessor(Task task)
:   mRunning(false),
    mTask(task),
    mThread()
{
    spdlog::get("console")->debug("TaskProcessor::TaskProcessor - Start");
}

TaskProcessor::~TaskProcessor()
{
    spdlog::get("console")->debug("TaskProcessor::~TaskProcessor - Start");

    Stop();
}

bool TaskProcessor::Start()
{
    spdlog::get("console")->debug("TaskProcessor::Start() - Start.");

    mRunning = true;

    mThread = std::thread([&]{
        spdlog::get("console")->debug("TaskProcessor::Start() - Thread started");

        while( mRunning )
        {
            mTask();
        }
    });

    return false;
}

void TaskProcessor::Stop()
{
    spdlog::get("console")->debug("TaskProcessor::Stop() - Start.");

    mRunning = false;

    if (mThread.joinable())
    {
        spdlog::get("console")->debug("TaskProcessor::Stop() - Waiting for thread to join...");
        mThread.join();
    }
    else
    {
        spdlog::get("stderr")->error("TaskProcessor::Stop() - Thread not joinable");
    }
    
    return;
}