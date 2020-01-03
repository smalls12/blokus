#include "Task.hpp"

Task::Task(std::function<void()> func)
:   mFunc(func)
{
    spdlog::get("console")->debug("Task::Task() - Start");
}

Task::~Task()
{
    spdlog::get("console")->debug("Task::~Task() - Start");
}