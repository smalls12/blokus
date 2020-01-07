#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

extern "C" {
#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
}

#include "Network.hpp"

#include "StartScreen.hpp"
#include "GameLobbyScreen.hpp"

#include "TaskProcessor.hpp"
#include "FindGame.hpp"
#include "ActiveGameManager.hpp"

#include "PlayerManager.hpp"
#include "RegisterForGame.hpp" 
#include "WaitForServerNode.hpp"
#include "RegisterResponse.hpp"
#include "MessageProcessor.hpp"

#include "Register.hpp"

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

#ifdef SPDLOG_ACTIVE_LEVEL
    #undef SPDLOG_ACTIVE_LEVEL
    #define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_DEBUG
#endif

static const int screenWidth = 800;
static const int screenHeight = 450;

using namespace std::placeholders;  // for _1, _2, _3...

Game ShowStartScreen()
{
    // start looking for active games
    // NetworkConnection nc("searching");
    Network network("searching");
    network.Connect();
    network.Start();

    ActiveGameManager agm;
    FindGame fg(network, agm);
    StartScreen startScreen(fg, agm);
    Game gm = startScreen.Show();
    network.Stop();
    network.Disconnect();
    return gm;
}

void ShowGameLobbyScreen(Game gm)
{
    if ( gm.GetGameMode() == GameMode::START )
    {
        spdlog::get("console")->info("Blokus::Starting Game [ {} ]!", gm.GetGameName());

        // create network connection
        Network network(gm.GetUsername());
        network.Connect();
        network.Configure(gm.GetGameName());
        network.Start();
        network.JoinGroup(gm.GetGameName());

        Message m;

        // object that will respond to registration requests
        RegisterResponse rr(network, network, gm.GetUsername(), gm.GetGameName(), m);

        // create player manager
        PlayerManager pm(rr);

        // create local user
        auto myself = std::make_shared<Player>( gm.GetUsername(), network.GetUniqueIdentifier(), 1 );

        // add local user to player manager
        pm.AddPlayerToGame(network.GetUniqueIdentifier(), myself);

        // create message processor
        MessageProcessor mp(m);

        // add an endpoint
        // in this case we are interested in responding to registration requests
        // mp.SetReceiveEndpoint(blokus::REGISTER, std::bind(static_cast<bool(PlayerManager::*)(blokus::Message, blokus::Message&)>(&PlayerManager::RegisterPlayer), &pm, _1, _2));
        // mp.SetResponseEndpoint(blokus::REGISTER, std::bind(&RegisterResponse::SendRegisterResponse, &rr, _1));
        mp.SetRegisterRequestEndpoint(std::bind(&PlayerManager::RegisterRemotePlayer, &pm, _1));
        
        // create read game notification object
        ReadGameNotification rgn(network, gm.GetGameName());

        // create game lobby
        GameLobbyScreen gameLobbyScreen(gm.GetGameMode(), mp, rgn, pm);

        // display the screen on the gui
        gameLobbyScreen.Show();

        network.Stop();
        network.LeaveGroup(gm.GetGameName());
        network.Disconnect();
    }
    else if (gm.GetGameMode() == GameMode::JOIN )
    {
        spdlog::get("console")->info("Blokus::Joining Game [ {} ]!", gm.GetGameName());

        // create network connection
        Network network(gm.GetUsername());
        network.Connect();
        network.Start();
        network.JoinGroup(gm.GetGameName());

        Message m;

        // object that will respond to registration requests
        RegisterResponse rr(network, network, gm.GetUsername(), gm.GetGameName(), m);

        // create player manager
        PlayerManager pm(rr);

        // create local user
        auto myself = std::make_shared<Player>( gm.GetUsername(), network.GetUniqueIdentifier(), 1 );

        // add local user to player manager
        pm.AddPlayerToGame(network.GetUniqueIdentifier(), myself);

        // create message processor
        MessageProcessor mp(m);

        // add an endpoint
        // in this case we are interested in the response to a registration request
        // mp.SetResponseEndpoint(blokus::REGISTER, std::bind(static_cast<bool(PlayerManager::*)(blokus::Message)>(&PlayerManager::RegisterPlayer), &pm, _1));
        mp.SetRegistrationSuccessfulEndpoint(std::bind(&PlayerManager::RegisterLocalPlayer, &pm, _1));
        mp.SetRegistrationUnsuccessfulEndpoint(std::bind(static_cast<bool(PlayerManager::*)(IRegistrationUnsuccessful&)>(&PlayerManager::RemovePlayerFromGame), &pm, _1));

        // create read game notification object
        ReadGameNotification rgn(network, gm.GetGameName());

        // build internal registration object
        Register _register;
        _register.SetUsername(gm.GetUsername());
        _register.SetUuid(network.GetUniqueIdentifier());

        // object used to send register requests
        RegisterForGame rfg(network, _register, m);

        // perform registration request
        rfg.Register(gm.GetGameName());

        // create game lobby
        GameLobbyScreen gameLobbyScreen(gm.GetGameMode(), mp, rgn, pm);

        // display the screen on the gui
        gameLobbyScreen.Show();

        network.Stop();
        network.LeaveGroup(gm.GetGameName());
        network.Disconnect();
    }
    else
    {
        spdlog::get("stderr")->error("Blokus::Start Screen error! Closing...");
    }
}

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

    Game gm = ShowStartScreen();
    
    ShowGameLobbyScreen(gm);

    CloseWindow();

    spdlog::get("console")->info("Blokus::Done");
    
    return 0;
}

