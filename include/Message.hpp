#pragma once

// this file helps build messages for transport

// protobuf header
#include <protobuf/blokus.pb.h>

#include <Player.hpp>
#include <PieceMove.hpp>

class Message {

public:
    static blokus::Message BuildRegisterReq(const std::string username, std::string uuid);
    static blokus::Message BuildRegisterResp(PlayerColor color, uint32_t id, std::string username);

    static blokus::Message BuildStartGameReq(const std::vector<Player *> players);
    static blokus::Message BuildStartGameResp();

    static blokus::Message BuildPlayerMoveReq();
    static blokus::Message BuildPlayerMoveResp(const PieceMove *move);

    static blokus::Message BuildPlayerMoveSyncReq(const PieceMove *move);
    static blokus::Message BuildPlayerMoveSyncResp();

    static blokus::Message BuildEndGameReq();
    static blokus::Message BuildEndGameResp();

private:
    Message();
    ~Message();
};
