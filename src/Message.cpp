#include <Message.hpp>

static blokus::PlayerColor ConvertPlayerColorEnum(PlayerColor color)
{
    switch (color)
    {
        case PlayerColor::BLUE:
            return blokus::PlayerColor::BLOKUS_BLUE;
        case PlayerColor::RED:
            return blokus::PlayerColor::BLOKUS_RED;
        case PlayerColor::GREEN:
            return blokus::PlayerColor::BLOKUS_GREEN;
        case PlayerColor::YELLOW:
            return blokus::PlayerColor::BLOKUS_YELLOW;
    }

    // this can't happen
    // it's an enum
    return blokus::PlayerColor::BLOKUS_BLUE;
}

blokus::Message Message::BuildRegisterReq(std::string username, std::string uuid)
{
    blokus::Message message;
    message.set_type(blokus::Message::REQUEST);
    message.set_uuid(uuid);

    // initialize PlayerMove message
    blokus::Request *blokus_request = message.mutable_request();
    blokus_request->set_type(blokus::REGISTER);

    // initialize PlayerMove message
    blokus::RegisterReq *register_req = blokus_request->mutable_register_req();

    // assign pice that was moved
    register_req->set_username(username);

    return message;
}

blokus::Message Message::BuildRegisterResp(PlayerColor color, uint32_t id, std::string username)
{
    blokus::Message message;
    message.set_type(blokus::Message::RESPONSE);

    // initialize PlayerMove message
    blokus::Response *blokus_response = message.mutable_response();
    blokus_response->set_type(blokus::REGISTER);

    blokus::RegisterResp *register_resp = blokus_response->mutable_register_resp();

    // build player message
    blokus::Player *player = register_resp->mutable_player();
    player->set_color(ConvertPlayerColorEnum(color));
    player->set_id(id);
    player->set_username(username);

    return message;
}

blokus::Message Message::BuildStartGameReq(const std::vector<Player *> players)
{
    blokus::Message message;
    message.set_type(blokus::Message::REQUEST);

    // initialize PlayerMove message
    blokus::Request *blokus_request = message.mutable_request();
    blokus_request->set_type(blokus::START_GAME);

    blokus::StartGameReq *start_game_req = blokus_request->mutable_start_game_req();

    for(auto const& value: players)
    {
        blokus::Player *player = start_game_req->add_players();
        player->set_color(ConvertPlayerColorEnum(value->getColor()));
        player->set_id(value->getPlayerId());
        player->set_username(value->getUsername());
    }

    return message;
}

blokus::Message Message::BuildStartGameResp()
{
    blokus::Message message;
    message.set_type(blokus::Message::RESPONSE);

    // initialize PlayerMove message
    blokus::Response *blokus_response = message.mutable_response();
    blokus_response->set_type(blokus::START_GAME);

    return message;
}

blokus::Message Message::BuildPlayerMoveReq()
{
    blokus::Message message;
    message.set_type(blokus::Message::REQUEST);

    // initialize PlayerMove message
    blokus::Request *blokus_request = message.mutable_request();
    blokus_request->set_type(blokus::PLAYER_MOVE);

    return message;
}

static blokus::Piece ConvertPieceEnum(int piece)
{
    switch (piece)
    {
        case 0:
            return blokus::Piece::I5;
        case 1:
            return blokus::Piece::N;
        case 2:
            return blokus::Piece::V5;
        case 3:
            return blokus::Piece::T5;
        case 4:
            return blokus::Piece::U;
        case 5:
            return blokus::Piece::L5;
        case 6:
            return blokus::Piece::Y;
        case 7:
            return blokus::Piece::Z5;
        case 8:
            return blokus::Piece::W;
        case 9:
            return blokus::Piece::P;
        case 10:
            return blokus::Piece::X;
        case 11:
            return blokus::Piece::Z4;
        case 12:
            return blokus::Piece::I4;
        case 13:
            return blokus::Piece::L4;
        case 14:
            return blokus::Piece::O;
        case 15:
            return blokus::Piece::T4;
        case 16:
            return blokus::Piece::I3;
        case 17:
            return blokus::Piece::V3;
        case 18:
            return blokus::Piece::I2;
        case 19:
            return blokus::Piece::I1;
    }

    return blokus::Piece::I5;
}

// eventualy change this to an enumerated piece
blokus::Message Message::BuildPlayerMoveResp(const PieceMove *move)
{
    blokus::Message message;
    message.set_type(blokus::Message::RESPONSE);

    // initialize PlayerMove message
    blokus::Response *blokus_response = message.mutable_response();
    blokus_response->set_type(blokus::PLAYER_MOVE);

    // // initialize PlayerMove message
    blokus::PlayerMoveResp *player_move_resp = blokus_response->mutable_player_move_resp();

    // assign pice that was moved
    player_move_resp->set_piece(ConvertPieceEnum(move->getPiece()));

    // initialize Location messages
    blokus::Location *location = player_move_resp->mutable_location();
    location->set_x_position(move->getXPos());
    location->set_y_position(move->getYPos());

    return message;
}

blokus::Message Message::BuildEndGameReq()
{
    blokus::Message message;
    message.set_type(blokus::Message::RESPONSE);

    // initialize PlayerMove message
    blokus::Response *blokus_response = message.mutable_response();
    blokus_response->set_type(blokus::END_GAME);

    return message;
}

blokus::Message Message::BuildEndGameResp()
{
    blokus::Message message;
    message.set_type(blokus::Message::RESPONSE);

    // initialize PlayerMove message
    blokus::Response *blokus_response = message.mutable_response();
    blokus_response->set_type(blokus::END_GAME);

    return message;
}
