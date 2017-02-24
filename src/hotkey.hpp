#pragma once
#include <functional>
#include "ticket.hpp"

namespace Hotkey
{

//
// Types of keys, representing virtual key codes.
//

enum class KeyType { MediaPlayPause = 0xB3, MediaStop = 0xB2 };

//
// Register and dispatch hotkey listeners.
//

Ticket registerHotkey(KeyType key, std::function<void()> listener);
void dispatchHotkeys();

}
