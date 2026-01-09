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

namespace ladtui {
	static void ClearConsole()
	{
		HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
		if (hOut == INVALID_HANDLE_VALUE) return;

		CONSOLE_SCREEN_BUFFER_INFO csbi;
		if (!GetConsoleScreenBufferInfo(hOut, &csbi)) return;

		DWORD cellCount = static_cast<DWORD>(csbi.dwSize.X) * csbi.dwSize.Y;
		DWORD count = 0;
		COORD homeCoords = { 0, 0 };

		FillConsoleOutputCharacterA(hOut, ' ', cellCount, homeCoords, &count);
		FillConsoleOutputAttribute(hOut, csbi.wAttributes, cellCount, homeCoords, &count);
		SetConsoleCursorPosition(hOut, homeCoords);
	}


	const int MENU_ITEM_WIDTH = 20;

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
			std::cout << std::left << std::setw(MENU_ITEM_WIDTH + 2) << output << std::endl;

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

	void Menu::drawLineRight() {
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		int LineHorizontal;
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
		LineHorizontal = csbi.srWindow.Right - csbi.srWindow.Left + 1;
		for (int i = 0; i < LineHorizontal; i++) {
			std::cout << '-';
		}
		std::cout << '\n';
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
		_setmode(_fileno(stdout), prevMode);
		std::cout << TeXt;
		prevMode = _setmode(_fileno(stdout), _O_U16TEXT);
		std::wcout << pipeLD << '\n';
		std::wcout << pipeDR;
		for (size_t i = 0; i < TeXt.size(); i++) {
			std::wcout << pipeLH;
		}
		std::wcout << pipeDL << '\n';
		_setmode(_fileno(stdout), prevMode);
		return;
	}
}