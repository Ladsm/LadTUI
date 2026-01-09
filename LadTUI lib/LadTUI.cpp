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


	void Menu::DisplayMenu(std::string ItemsToShow[], int WhatsSelected, int amountofItems) {
		for (int i = 0; i < amountofItems; ++i) {
			if ((i + 1) == WhatsSelected)
				std::cout << "->" << ItemsToShow[i] << '\n';
			else
				std::cout << "  " << ItemsToShow[i] << '\n';
		}
	}

	void Menu::MenuMenu(std::string ItemsToUse[], const std::vector<std::function<void()>>& callbacks, int amountofItems) {
		int selected = 1;
		int keypressed = 0;
		while (true) {
			ClearConsole();
			DisplayMenu(ItemsToUse, selected, amountofItems);
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