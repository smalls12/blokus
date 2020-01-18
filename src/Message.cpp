#include "Message.hpp"
#include "Register.hpp"

#include "PlayerMoveRequestData.hpp"

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

    blokus::PlayerColor pc = blokus::PlayerColor::BLOKUS_BLUE;
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

std::string Message::BuildStartGameRequestMessage(IMessageBase& base)
{
    blokus::Message message;
    message.set_uuid(base.GetUniqueIdentifier());

    message.set_type(blokus::Message::REQUEST);

    blokus::Request *blokus_request = message.mutable_request();
    blokus_request->set_type(blokus::START_GAME);

    size_t size = message.ByteSizeLong(); 
    void *buffer = malloc(size);
    message.SerializeToArray(buffer, size);

    return std::string( (char *)buffer );
}

bool Message::ParseStartGameRequestMessage(std::string message)
{
    blokus::Message in;
    in.ParseFromString(message);
    
    spdlog::get("console")->debug("Message::ParseStartGameRequestMessage() - {}", in.DebugString());

    return true;
}

std::string Message::BuildPlayerMoveRequestMessage(IMessageBase& base, IPlayerMoveRequestData& data)
{
    blokus::Message message;
    message.set_uuid(base.GetUniqueIdentifier());

    message.set_type(blokus::Message::REQUEST);

    blokus::Request *_request = message.mutable_request();
    _request->set_type(blokus::PLAYER_MOVE);

    blokus::PlayerMoveReq *_player_move = _request->mutable_player_move_req();

    _player_move->set_id(data.GetPlayerId());

    blokus::Piece piece = ConvertPieceToMessageEnum(data.GetPieceType());
    _player_move->set_piece(piece);

    // initialize Location messages
    blokus::Location *location = _player_move->mutable_location();
    location->set_x_position(data.GetLocation().GetX());
    location->set_y_position(data.GetLocation().GetY());

    size_t size = message.ByteSizeLong(); 
    void *buffer = malloc(size);
    message.SerializeToArray(buffer, size);

    return std::string( (char *)buffer );
}

bool Message::ParsePlayerMoveRequestMessage(std::string message, IPlayerMoveRequestData& data)
{
    blokus::Message in;
    in.ParseFromString(message);
    
    spdlog::get("console")->debug("Message::ParseStartGameRequestMessage() - {}", in.DebugString());

    data.SetPlayerId(in.request().player_move_req().id());

    PieceType type = ParseMessageEnumToPiece(in.request().player_move_req().piece());
    data.SetPieceType(type);

    data.SetLocation(Point(in.request().player_move_req().location().x_position(), in.request().player_move_req().location().y_position()));

    return true;
}

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

blokus::Piece Message::ConvertPieceToMessageEnum(PieceType type)
{
    switch ( type )
    {
        case PieceType::I5:
            return blokus::Piece::I5;
        case PieceType::N:
            return blokus::Piece::N;
        case PieceType::V5:
            return blokus::Piece::V5;
        case PieceType::T5:
            return blokus::Piece::T5;
        case PieceType::U:
            return blokus::Piece::U;
        case PieceType::L5:
            return blokus::Piece::L5;
        case PieceType::Y:
            return blokus::Piece::Y;
        case PieceType::Z5:
            return blokus::Piece::Z5;
        case PieceType::W:
            return blokus::Piece::W;
        case PieceType::P:
            return blokus::Piece::P;
        case PieceType::X:
            return blokus::Piece::X;
        case PieceType::Z4:
            return blokus::Piece::Z4;
        case PieceType::I4:
            return blokus::Piece::I4;
        case PieceType::L4:
            return blokus::Piece::L4;
        case PieceType::O:
            return blokus::Piece::O;
        case PieceType::T4:
            return blokus::Piece::T4;
        case PieceType::I3:
            return blokus::Piece::I3;
        case PieceType::V3:
            return blokus::Piece::V3;
        case PieceType::I2:
            return blokus::Piece::I2;
        case PieceType::I1:
            return blokus::Piece::I1;
    }

    return blokus::Piece::I5;
}

PieceType Message::ParseMessageEnumToPiece(blokus::Piece type)
{
    switch ( type )
    {
        case blokus::Piece::I5:
            return PieceType::I5;
        case blokus::Piece::N:
            return PieceType::N;
        case blokus::Piece::V5:
            return PieceType::V5;
        case blokus::Piece::T5:
            return PieceType::T5;
        case blokus::Piece::U:
            return PieceType::U;
        case blokus::Piece::L5:
            return PieceType::L5;
        case blokus::Piece::Y:
            return PieceType::Y;
        case blokus::Piece::Z5:
            return PieceType::Z5;
        case blokus::Piece::W:
            return PieceType::W;
        case blokus::Piece::P:
            return PieceType::P;
        case blokus::Piece::X:
            return PieceType::X;
        case blokus::Piece::Z4:
            return PieceType::Z4;
        case blokus::Piece::I4:
            return PieceType::I4;
        case blokus::Piece::L4:
            return PieceType::L4;
        case blokus::Piece::O:
            return PieceType::O;
        case blokus::Piece::T4:
            return PieceType::T4;
        case blokus::Piece::I3:
            return PieceType::I3;
        case blokus::Piece::V3:
            return PieceType::V3;
        case blokus::Piece::I2:
            return PieceType::I2;
        case blokus::Piece::I1:
            return PieceType::I1;
    }

    return PieceType::I5;
}

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
