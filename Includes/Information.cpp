#include "CTRPluginFramework.hpp"

namespace CTRPluginFramework
{
	using StringVector = std::vector<std::string>;
	static StringVector info;
	
	struct Info
	{
		const char *type;
	};
	
	static const std::vector<Info> g_info =
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
	
	void information(MenuEntry *entry)
	{
		if(info.empty())
		{
			for (const Info &i : g_info)
				info.push_back(i.type);
		}
		Keyboard keyboard("Select the item you want to check.", info);
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
