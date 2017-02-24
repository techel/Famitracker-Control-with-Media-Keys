#include "ftremote.hpp"
#include "hotkey.hpp"
#include <windows.h>

int CALLBACK WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	auto ticket1 = Hotkey::registerHotkey(Hotkey::KeyType::MediaPlayPause, [&]()
	{
		FtRemote::togglePlay();
	});

	auto ticket2 = Hotkey::registerHotkey(Hotkey::KeyType::MediaStop, [&]()
	{
		FtRemote::stop();
	});

	Hotkey::dispatchHotkeys();
}