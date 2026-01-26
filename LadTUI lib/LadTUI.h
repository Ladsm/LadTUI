#pragma once
#include <string>
#include <vector>
#include <functional>

namespace ladtui {
	void DisplayTh3B3stD3v3lop3r();
	void drawLineRight();
	int intrandnum(int first, int last);
	class Menu {
	public:
		int sizeOfItems = 0;
		void DisplayMenu(std::string ItemsToShow[], int WhatsSelected, int amountofItems, int type);
		void MenuMenu(std::string ItemsToUse[], const std::vector<std::function<void()>>& callbacks, int amountofItems, int type);
		Menu() = default;
	};
	void drawLineRight();
	class Text {
	public:
		std::string text = "";
		size_t lengthOfString = text.size();
		void out(std::string TeXt);
		void outboxed(std::string TeXt);
		Text() = default;
		Text(std::string x) {
			text = x;
		}
	};
	class Switch {
	public:
		std::function<void()> OFF;
		std::function<void()> ON;
		std::string nametoswitch;
		bool onOrOff;
		void displaySwitch(Switch stuff);
		void switchSwitch(Switch stuff);
		Switch(std::string x, std::function<void()> y, std::function<void()> z, bool defaultstate)
			: nametoswitch(x), OFF(y), ON(z), onOrOff(defaultstate) {
		}
	};
}