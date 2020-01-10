#include "common.hpp"

namespace CTRPluginFramework
{
	static StringVector info;
	
	static const std::vector<Item> g_info =
	{
		{"TitleID"},
		{"Console Type"},
		{"WiFi Status"}
	};

	void TitleID(void)
	{
		std::string tid;
		Process::GetTitleID(tid);
		MessageBox("TitleID: " + tid)();
	}
	
	void ConsoleType(void)
	{
		switch (System::IsNew3DS()) {
			case 0:
				MessageBox("Console: Old3DS")();
				break;
			case 1:
				MessageBox("Console: New3DS")();
				break;
		}
	}

	void WiFiStatus(void)
	{
		switch (System::IsConnectedToInternet()) {
			case 0:
				MessageBox("WiFi: Off")();
				break;
			case 1:
				MessageBox("WiFi: On")();
				break;
		}
	}
	
	void Information(MenuEntry *entry)
	{
		if(info.empty())
		{
			for (const Item &i : g_info)
				info.push_back(i.name);
		}
		Keyboard keyboard("Select which item you'd like to check", info);
		int choice = keyboard.Open();
		
		switch (choice) {
			case 0:
				TitleID();
				break;
			case 1:
				ConsoleType();
				break;
			case 2:
				WiFiStatus();
				break;
		}
	}
}
