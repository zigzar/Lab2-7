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

struct Node								// Узел списка
{
	int data;							// Данные
	Node* prev;							// Адрес предыдущего узла
	Node* next;							// Адрес следующего узла
};

struct List								// Список
{
	Node* head = nullptr;				// Первый элемент списка
	Node* tail = nullptr;				// Последний элемент списка
	int size = 0;						// Размер списка
};

const string dataFile = "data.txt";		// Файл с пользовательскими данными

// МЕНЮ. ГРАФИЧЕСКАЯ ЧАСТЬ //
int getAns();							// 
int getFillAns();						// 
int getDeleteAns();						// 
int getGetAns();						// 

// МЕНЮ. ЛОГИЧЕСКАЯ ЧАСТЬ //
void menu(List* list);					// 
void fillMenu(List* list);				// 
void deleteMenu();						// 
void getMenu();							// 

// ОБЩИЕ ДЕЙСТВИЯ //
void insert();							// 
void getByValue();						// 
void getByIndex();						// 
void delByValue();						// 
void delByIndex();						// 

// ФУНКЦИИ МАССИВА //
void getArr(int index);					// 
void deleteArr(int index);				// 
void insertArr(int value, int index);	// 
void pushBackArr(int value);			// 
void outArr();							// 
void fillArrRand();						// 
void fillMan(List* list);				// 
void fillFile(List* list);				// 

// ФУНКЦИИ СПИСКА //
Node* newNode(int data, Node* next = nullptr, Node* prev = nullptr);
void destroyList(List* list);
void pushBackList(List* list, int data);
void outList(List* list);
void popFrontList(List* list);

int* arr = nullptr;
int arrSize = 0;


int main()
{
	setlocale(LC_ALL, "russian");

	List list;
	menu(&list);
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

void menu(List* list) {
	int answer;
	do {
		answer = getAns();
		switch (answer)
		{
		case 0:
			fillMenu(list);
			break;
		case 1:
			insert();
			break;
		case 2:
			deleteMenu();
			break;
		case 3:
			getMenu();
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

void getMenu()
{
	int answer = getGetAns();
	switch (answer)
	{
	case 0:
		getByIndex();
		system("pause");
		break;
	case 1:
		getByValue();
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

void getByValue()
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
		getArr(index);
	}
	else
	{
		cerr << "Значение не найдено. Попробуйте ввести другое число: ";
		getByValue();
	}
}

void getByIndex()
{
	int index;
	cout << "Введите индекс: ";
	cin >> index;
	getArr(index);
}

void getArr(int index)
{
	cout << "Элемент " << arr[index] << " имеет индекс " << index << endl;
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
	arrSize = inputCheck();
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

void fillMan(List* list)
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
		pushBackList(list, stoi(number));
	}
		
}
void fillFile(List* list)
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
			pushBackList(list, stoi(number));
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

int getGetAns()
{
	int choice = 0;
	int options = 3;
	int ch;
	while (true) {
		system("cls");
		cout << "Выберите способ получения элемента:" << endl << endl;
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

void fillMenu(List* list)
{
	int answer = getFillAns();
	if (answer != 3)
	{
		destroyArr();
		destroyList(list);
	}

	switch (answer)
	{
	case 0:
		fillArrRand();
		break;
	case 1:
		fillMan(list);
		break;
	case 2:
		fillFile(list);
		break;
	case 3:
		return;
		break;
	}

	cout << "Ваш массив: ";
	outArr();
	cout << endl;
	cout << "Ваш список: ";
	outList(list);
	cout << endl;
	system("pause");
}

Node* newNode(int data, Node* next, Node* prev)
{
	Node* node = new Node;
	node->data = data;
	node->next = next;
	node->prev = prev;
	return node;
}

void destroyList(List* list)
{
	while (list->size)
	{
		popFrontList(list);
	}
}

void pushBackList(List* list, int data)
{
	if (list->size > 1)
	{
		Node* temp = list->tail;
		list->tail = newNode(data, nullptr, list->tail);
		temp->next = list->tail;
	}
	else if (list->size == 1)
	{
		list->tail = newNode(data, nullptr, list->tail);
		list->head->next = list->tail;
	}
	else
	{
		list->head = list->tail = newNode(data, list->head, list->tail);
	}
	list->size++;
}

void popFrontList(List* list)
{
	if (list->size > 1)
	{
		Node* temp = list->head;
		list->head = list->head->next;
		delete temp;
	}
	else if (list->size == 1)
	{
		Node* temp = list->head;
		list->tail = list->head = list->head->next;
		delete temp;
	}

	list->size--;
}

void outList(List* list)
{
	Node* p = list->head;
	while (p != nullptr)
	{
		cout << p->data << " ";
		p = p->next;
	}
	cout << endl;
}
