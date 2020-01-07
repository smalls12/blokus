#include "Message.hpp"
#include "Register.hpp"

#include "spdlog/spdlog.h"

Message::Message()
{
    spdlog::get("console")->debug("Message::Message()");

}

Message::~Message()
{
    spdlog::get("console")->debug("Message::~Message()");

}

std::string Message::BuildRegistrationRequestMessage(IRegisterRequest& request)
{
    blokus::Message message;
    message.set_uuid(request.GetUuid());

    message.set_type(blokus::Message::REQUEST);

    blokus::Request *blokus_request = message.mutable_request();
    blokus_request->set_type(blokus::REGISTER);

    blokus::RegisterReq *register_req = blokus_request->mutable_register_req();

    // assign pice that was moved
    register_req->set_username(request.GetUsername());
    register_req->set_uuid(request.GetUuid());

    size_t size = message.ByteSizeLong(); 
    void *buffer = malloc(size);
    message.SerializeToArray(buffer, size);

    return std::string( (char *)buffer );
}

std::string Message::BuildRegistrationResponseMessage(IRegistrationSuccessful& response)
{
    blokus::Message _message;
    _message.set_uuid(response.GetUuid());

    _message.set_type(blokus::Message::RESPONSE);

    blokus::Response *_response = _message.mutable_response();
    _response->set_type(blokus::REGISTER);

    blokus::RegisterResp *_register = _response->mutable_register_resp();

    blokus::PlayerColor pc;
    switch (response.GetPlayerColor())
    {
        case PlayerColor::BLUE:
        {
            pc = blokus::PlayerColor::BLOKUS_BLUE;
            break;
        }
        case PlayerColor::RED:
        {
            pc = blokus::PlayerColor::BLOKUS_RED;
            break;
        }
        case PlayerColor::GREEN:
        {
            pc = blokus::PlayerColor::BLOKUS_GREEN;
            break;
        }
        case PlayerColor::YELLOW:
        {
            pc = blokus::PlayerColor::BLOKUS_YELLOW;
            break;
        }
        default:
        {
            break;
        }
    }

    _register->set_status(blokus::RegisterResp::SUCCESSFUL);
    _register->set_color(pc);
    _register->set_id(response.GetPlayerId());
    _register->set_username(response.GetUsername());
    _register->set_uuid(response.GetUuid());

    size_t size = _message.ByteSizeLong(); 
    void *buffer = malloc(size);
    _message.SerializeToArray(buffer, size);

    return std::string( (char *)buffer );
}

std::string Message::BuildRegistrationResponseMessage(IRegistrationUnsuccessful& response)
{
    blokus::Message _message;
    _message.set_uuid(response.GetUuid());

    _message.set_type(blokus::Message::RESPONSE);

    blokus::Response *_response = _message.mutable_response();
    _response->set_type(blokus::REGISTER);

    blokus::RegisterResp *_register = _response->mutable_register_resp();

    _register->set_status(blokus::RegisterResp::UNSUCCESSFUL);
    _register->set_error("blah");

    size_t size = _message.ByteSizeLong(); 
    void *buffer = malloc(size);
    _message.SerializeToArray(buffer, size);

    return std::string( (char *)buffer );
}

bool Message::ParseRegistrationRequestMessage(std::string message, IRegisterRequest& request)
{
    spdlog::get("console")->debug("Message::ParseRegistrationRequestMessage()");

    blokus::Message in;
    in.ParseFromString(message);

    spdlog::get("console")->debug("Message::ParseRegistrationRequestMessage() - {}", in.DebugString());

    request.SetUsername(in.request().register_req().username());
    request.SetUuid(in.request().register_req().uuid());

    return true;
}

bool Message::ParseRegistrationResponseMessage(std::string message, IRegistrationSuccessful& sucessful, IRegistrationUnsuccessful& unsuccesful)
{
    blokus::Message in;
    in.ParseFromString(message);

    spdlog::get("console")->debug("Message::ParseRegistrationResponseMessage() - {}", in.DebugString());

    bool success = false;
    success = in.response().success();

    Register r;
    if( success )
    {
        PlayerColor pc;
        switch( in.response().register_resp().color() )
        {
            case blokus::PlayerColor::BLOKUS_BLUE:
            {
                pc = PlayerColor::BLUE;
                break;
            }
            case blokus::PlayerColor::BLOKUS_RED:
            {
                pc = PlayerColor::BLUE;
                break;
            }
            case blokus::PlayerColor::BLOKUS_GREEN:
            {
                pc = PlayerColor::BLUE;
                break;
            }
            case blokus::PlayerColor::BLOKUS_YELLOW:
            {
                pc = PlayerColor::BLUE;
                break;
            }
            default:
            {
                // error
                break;
            }
        }

        r.SetPlayerColor(pc);
        r.SetPlayerId(in.response().register_resp().id());
        r.SetUsername(in.response().register_resp().username());
        r.SetUuid(in.response().register_resp().uuid());

        sucessful = r;
    }
    else
    {
        // set error message

        unsuccesful = r;
    }

    return success;
}




// static blokus::Message BuildBaseMessage(std::string uuid)
// {
//     blokus::Message message;
//     message.set_uuid(uuid);

//     return message;
// }

// static blokus::PlayerColor ConvertPlayerColorEnum(PlayerColor color)
// {
//     switch (color)
//     {
//         case PlayerColor::BLUE:
//             return blokus::PlayerColor::BLOKUS_BLUE;
//         case PlayerColor::RED:
//             return blokus::PlayerColor::BLOKUS_RED;
//         case PlayerColor::GREEN:
//             return blokus::PlayerColor::BLOKUS_GREEN;
//         case PlayerColor::YELLOW:
//             return blokus::PlayerColor::BLOKUS_YELLOW;
//     }

//     // this can't happen
//     // it's an enum
//     return blokus::PlayerColor::BLOKUS_BLUE;
// }

// void Message::BuildRegisterReq(blokus::Message& message, std::string username)
// {
//     message.set_type(blokus::Message::REQUEST);

//     // initialize PlayerMove message
//     blokus::Request *blokus_request = message.mutable_request();
//     blokus_request->set_type(blokus::REGISTER);

//     // initialize PlayerMove message
//     blokus::RegisterReq *register_req = blokus_request->mutable_register_req();

//     // assign pice that was moved
//     register_req->set_username(username);
// }

// blokus::Message Message::BuildRegisterReq(std::string username, std::string uuid)
// {
//     blokus::Message message;
//     message.set_type(blokus::Message::REQUEST);
//     message.set_uuid(uuid);

//     // initialize PlayerMove message
//     blokus::Request *blokus_request = message.mutable_request();
//     blokus_request->set_type(blokus::REGISTER);

//     // initialize PlayerMove message
//     blokus::RegisterReq *register_req = blokus_request->mutable_register_req();

//     // assign pice that was moved
//     register_req->set_username(username);

//     return message;
// }

// void Message::BuildRegisterResp(blokus::Message& message, PlayerColor color, uint32_t id, std::string username, std::string uuid)
// {
//     message.set_type(blokus::Message::RESPONSE);

//     // initialize PlayerMove message
//     blokus::Response *blokus_response = message.mutable_response();
//     blokus_response->set_type(blokus::REGISTER);

//     blokus::RegisterResp *register_resp = blokus_response->mutable_register_resp();
//     register_resp->set_color(ConvertPlayerColorEnum(color));
//     register_resp->set_id(id);
//     register_resp->set_username(username);
//     register_resp->set_uuid(uuid);
// }

// blokus::Message Message::BuildRegisterResp(PlayerColor color, uint32_t id, std::string username)
// {
//     blokus::Message message;
//     message.set_type(blokus::Message::RESPONSE);

//     // initialize PlayerMove message
//     blokus::Response *blokus_response = message.mutable_response();
//     blokus_response->set_type(blokus::REGISTER);

//     blokus::RegisterResp *register_resp = blokus_response->mutable_register_resp();
//     register_resp->set_color(ConvertPlayerColorEnum(color));
//     register_resp->set_id(id);
//     register_resp->set_username(username);
//     // register_resp->set_uuid(uuid);

//     return message;
// }

// blokus::Message Message::BuildStartGameReq(const std::vector<Player *> players)
// {
//     blokus::Message message;
//     message.set_type(blokus::Message::REQUEST);

//     // initialize PlayerMove message
//     blokus::Request *blokus_request = message.mutable_request();
//     blokus_request->set_type(blokus::START_GAME);

//     blokus::StartGameReq *start_game_req = blokus_request->mutable_start_game_req();

//     return message;
// }

// blokus::Message Message::BuildStartGameResp()
// {
//     blokus::Message message;
//     message.set_type(blokus::Message::RESPONSE);

//     // initialize PlayerMove message
//     blokus::Response *blokus_response = message.mutable_response();
//     blokus_response->set_type(blokus::START_GAME);

//     return message;
// }

// blokus::Message Message::BuildPlayerMoveReq()
// {
//     blokus::Message message;
//     message.set_type(blokus::Message::REQUEST);

//     // initialize PlayerMove message
//     blokus::Request *blokus_request = message.mutable_request();
//     blokus_request->set_type(blokus::PLAYER_MOVE);

//     return message;
// }

// static blokus::Piece ConvertPieceEnum(int piece)
// {
//     switch (piece)
//     {
//         case 0:
//             return blokus::Piece::I5;
//         case 1:
//             return blokus::Piece::N;
//         case 2:
//             return blokus::Piece::V5;
//         case 3:
//             return blokus::Piece::T5;
//         case 4:
//             return blokus::Piece::U;
//         case 5:
//             return blokus::Piece::L5;
//         case 6:
//             return blokus::Piece::Y;
//         case 7:
//             return blokus::Piece::Z5;
//         case 8:
//             return blokus::Piece::W;
//         case 9:
//             return blokus::Piece::P;
//         case 10:
//             return blokus::Piece::X;
//         case 11:
//             return blokus::Piece::Z4;
//         case 12:
//             return blokus::Piece::I4;
//         case 13:
//             return blokus::Piece::L4;
//         case 14:
//             return blokus::Piece::O;
//         case 15:
//             return blokus::Piece::T4;
//         case 16:
//             return blokus::Piece::I3;
//         case 17:
//             return blokus::Piece::V3;
//         case 18:
//             return blokus::Piece::I2;
//         case 19:
//             return blokus::Piece::I1;
//     }

//     return blokus::Piece::I5;
// }

// // eventualy change this to an enumerated piece
// blokus::Message Message::BuildPlayerMoveResp(const PieceMove *move)
// {
//     blokus::Message message;
//     message.set_type(blokus::Message::RESPONSE);

//     // initialize PlayerMove message
//     blokus::Response *blokus_response = message.mutable_response();
//     blokus_response->set_type(blokus::PLAYER_MOVE);

//     // // initialize PlayerMove message
//     blokus::PlayerMoveResp *player_move_resp = blokus_response->mutable_player_move_resp();

//     // assign pice that was moved
//     player_move_resp->set_piece(ConvertPieceEnum(move->getPiece()));

//     // initialize Location messages
//     blokus::Location *location = player_move_resp->mutable_location();
//     location->set_x_position(move->getXPos());
//     location->set_y_position(move->getYPos());

//     return message;
// }

// blokus::Message Message::BuildEndGameReq()
// {
//     blokus::Message message;
//     message.set_type(blokus::Message::RESPONSE);

//     // initialize PlayerMove message
//     blokus::Response *blokus_response = message.mutable_response();
//     blokus_response->set_type(blokus::END_GAME);

//     return message;
// }

// blokus::Message Message::BuildEndGameResp()
// {
//     blokus::Message message;
//     message.set_type(blokus::Message::RESPONSE);

//     // initialize PlayerMove message
//     blokus::Response *blokus_response = message.mutable_response();
//     blokus_response->set_type(blokus::END_GAME);

//     return message;
// }
