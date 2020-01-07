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
    UNKNOWN
};
