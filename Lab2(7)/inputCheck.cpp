#include <iostream>
#include "inputCheck.h"

int inputCheck() {
	while (true) {
		int input;
		std::cin >> input;
		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(std::cin.rdbuf()->in_avail());
			setlocale(0, "russian");
			std::cout << std::endl << "������ �����. ����������, ���������� ������ ����� ��������� ������� � ������������� ����: ";
		}
		else {
			std::cin.ignore(std::cin.rdbuf()->in_avail());
			return input;
		}
	}
}
