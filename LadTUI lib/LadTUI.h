#pragma once
#include <string>
#include <vector>
#include <functional>

namespace ladtui {
	void DisplayTh3B3stD3v3lop3r();
	int intrandnum(int first, int last);
	class Menu {
	public:
		int sizeOfItems = 0;
		void DisplayMenu(std::string ItemsToShow[], int WhatsSelected, int amountofItems);
		void MenuMenu(std::string ItemsToUse[], const std::vector<std::function<void()>>& callbacks, int amountofItems);
		Menu() = default;
	};
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
	class consoleUtils {
	public:
		int getConsoleWidth();
		int getConsoleHeight();
		void drawLineRight();
		void BackgroundDraw(int color);
		void CursorUp(int TimesToGoUp);
		void CursorDown(int TimesToGoDown);
		void FullScreen();
		void DelaySeconds(int seconds);
		void ClearScreen();
	};
	class NumericUpDown {
	public:
		void displayNumupdown(int currentNumber);
		int useNumupdown();
	};
}