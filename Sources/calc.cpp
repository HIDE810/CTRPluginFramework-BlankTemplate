#include "common.hpp"

namespace CTRPluginFramework
{
	u32 data;
	int hex1, hex2, choice, ans;
	std::string result;

	static const std::vector<Item> g_calc =
	{
		{"+"},
		{"-"},
		{"×"},
		{"÷"}
	};
	
	void Calculate(void)
	{
		switch (choice) {
			case 0:
				ans = hex1+hex2;
				break;
			case 1:
				ans = hex1-hex2;
				break;
			case 2:
				ans = hex1*hex2;
				break;
			case 3:
				ans = hex1/hex2;
				break;
		}
	}
	
	void Calculator(MenuEntry *entry)
	{
		Keyboard keyboard("Enter the first number (in hex):");
		if (keyboard.Open(data) != -1)
		{
			hex1 = data;
			static StringVector calc;
			
			if (calc.empty()) {
				for (const Item &i : g_calc)
					calc.push_back(i.name);
			}
			Keyboard keyboard("Enter the calculating option:", calc);
			choice = keyboard.Open();
			
			if (choice != -1)
			{
				Keyboard keyboard("Enter the second number (in hex):");
				if (keyboard.Open(data) != -1)
				{
					hex2 = data;
					Calculate();
					result = std::to_string(ans);
					MessageBox("Result: " + result)();
				}
				else choice = -1;
			}
			else data = -1;
		}
	}
}
				