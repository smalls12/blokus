#pragma once

/* =========================================================
 *
 * IMessage.hpp
 * 
 * Network layer abstraction
 * Building with reference to what I know I need from zyre
 * However should be abstract enough to replace with any
 * network technology
 * 
 * ========================================================= */

#include <string>

class IMessage
{
    public:
        virtual std::string GetUuid();

};