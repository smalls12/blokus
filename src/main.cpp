#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

extern "C" {
#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
}

#include "StartScreen.hpp"
#include "GameLobbyScreen.hpp"

#include "TaskProcessor.hpp"
#include "FindGame.hpp"
#include "StartGame.hpp"
#include "JoinGame.hpp"
#include "ActiveGameManager.hpp"

#include "PlayerManager.hpp"
#include "RegisterForGame.hpp" 
#include "WaitForServerNode.hpp"
#include "RegisterResponse.hpp"
#include "MessageProcessor.hpp"

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

#ifdef SPDLOG_ACTIVE_LEVEL
    #undef SPDLOG_ACTIVE_LEVEL
    #define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_DEBUG
#endif

static const int screenWidth = 800;
static const int screenHeight = 450;

using namespace std::placeholders;  // for _1, _2, _3...

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    // create color multi threaded logger
    spdlog::set_level(spdlog::level::debug); // Set global log level to info
    auto console = spdlog::stdout_color_mt("console");    
    auto err_logger = spdlog::stderr_color_mt("stderr");

    spdlog::get("console")->info("Blokus::Start");
    spdlog::get("console")->info("Blokus::Start - CPP {}", __cplusplus);

    SetConfigFlags(FLAG_MSAA_4X_HINT);  // NOTE: Try to enable MSAA 4X

    InitWindow(screenWidth, screenHeight, "Blokus");

    Game gm;
    // std::string name(argv[argc - 1]);

    {
        // start looking for active games
        NetworkConnection nc("searching");
        ActiveGameManager agm;
        FindGame fg(nc, agm);
        StartScreen startScreen(fg, agm);
        gm = startScreen.Show();
    }
    
    if ( gm.GetGameMode() == GameMode::START )
    {
        spdlog::get("console")->info("Blokus::Starting Game [ {} ]!", gm.GetGameName());

        // create network connection
        NetworkConnection nc(gm.GetUsername());

        // start network
        StartGame sg(nc, gm.GetGameName());

        // create player manager
        PlayerManager pm;

        // create local user
        auto myself = std::make_shared<Player>( gm.GetUsername(), sg.GetUuid(), 1 );

        // add local user to player manager
        pm.AddPlayerToGame(sg.GetUuid(), myself);

        // not sure yet
        RegisterResponse rr(nc, gm.GetUsername(), gm.GetGameName());

        // create message processor
        MessageProcessor mp;

        // add an endpoint
        // in this case we are interested in responding to registration requests
        mp.SetReceiveEndpoint(blokus::REGISTER, std::bind(static_cast<bool(PlayerManager::*)(blokus::Message, blokus::Message&)>(&PlayerManager::RegisterPlayer), &pm, _1, _2));
        mp.SetResponseEndpoint(blokus::REGISTER, std::bind(&RegisterResponse::SendRegisterResponse, &rr, _1));

        // create read game notification object
        ReadGameNotification rgn(nc, gm.GetGameName());

        // create game lobby
        GameLobbyScreen gameLobbyScreen(gm.GetGameMode(), mp, rgn, pm);

        // display the screen on the gui
        gameLobbyScreen.Show();
    }
    else if (gm.GetGameMode() == GameMode::JOIN )
    {
        spdlog::get("console")->info("Blokus::Joining Game [ {} ]!", gm.GetGameName());

        // create network connection
        NetworkConnection nc(gm.GetUsername());

        // join network
        JoinGame jg(nc, gm.GetGameName());

        // create player manager
        PlayerManager pm;

        // create local user
        auto myself = std::make_shared<Player>( gm.GetUsername(), jg.GetUuid(), 1 );

        // add local user to player manager
        pm.AddPlayerToGame(jg.GetUuid(), myself);

        // create message processor
        MessageProcessor mp;

        // add an endpoint
        // in this case we are interested in the response to a registration request
        mp.SetResponseEndpoint(blokus::REGISTER, std::bind(static_cast<bool(PlayerManager::*)(blokus::Message)>(&PlayerManager::RegisterPlayer), &pm, _1));

        // create read game notification object
        ReadGameNotification rgn(nc, gm.GetGameName());

        //
        RegisterForGame rfg(nc, gm.GetGameName());

        //
        rfg(gm.GetUsername(), jg.GetUuid());

        //
        GameLobbyScreen gameLobbyScreen(gm.GetGameMode(), mp, rgn, pm);

        //
        gameLobbyScreen.Show();
    }
    else
    {
        spdlog::get("stderr")->error("Blokus::Start Screen error! Closing...");
        return 1;
    }

    CloseWindow();

    spdlog::get("console")->info("Blokus::Done");
    
    return 0;
}

