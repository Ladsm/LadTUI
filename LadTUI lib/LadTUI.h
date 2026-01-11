#pragma once
#include <string>
#include <vector>
#include <functional>

namespace ladtui {
	class Menu {
	public:
		int sizeOfItems = 0;
		void DisplayMenu(std::string ItemsToShow[], int WhatsSelected, int amountofItems, int type);
		void MenuMenu(std::string ItemsToUse[], const std::vector<std::function<void()>>& callbacks, int amountofItems, int type);
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
		bool onOrOff = false;
		std::string nametoswitch;
		const std::function<void()>& OFF;
		const std::function<void()>& ON;
		void displaySwitch(Switch stuff);
		void switchSwitch(Switch stuff);
		Switch(std::string x, std::function<void()> y, std::function<void()> z, bool defaultstate)
			: nametoswitch(x), OFF(y), ON(z), onOrOff(defaultstate) {
		}
	};

}