#include "Register.hpp"

Register::Register()
{
    spdlog::get("console")->debug("Register::Register");
}

Register::~Register()
{
    spdlog::get("console")->debug("Register::~Register");
}