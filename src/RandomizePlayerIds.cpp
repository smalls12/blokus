#include "RandomizePlayerIds.hpp"

RandomizePlayerIds::RandomizePlayerIds(IPlayerRegistry& registry)
:   mPlayerRegistry(registry)
{
    spdlog::get("console")->debug("RandomizePlayerIds::RandomizePlayerIds()");
}

RandomizePlayerIds::~RandomizePlayerIds()
{
    spdlog::get("console")->debug("RandomizePlayerIds::~RandomizePlayerIds()");
}

void RandomizePlayerIds::Randomize()
{
    spdlog::get("console")->debug("RandomizePlayerIds::Process() - Start");

    std::vector<std::shared_ptr<Player>> players = mPlayerRegistry.GetListOfPlayers();
    unsigned int numberOfPlayers = players.size();
    std::random_shuffle(players.begin(), players.end());
    for( unsigned int x = 0; x < numberOfPlayers; x++ )
    {
        players[x]->AssignPlayerID(x + 1);
    }

    spdlog::get("console")->debug("RandomizePlayerIds::Process() - Done");
}
