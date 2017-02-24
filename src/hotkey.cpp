#include "hotkey.hpp"
#include <Windows.h>
#include <atomic>
#include <map>

namespace Hotkey
{

static std::map<int, std::function<void()>> Listeners;

Ticket registerHotkey(KeyType key, std::function<void()> listener)
{
	int id = static_cast<int>(Listeners.size());
	RegisterHotKey(0, id, 0, static_cast<UINT>(key));

	auto it = Listeners.insert({ id, std::move(listener) });

	return Ticket([=]()
	{
		UnregisterHotKey(0, id);
		if(it.second)
			Listeners.erase(it.first);
	});
}

void dispatchHotkeys()
{
	MSG msg;
	while(GetMessageA(&msg, 0, 0, 0))
	{
		if(msg.message == WM_HOTKEY)
		{
			int id = static_cast<size_t>(msg.wParam);
			auto it = Listeners.find(id);
			if(it != Listeners.end())
				it->second();
		}
	}
}

}