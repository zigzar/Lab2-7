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
int getDeleteAns();

void menu();
void fillMenu();
void deleteMenu();

void insert();

void delByValue();
void delByIndex();
void deleteArr(int index);
void insertArr(int value, int index);
void pushBackArr(int value);
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
			insert();
			break;
		case 2:
			deleteMenu();
			break;
		case 3:
			
			break;
		case 4:
			exit(0);
			break;
		}
	} while (true);
}

void deleteMenu()
{
	int answer = getDeleteAns();
	switch (answer)
	{
	case 0:
		delByIndex();
		outArr();
		system("pause");
		break;
	case 1:
		delByValue();
		outArr();
		system("pause");
		break;
	case 2:
		return;
		break;
	}
}

void delByValue()
{
	int value;
	int index = -1;
	cout << "Введите значение: ";
	cin >> value;
	for (int i = 0; i < arrSize; i++)
	{
		if (arr[i] == value)
		{
			index = i;
			break;
		}
	}
	if (index != -1)
	{
		deleteArr(index);
	}
	else
	{
		cerr << "Значение не найдено. Попробуйте ввести другое число: ";
		delByValue();
	}
}

void delByIndex()
{
	int index;
	cout << "Введите индекс: ";
	cin >> index;
	deleteArr(index);
}

void outArr()
{
	for (int i = 0; i < arrSize; i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
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

void insert()
{
	int value;
	int index;

	cout << "Введите значение: ";
	value = inputCheck();
	cout << endl;

	cout << "Введите индекс, который займет значение: ";
	index = inputCheck();
	cout << endl << endl;

	insertArr(value, index);

	cout << "Массив/список после изменений:" << endl;
	outArr();
	system("pause");
}

void destroyArr()
{
	delete[] arr;
	arr = nullptr;
	arrSize = 0;
}

void insertArr(int value, int index)
{
	if (index >= arrSize)
	{
		pushBackArr(value);
	}
	else if (index >= 0)
	{
		int* newArr = new int[arrSize + 1];
		for (int i = arrSize; i > index; i--)
		{
			newArr[i] = arr[i - 1];
		}
		for (int i = 0; i < index; i++)
		{
			newArr[i] = arr[i];
		}

		delete[] arr;
		newArr[index] = value;
		arrSize++;
		arr = newArr;
	}
	else
	{
		cerr << "Указан неверный индекс. Пожалуйста введите другой индекс" << endl;
		system("pause");
		insert();
	}
}

void deleteArr(int index)
{
	int* newArr = new int[arrSize - 1];

	if (index > arrSize) index = arrSize;
	for (int i = 0; i < index; i++)
	{
		newArr[i] = arr[i];
	}
	for (int i = index+1; i < arrSize; i++)
	{
		newArr[i-1] = arr[i];
	}

	delete[] arr;
	arrSize--;
	arr = newArr;
}

void pushBackArr(int value) 
{
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
	cout << "Введите значения через пробел и нажмите Enter:" << endl;
	string buffer;
	string number;
	stringstream bufStream;
	getline(cin, buffer);
	bufStream << buffer;
	cin.clear();
	while (getline(bufStream, number, ' '))
	{
		pushBackArr(stoi(number));
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
		while (getline(bufStream, number, ' '))
		{
			pushBackArr(stoi(number));
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

int getDeleteAns()
{
	int choice = 0;
	int options = 3;
	int ch;
	while (true) {
		system("cls");
		cout << "Выберите способ удаления элемента:" << endl << endl;
		choice = (choice + options) % options;
		if (choice == 0) cout << "-> По индексу" << endl;
		else  cout << "   По индексу" << endl;

		if (choice == 1) cout << "-> По значению" << endl;
		else  cout << "   По значению" << endl;

		if (choice == 2) cout << "-> Назад" << endl;
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
		if (ch == 13) break;
	}
	system("cls");
	return choice;
}

void fillMenu()
{
	int answer = getFillAns();
	if (answer != 3) destroyArr();

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