#pragma once

#include "IRandomizePlayerIds.hpp"

#include "IPlayerRegistry.hpp"

#include "spdlog/spdlog.h"

class RandomizePlayerIds : public IRandomizePlayerIds
{
    public:
        RandomizePlayerIds(IPlayerRegistry& registry);
        ~RandomizePlayerIds();

        void Randomize();

    private:
        IPlayerRegistry&       mPlayerRegistry;
};