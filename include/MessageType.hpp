#pragma once

/* =========================================================
 *
 * Identifies the type of message before passing down to
 * message abstraction layer
 * 
 * ========================================================= */

enum class MessageType
{
    REGISTRATION_REQUEST = 0,
    REGISTRATION_RESPONSE,
    STARTGAME_REQUEST,
    STARTGAME_RESPONSE,
    PLAYERMOVE_REQUEST,
    PLAYERMOVE_RESPONSE,
    UNKNOWN
};
