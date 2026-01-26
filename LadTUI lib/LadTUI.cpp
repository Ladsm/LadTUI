#include "LadTUI.h"
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <locale>
#include <codecvt>
#include <ctime>
#include <thread>
#include <io.h>
#include <fcntl.h>
#include <WinUser.h>
#include <cstdlib>
#include <functional>
#include <vector>
#include <iomanip>
#include <random>
#include <limits>

namespace ladtui {
	const int MENU_ITEM_WIDTH = 10;

	void DisplayTh3B3stD3v3lop3r() {
	  std::wstring L1 = L"\n ▄█        ▄████████ ███████▄     ▄████████    ▄▄▄▄███▄▄▄▄    \n";
		std::wstring L2 = L"███        ███   ███ ███  ▀███   ███    ███  ▄██▀▀▀███▀▀▀██▄  \n";
		std::wstring L3 = L"███        ███   ███ ███   ███   ███    █▀   ███   ███   ███  \n";
		std::wstring L4 = L"███        ███   ███ ███   ███   ███         ███   ███   ███  \n";
		std::wstring L5 = L"███      ▀██████████████   ████████████████  ███   ███   ███  \n";
		std::wstring L6 = L"███        ███   ███ ███   ███          ███  ███   ███   ███  \n";
		std::wstring L7 = L"███▌    ▄  ███   ███ ███  ▄███    ▄█    ███  ███   ███   ███  \n";
		std::wstring L8 = L"█████▄▄██  ███   █▀  ███████▀   ▄████████▀    ▀█   ▀▀▀   █▀   \n";
		std::wstring L9 = L"▀                                                             \n";
	   std::wstring L10 = L"                  https://ladsm.neocities.org/              \n";
	   std::wstring Lines = L1 + L2 + L3 + L4 + L5 + L6 + L7 + L8 + L9 + L10;
		int prevMode = _setmode(_fileno(stdout), _O_U16TEXT);
		std::wcout << Lines;
		(void)_setmode(_fileno(stdout), prevMode);
	}
	void drawLineRight() {
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		int LineHorizontal;
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
		LineHorizontal = csbi.srWindow.Right - csbi.srWindow.Left + 1;
		int prevMode = _setmode(_fileno(stdout), _O_U16TEXT);
		for (int i = 0; i < LineHorizontal; i++) {
			std::wcout << L'─';
		}
		(void)_setmode(_fileno(stdout), prevMode);
		std::cout << '\n';
	}
	int intrandnum(int first, int last) {
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> distrib(first, last);
		return distrib(gen);
	}
	void Menu::DisplayMenu(std::string ItemsToShow[], int WhatsSelected, int amountofItems, int type) {
		HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(color, 7);
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		GetConsoleScreenBufferInfo(color, &csbi);
		COORD start_pos = csbi.dwCursorPosition;
		for (int i = 0; i < amountofItems; ++i) {
			SetConsoleTextAttribute(color, 7);
			std::string prefix = "  ";
			if ((i + 1) == WhatsSelected) {
				prefix = "->";
				if (type == 2) {
					prefix = "";
				} if (type == 2 || type == 3) {
					SetConsoleTextAttribute(color, 240);
				}
			}
			if (type == 2) {
				prefix = "";
			}
			std::string output = prefix + ItemsToShow[i];
			std::cout << std::left << std::setw(MENU_ITEM_WIDTH + 2) << output << '\n';

			SetConsoleTextAttribute(color, 7);
		}
		SetConsoleCursorPosition(color, start_pos);
		std::cout << std::flush;
	}
	void Menu::MenuMenu(std::string ItemsToUse[], const std::vector<std::function<void()>>& callbacks, int amountofItems, int type) {
		int selected = 1;
		int keypressed = 0;
		while (true) {
			DisplayMenu(ItemsToUse, selected, amountofItems, type);
			keypressed = _getch();
			if (keypressed == 0 || keypressed == 0xE0) {
				keypressed = _getch();
				switch (keypressed) {
				case 72: // up
					if (selected > 1) {
						selected--;
					}
					break;
				case 80: // down
					if (selected < amountofItems) {
						selected++;
					}
					break;
				}
			}
			else {
				if (keypressed == '\r') {
					int idx = selected - 1;
					if (idx >= 0 && idx < static_cast<int>(callbacks.size()) && callbacks[idx]) {
						callbacks[idx]();
					}
					return;
				}
			}
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
		}
	}
	void Text::out(std::string TeXt) {
		std::cout << TeXt;
	}
	void Text::outboxed(std::string TeXt) {
		const wchar_t pipeUR = L'╔';
		const wchar_t pipeUL = L'╗';
		const wchar_t pipeDR = L'╚';
		const wchar_t pipeDL = L'╝';
		const wchar_t pipeLH = L'═';
		const wchar_t pipeLD = L'║';
		int prevMode = _setmode(_fileno(stdout), _O_U16TEXT);
		std::wcout << pipeUR;
		for (size_t i = 0; i < TeXt.size(); i++) {
			std::wcout << pipeLH;
		}
		std::wcout << pipeUL;
		std::wcout << '\n' << pipeLD;
		(void)_setmode(_fileno(stdout), prevMode);
		std::cout << TeXt;
		prevMode = _setmode(_fileno(stdout), _O_U16TEXT);
		std::wcout << pipeLD << '\n';
		std::wcout << pipeDR;
		for (size_t i = 0; i < TeXt.size(); i++) {
			std::wcout << pipeLH;
		}
		std::wcout << pipeDL << '\n';
		(void)_setmode(_fileno(stdout), prevMode);
		return;
	}
	void Switch::displaySwitch(Switch stuff)
	{
		HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(color, 7);
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		GetConsoleScreenBufferInfo(color, &csbi);
		COORD start_pos = csbi.dwCursorPosition;
		const wchar_t* OnStr = L"▓▒░";
		const wchar_t* OffStr = L"░▒";
		int originalMode = _setmode(_fileno(stdout), _O_U16TEXT);
		std::wcout << stuff.nametoswitch.c_str() << L'\n';
		if (stuff.onOrOff == true) {
			SetConsoleTextAttribute(color, 240);
			std::wcout << L"ON";
			SetConsoleTextAttribute(color, 7);
			std::wcout << OnStr << L'\n';
		}
		else {
			std::wcout << OffStr;
			SetConsoleTextAttribute(color, 240);
			std::wcout << L"OFF" << L'\n';
			SetConsoleTextAttribute(color, 7);
		}
		(void)_setmode(_fileno(stdout), originalMode);
		SetConsoleCursorPosition(color, start_pos);
		std::cout << std::flush;
		return;
	}
	void Switch::switchSwitch(Switch stuff) {
		int keypressed = 0;
		while (true) {
			displaySwitch(stuff);
			keypressed = _getch();
			if (keypressed == 0 || keypressed == 0xE0) {
				keypressed = _getch();
				switch (keypressed) {
				case 75: // left
					stuff.onOrOff = true;
					break;
				case 77: // right
					stuff.onOrOff = false;
					break;
				}
			}
			else {
				if (keypressed == '\r') {
					if (stuff.onOrOff == true) {
						std::cout << "\n\n";
						stuff.ON();
						return;
					}
					else {
						std::cout << "\n\n";
						stuff.OFF();
						return;
					}
				}
			}
		}
	}
}