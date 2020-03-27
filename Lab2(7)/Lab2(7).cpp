#include <iostream>
#include <fstream>
#include <ctime>
#include <chrono>
#include <conio.h>
#include <Windows.h>
#include "inputCheck.h"

using namespace std;

struct List
{
	int data;
	List* prev;
	List* next;
};

const char dataFile[] = "data.txt";

int getAns();
int getFillAns();

void menu();
void fillMenu();

void outArr(int* arr, int size);
void fillArrRand(int* arr, int size);
void fillArrMan(int* arr, int size);
void fillArrFile(int* arr, int size);


int* arr = nullptr;
int arrsize = 0;
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

void outArr(int* arr, int size)
{
	for (int i = 0; i < size; i++)
	{
		cout << arr[i] << " ";
	}
}
void fillArrRand(int* arr, int size)
{
	for (int i = 0; i < size; i++)
	{
		arr[i] = rand() % 100;
	}
}
void fillArrMan(int* arr, int size)
{
	cout << "Введите значения: " << endl;
	for (int i = 0; i < size; i++)
	{
		cout << "Введите arr[" << i << "] ";
		arr[i] = inputCheck();
	}
}
void fillArrFile(int* arr, int size)
{
	ifstream fin;
	try
	{
		fin.open(dataFile);
		for (int i = 0; i < size; i++)
		{
			if (fin.eof()) {
				cout << "В файле недостаточно чисел. Пожалуйста, введите больше чисел в файл и нажмите Enter" << endl;
				system("pause");
				fillMenu();
			}
			fin >> arr[i];
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
	int options = 3;
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
	int size;
	cout << "Введите размерность массива" << endl;
	cin >> size;
	int* arr = new int[size];

	int answer = getFillAns();

	switch (answer)
	{
	case 0:
		fillArrRand(arr, size);
		break;
	case 1:
		fillArrMan(arr, size);
		break;
	case 2:
		fillArrFile(arr, size);
		break;
	default:
		break;
	}

	cout << "Ваш массив/список: ";
	outArr(arr, size);
	cout << endl;
	system("pause");
}