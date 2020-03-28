#include <iostream>
#include <sstream>
#include <fstream>
#include <ctime>
#include <chrono>
#include <conio.h>
#include <Windows.h>
#include <string>
#include "inputCheck.h"

using namespace std;

struct List
{
	int data;
	List* prev;
	List* next;
};

const string dataFile = "data.txt";

int getAns();
int getFillAns();

void menu();
void fillMenu();

void deleteArr();
void push_back_arr();
void outArr();
void fillArrRand();
void fillArrMan();
void fillArrFile();


int* arr = nullptr;
int arrSize = 0;
List list;

int main()
{
	setlocale(LC_ALL, "russian");
	menu();
}

int getAns() {
	int choice = 0;
	int options = 5;
	int ch;
	while (true) {
		system("cls");
		choice = (choice + options) % options;
		cout << "Вверх/w и " << "вниз/s для перемещения" << endl;
		cout << "Enter для выбора" << endl << endl;

		if (choice == 0) cout << "-> Создать массив/список" << endl;
		else  cout << "   Создать массив/список" << endl;

		if (choice == 1) cout << "-> Добавить элемент" << endl;
		else  cout << "   Добавить элемент" << endl;

		if (choice == 2) cout << "-> Удалить элемент" << endl;
		else  cout << "   Удалить элемент" << endl;

		if (choice == 3) cout << "-> Получить элемент" << endl;
		else  cout << "   Получить элемент" << endl;

		if (choice == 4) cout << "-> Выход" << endl;
		else  cout << "   Выход" << endl;

		ch = _getch();
		if (ch == 224)
		{
			ch = _getch();
			if (ch == 80) choice++;
			if (ch == 72) choice--;
		}
		if (ch == 119) choice--;
		if (ch == 115) choice++;
		if (ch == 13) break;
	}
	system("cls");
	return choice;
}

void menu() {
	int answer;
	do {
		answer = getAns();
		switch (answer)
		{
		case 0:
			fillMenu();
			break;
		case 1:

			break;
		case 2:
			
			break;
		case 3:
			
			break;
		case 4:
			exit(0);
			break;
		}
	} while (true);
}

void outArr()
{
	for (int i = 0; i < arrSize; i++)
	{
		cout << arr[i] << " ";
	}
}
void fillArrRand()
{
	cout << "Введите размерность массива" << endl;
	cin >> arrSize;
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());
	arr = new int[arrSize];
	for (int i = 0; i < arrSize; i++)
	{
		arr[i] = rand() % 100;
	}
}

void deleteArr()
{
	delete[] arr;
	arr = nullptr;
	arrSize = 0;
}

void push_back_arr(int value) {
	int* newArr = new int[arrSize + 1];

	for (int i = 0; i < arrSize; i++)
	{
		newArr[i] = arr[i];
	}

	delete[] arr;
	newArr[arrSize] = value;
	arrSize++;
	arr = newArr;
}

void fillArrMan()
{
	cout << "Введите значения через пробел и нажмите Enter: " << endl;
	string buffer;
	string number;
	stringstream bufStream;
	getline(cin, buffer);
	bufStream << buffer;
	cin.clear();
	while (getline(bufStream, number, ' '))
	{
		push_back_arr(stoi(number));
	}
		
}
void fillArrFile()
{
	ifstream fin;
	try
	{
		fin.open(dataFile);
		string buffer;
		string number;
		stringstream bufStream;
		getline(fin, buffer);
		bufStream << buffer;
		fin.clear();
		while (getline(bufStream, number, ' '))
		{
			push_back_arr(stoi(number));
		}
		fin.close();
	}
	catch (const exception&)
	{
		cout << "Ошибка открытия файла" << endl;
		ofstream fout;
		fout.open(dataFile);
		fout.close();
	}
}

int getFillAns() {
	int choice = 0;
	int options = 4;
	int ch;
	while (true) {
		system("cls");
		cout << "Как вы хотите заполнить массив? (ESC для выхода в главное меню)" << endl << endl;
		choice = (choice + options) % options;
		if (choice == 0) cout << "-> Случайно" << endl;
		else  cout << "   Случайно" << endl;

		if (choice == 1) cout << "-> Вручную" << endl;
		else  cout << "   Вручную" << endl;

		if (choice == 2) cout << "-> Прочитать из файла" << endl;
		else  cout << "   Прочитать из файла" << endl;

		if (choice == 3) cout << "-> Назад" << endl;
		else  cout << "   Назад" << endl;

		ch = _getch();
		if (ch == 224)
		{
			ch = _getch();
			if (ch == 80) choice++;
			if (ch == 72) choice--;
		}
		if (ch == 119)
		{
			choice--;
		}
		if (ch == 115)
		{
			choice++;
		}
		if (ch == 27) menu();
		if (ch == 13) break;
	}
	system("cls");
	return choice;
}

void fillMenu()
{
	int answer = getFillAns();
	if (answer != 3) deleteArr();

	switch (answer)
	{
	case 0:
		fillArrRand();
		break;
	case 1:
		fillArrMan();
		break;
	case 2:
		fillArrFile();
		break;
	case 3:
		return;
		break;
	}

	cout << "Ваш массив/список: ";
	outArr();
	cout << endl;
	system("pause");
}