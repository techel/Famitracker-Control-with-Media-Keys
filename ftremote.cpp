#include "ftremote.hpp"
#include <algorithm>
#include <string>
#include <vector>
#include <Windows.h>

namespace FtRemote
{

//
// famitracker remote control
//

static std::vector<HWND> enumHandles()
{
	std::vector<HWND> handles;
	EnumWindows([](HWND hWnd, LPARAM lParam) -> BOOL CALLBACK
	{
		std::string title;
		title.resize(256);
		GetWindowTextA(hWnd, &title[0], title.size());

		//find heuristically
		if(title.find("FamiTracker") != title.npos && title.find("[#") != title.npos)
		{
			auto *r = (std::vector<HWND>*)lParam;
			r->push_back(hWnd);
		}

		return TRUE;

	}, (LPARAM)&handles);

	return handles;
}

static void postMessage(const std::vector<HWND> &handles, UINT msg, WPARAM wParam, LPARAM lParam)
{
	for(const auto &h : handles)
		PostMessageA(h, msg, wParam, lParam);
}

static void broadcastMessage(UINT msg, WPARAM wParam, LPARAM lParam)
{
	auto handles = enumHandles();
	postMessage(handles, msg, wParam, lParam);
}

//copied straight from resource.h
constexpr unsigned int ID_TRACKER_PLAY_START = 138;
constexpr unsigned int ID_TRACKER_TOGGLE_PLAY = 136;
constexpr unsigned int ID_TRACKER_STOP = 32776;

void playStart()
{
	broadcastMessage(WM_COMMAND, ID_TRACKER_PLAY_START, 0);
}
void togglePlay()
{
	broadcastMessage(WM_COMMAND, ID_TRACKER_TOGGLE_PLAY, 0);
}
void stop()
{
	broadcastMessage(WM_COMMAND, ID_TRACKER_STOP, 0);
}

}