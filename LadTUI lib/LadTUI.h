#pragma once
#include <string>
#include <vector>
#include <functional>

namespace ladtui {
	class Menu {
	public:
		int sizeOfItems = 0;
		void DisplayMenu(std::string ItemsToShow[], int WhatsSelected, int amountofItems);
		void MenuMenu(std::string ItemsToUse[], const std::vector<std::function<void()>>& callbacks, int amountofItems);
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

}