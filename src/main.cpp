extern "C" {
#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
}

#include "Network.hpp"

#include "StartScreen.hpp"

#include "GameLobby.hpp"
#include "GameLobbyScreen.hpp"
#include "StartGameLobbyScreen.hpp"
#include "GameScreen.hpp"

#include "FindGame.hpp"
#include "ActiveGameManager.hpp"

#include "PlayerManager.hpp"

#include "MessageBase.hpp"

#include "Register.hpp"
#include "RegisterForGame.hpp" 
#include "RegisterResponse.hpp"

#include "MessageProcessor.hpp"

#include "RandomizePlayerIds.hpp"

#include "StartGame.hpp"
#include "StartGameRequest.hpp"

#include "PlayerMoveRequest.hpp"
#include "ProcessPlayerMove.hpp"

#include <sstream>

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

void ShowGameLobby_StartGame(Game gm)
{
    spdlog::get("console")->info("Blokus::Starting Game [ {} ]!", gm.GetGameName());

    // create network connection
    Network network(gm.GetUsername());
    network.Connect();
    network.Configure(gm.GetGameName());
    network.Start();
    network.JoinGroup(gm.GetGameName());

    GameLobby gameLobby(gm, network);

    Message m;

    // object that will respond to registration requests
    RegisterResponse rr(network, network, gm.GetUsername(), gm.GetGameName(), m);

    // create player manager
    PlayerManager playerManager(rr);

    // create local user
    auto myself = std::make_shared<Player>( gm.GetUsername(), network.GetUniqueIdentifier() );

    // add local user to player manager
    playerManager.AddLocalPlayerToGame(network.GetUniqueIdentifier(), myself);

    // create message processor
    MessageProcessor mp;

    // add an endpoint
    // in this case we are interested in responding to registration requests
    mp.SetRegisterRequestEndpoint(std::bind(static_cast<bool(PlayerManager::*)(IRegisterRequest&)>(&PlayerManager::RegisterPlayer), &playerManager, _1));
    // mp.SetStartGameEndpoint();

    // build start game object
    MessageBase startGameMessageBase(network);
    StartGameRequest startGameRequest(m, startGameMessageBase);
    StartGame sg(network, startGameRequest);

    // build player move object
    MessageBase playerMoveMessageBase(network);
    PlayerMoveRequest playerMoveRequest(m, playerMoveMessageBase);
    ProcessPlayerMove processPlayerMove(gameLobby, playerMoveRequest);

    // create read game notification object
    ReadGameNotification rgn(network, gm.GetGameName());

    // create randomize object
    RandomizePlayerIds randomizePlayerIds(playerManager);

    // create game lobby
    StartGameLobbyScreen startGameLobbyScreen(gm, mp, rgn, playerManager, sg, randomizePlayerIds);

    // display the start screen on the gui
    startGameLobbyScreen.Show();

    std::stringstream sstream;
    sstream << playerManager;
    spdlog::get("console")->info("Blokus::Players {}", sstream.str());

    // create the game screen
    GameScreen gameScreen(gm, mp, rgn, playerManager, processPlayerMove);
    
    mp.SetPlayerMoveEndpoint(std::bind(&GameScreen::ProcessRemotePlayerMove, &gameScreen, _1));

    // display the game screen on the gui
    gameScreen.Show();

    network.Stop();
    network.LeaveGroup(gm.GetGameName());
    network.Disconnect();
}

void ShowGameLobby_JoinGame(Game gm)
{
    spdlog::get("console")->info("Blokus::Joining Game [ {} ]!", gm.GetGameName());

    // create network connection
    Network network(gm.GetUsername());
    network.Connect();
    network.Start();
    network.JoinGroup(gm.GetGameName());

    GameLobby gameLobby(gm, network);

    Message m;

    // object that will respond to registration requests
    RegisterResponse rr(network, network, gm.GetUsername(), gm.GetGameName(), m);

    // create player manager
    PlayerManager playerManager(rr);

    // create local user
    auto myself = std::make_shared<Player>( gm.GetUsername(), network.GetUniqueIdentifier() );

    // add local user to player manager
    playerManager.AddLocalPlayerToGame(network.GetUniqueIdentifier(), myself);
    
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

    // create message processor
    MessageProcessor mp;

    // create game lobby
    GameLobbyScreen gameLobbyScreen(gm, mp, rgn, playerManager);

    // add an endpoint
    // in this case we are interested in the response to a registration request
    mp.SetRegistrationSuccessfulEndpoint(std::bind(static_cast<bool(PlayerManager::*)(IRegistrationSuccessful&)>(&PlayerManager::RegisterPlayer), &playerManager, _1));
    mp.SetRegistrationUnsuccessfulEndpoint(std::bind(static_cast<bool(PlayerManager::*)(IRegistrationUnsuccessful&)>(&PlayerManager::RemovePlayerFromGame), &playerManager, _1));
    mp.SetStartGameEndpoint(std::bind(&GameLobbyScreen::ReadyToStart, &gameLobbyScreen, _1));

    // display the start screen on the gui
    gameLobbyScreen.Show();

    std::stringstream sstream;
    sstream << playerManager;
    spdlog::get("console")->info("Blokus::Players {}", sstream.str());

    // build player move object
    MessageBase playerMoveMessageBase(network);
    PlayerMoveRequest playerMoveRequest(m, playerMoveMessageBase);
    ProcessPlayerMove processPlayerMove(gameLobby, playerMoveRequest);

    // create the game screen
    GameScreen gameScreen(gm, mp, rgn, playerManager, processPlayerMove);

    mp.SetPlayerMoveEndpoint(std::bind(&GameScreen::ProcessRemotePlayerMove, &gameScreen, _1));

    // display the game screen on the gui
    gameScreen.Show();

    network.Stop();
    network.LeaveGroup(gm.GetGameName());
    network.Disconnect();
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

    switch( gm.GetGameMode() )
    {
        case GameMode::START:
        {
            ShowGameLobby_StartGame(gm);
            break;
        }
        case GameMode::JOIN:
        {
            ShowGameLobby_JoinGame(gm);
            break;
        }
        default:
        {
            spdlog::get("stderr")->error("Blokus::Start Screen error! Closing...");
            break;
        }
    }
    
    CloseWindow();

    spdlog::get("console")->info("Blokus::Done");
    
    return 0;
}

