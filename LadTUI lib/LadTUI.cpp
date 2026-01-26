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
	int intrandnum(int first, int last) {
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> distrib(first, last);
		return distrib(gen);
	}
	void Menu::DisplayMenu(std::string ItemsToShow[], int WhatsSelected, int amountofItems) {
		consoleUtils Tils;
		HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
		for (int i = 0; i < amountofItems; ++i) {
			std::string prefix = "  ";
			if ((i + 1) == WhatsSelected) {
				prefix = "->";
			}
			std::string output = prefix + ItemsToShow[i];
			std::cout << std::left << std::setw(MENU_ITEM_WIDTH + 2) << output << '\n';
		}
		Tils.CursorUp(amountofItems);
		std::cout << std::flush;
	}
	void Menu::MenuMenu(std::string ItemsToUse[], const std::vector<std::function<void()>>& callbacks, int amountofItems) {
		consoleUtils Tils;
		int selected = 1;
		int keypressed = 0;
		while (true) {
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
					Tils.CursorDown(amountofItems);
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
		consoleUtils Tils;
		const wchar_t* OnStr = L"▓▒░";
		const wchar_t* OffStr = L"░▒";
		int originalMode = _setmode(_fileno(stdout), _O_U16TEXT);
		std::wcout << stuff.nametoswitch.c_str() << L'\n';
		if (stuff.onOrOff == true) {
			std::wcout << L"ON";
			std::wcout << OnStr << L'\n';
		}
		else {
			std::wcout << OffStr;
			std::wcout << L"OFF" << L'\n';
		}
		(void)_setmode(_fileno(stdout), originalMode);
		Tils.CursorUp(2);
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
	int consoleUtils::getConsoleWidth() {
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		if (GetConsoleScreenBufferInfo(hConsole, &csbi)) {
			int width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
			return width;
		}
		else {
			std::cout << "cry about it lol\n";
			return 0;
		}
	}
	int consoleUtils::getConsoleHeight() {
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		if (GetConsoleScreenBufferInfo(hConsole, &csbi)) {
			int height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
			return height;
		}
		else {
			std::cout << "cry about it lol\n";
			return 0;
		}
	}
	void consoleUtils::drawLineRight() {
		int prevMode = _setmode(_fileno(stdout), _O_U16TEXT);
		for (int i = 0; i < getConsoleWidth(); i++) {
			std::wcout << L'─';
		}
		(void)_setmode(_fileno(stdout), prevMode);
		std::cout << '\n';
	}
	void consoleUtils::BackgroundDraw(int color) {
		HANDLE ColoR = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		GetConsoleScreenBufferInfo(ColoR, &csbi);
		COORD start_pos = csbi.dwCursorPosition;

	 /* okay, im sorry for useing comments but its needed here due to MADIC NUMBERS and how weird the code looks.
		Theres no good way I can find to make this better, I dont want to make a wall of vars
		and enums wont work here, sorry :(.					-Ladsm */
		switch (color) { // background draw
		   /* Format: <Background color>-<draw-On color> */
		case 1:
			SetConsoleTextAttribute(ColoR, 0); //Black-White
			break;
		case 2:
			SetConsoleTextAttribute(ColoR, 255); //White-Black
			break;
		case 3:
			SetConsoleTextAttribute(ColoR, 17); //Blue Dark-White
			break;
		case 4:
			SetConsoleTextAttribute(ColoR, 51); //Cyan-White
			break;
		case 5:
			SetConsoleTextAttribute(ColoR, 238); //Yellow-Red / HOYTDAWG
			break;
		case 6:
			SetConsoleTextAttribute(ColoR, 153); //Blue Bright-White
			break;
		case 7:
			SetConsoleTextAttribute(ColoR, 221); //Pink-White
			break;
		default:
			SetConsoleTextAttribute(ColoR, 0); //Black-White
			break;
		}

		int prevMode = _setmode(_fileno(stdout), _O_U16TEXT);
		for (int i = 0; i < getConsoleHeight(); i++) {
			for (int i = 0; i < getConsoleWidth(); i++) {
				std::wcout << L'█';
			}
			std::wcout << L'\n';
		}
		(void)_setmode(_fileno(stdout), prevMode);
		SetConsoleCursorPosition(ColoR, start_pos);
		std::cout << std::flush;

		switch (color) { // draw on background
		case 1:
			SetConsoleTextAttribute(ColoR, 7); //Black-White
			break;
		case 2:
			SetConsoleTextAttribute(ColoR, 240); //White-Black
			break;
		case 3:
			SetConsoleTextAttribute(ColoR, 31); //Blue Dark-White
			break;
		case 4:
			SetConsoleTextAttribute(ColoR, 63); //Cyan-White
			break;
		case 5:
			SetConsoleTextAttribute(ColoR, 228); //Yellow-Red / HOYTDAWG
			break;
		case 6:
			SetConsoleTextAttribute(ColoR, 159); //Blue Bright-White
			break;
		case 7:
			SetConsoleTextAttribute(ColoR, 223); //Pink-White
			break;
		default:
			SetConsoleTextAttribute(ColoR, 7); //Black-White
			break;
		}
	}
	void consoleUtils::CursorUp(int TimesToGoUp) {
		HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		if (GetConsoleScreenBufferInfo(hStdout, &csbi)) {
			for (int i = 0; i < TimesToGoUp; i++) {
				csbi.dwCursorPosition.Y--;
			}
			csbi.dwCursorPosition.X = 0;
			SetConsoleCursorPosition(hStdout, csbi.dwCursorPosition);
		}
	}
	void consoleUtils::CursorDown(int TimesToGoDown) {
		HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		if (GetConsoleScreenBufferInfo(hStdout, &csbi)) {
			for (int i = 0; i < TimesToGoDown; i++) {
				csbi.dwCursorPosition.Y++;
			}
			csbi.dwCursorPosition.X = 0;
			SetConsoleCursorPosition(hStdout, csbi.dwCursorPosition);
		}
	}
}