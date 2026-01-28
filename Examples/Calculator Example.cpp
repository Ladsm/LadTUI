#include "LadTUI.h"
#include <iostream>

class calculator {
public:
	int result = 0;
	int calculate(int num1, char operation, int num2) {
		switch (operation) {
		case '+':
			result = num1 + num2;
			break;
		case '-':
			result = num1 - num2;
			break;
		case '*':
			result = num1 * num2;
			break;
		case '/':
			result = num1 / num2;
			break;
		default:
			result = 0;
			std::cout << ":(";
			break;
		}
		return result;
	}
};

int main() {
	ladtui::consoleUtils tils;
	int num1 = 0; int num2 = 0;
	char operation = ' ';
	ladtui::Menu Cmenu;
	ladtui::NumericUpDown Cupdown;
	calculator c;
	std::string items[5] = { "Add", "Subtrack", "Multiplication", "Devide", "Exit"};
    std::vector<std::function<void()>> OperationMenu = {
        [&operation]() { operation = '+'; },
        [&operation]() { operation = '-'; },
        [&operation]() { operation = '*'; },
        [&operation]() { operation = '/'; },
		[]() { exit(1); }
    };
	tils.DelaySeconds(2);
start:
	tils.ClearScreen();
	tils.BackgroundDraw(3);
	std::cout << "Calculator application\n";
	num1 = Cupdown.useNumupdown();
	Cmenu.MenuMenu(items, OperationMenu, 5);
	num2 = Cupdown.useNumupdown();
	c.calculate(num1, operation, num2);
	std::cout << c.result << '\n';
	tils.DelaySeconds(1);
	goto start;
	return 0;
}