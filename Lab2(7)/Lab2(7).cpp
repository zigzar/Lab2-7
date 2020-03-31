#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <ctime>
#include <chrono>
#include <conio.h>
#include <Windows.h>
#include <string>
#include "inputCheck.h"

using namespace std;

struct Node														// Узел списка
{
	int data;													// Данные
	Node* prev;													// Адрес предыдущего узла
	Node* next;													// Адрес следующего узла
};

struct List														// Список
{
	Node* head = nullptr;										// Первый элемент списка
	Node* tail = nullptr;										// Последний элемент списка
	int size = 0;												// Размер списка
};

struct Table													// Таблица времени
{
	float ArrCtn;												// Время создания массива
	float ArrIns;												// Время вставки элемента в массив
	float ArrDelVal;											// Время удаления элемента из массива по значению
	float ArrDelInd;											// Время удаления элемента из массива по индексу
	float ArrGetVal;											// Время получения элемента из массива значению
	float ArrGetInd;											// Время получения элемента из массива индексу
	float ListCtn;												// Время создания списка
	float ListIns;												// Время вставки элемента в список
	float ListDelVal;											// Время удаления элемента из списка по значению
	float ListDelInd;											// Время удаления элемента из списка по индексу
	float ListGetVal;											// Время получения элемента из списка по значению
	float ListGetInd;											// Время получения элемента из списка по индексу
};

const string dataFile = "data.txt";								// Файл с пользовательскими данными

// МЕНЮ. ГРАФИЧЕСКАЯ ЧАСТЬ //
int getAns();													// Выбрать пункт в главном меню
int getFillAns();												// Выбрать пункт в меню выбора заполнения массива
int getDeleteAns();												// Выбрать пункт в меню выбора удаления элемента
int getGetAns();												// Выбрать пункт в меню выбора получения элемента

// МЕНЮ. ЛОГИЧЕСКАЯ ЧАСТЬ //
void menu(List* list, int*& arr, int& arrSize);					// Главное меню
void fillMenu(List* list, int*& arr, int& arrSize);				// Меню заполнения массива
void deleteMenu(List* list, int*& arr, int& arrSize);			// Меню удаления элемента
void getMenu(List* list, int*& arr, int& arrSize);				// Меню получения элемента

// ОБЩИЕ ДЕЙСТВИЯ //
void fillRand(List* list, int*& arr, int& arrSize);				// Заполнить случайными числами
void fillMan(List* list, int*& arr, int& arrSize);				// Заполнить вручную
void fillFile(List* list, int*& arr, int& arrSize);				// Заполнить числами из файла
void insert(List* list, int*& arr, int& arrSize);				// Вставить значение
void getByValue(List* list, int*& arr, int& arrSize);			// Получить элемент по значению
void getByIndex(List* list, int*& arr, int& arrSize);			// Получить элемент по индексу
void delByValue(List* list, int*& arr, int& arrSize);			// Удалить элемент по значению
void delByIndex(List* list, int*& arr, int& arrSize);			// Удалить элемент по индексу
void showTable();												// Вывести в консоль таблицу времени

// ФУНКЦИИ МАССИВА //
void outArr(int*& arr, int& arrSize);							// Вывести массив в консоль
void destroyArr(int*& arr, int& arrSize);						// Удалить массив
void pushBackArr(int value, int*& arr, int& arrSize);			// Добавить элемент в конец массива
void insertArr(int value, int index, int*& arr, int& arrSize);	// Вставить элемент в массив
void deleteArrByIndex(int index, int*& arr, int& arrSize);		// Удалить элемент массива по индексу
void deleteArrByValue(int value, int*& arr, int& arrSize);		// Удалить элемент массива по значению
void getArrByIndex(int index, int*& arr, int& arrSize);			// Получить элемент массива по индексу
void getArrByValue(int value, int*& arr, int& arrSize);			// Получить элемент массива по значению

// ФУНКЦИИ СПИСКА //
Node* newNode(int data, Node* next, Node* prev);				// Создать новый узел списка
void outList(List* list);										// Вывести список в консоль
void destroyList(List* list);									// Удалить список
void pushBackList(List* list, int data);						// Добавить элемент в конец списка
void pushFrontList(List* list, int data);						// Добавить элемент в начало списка
void popBackList(List* list);									// Удалить элемент из конца списка
void popFrontList(List* list);									// Удалить элемент из начала списка
void insertList(List* list, int data, int index);				// Вставить элемент в список
void deleteListByIndex(List* list, int index);					// Удалить элемент списка по индексу
void deleteListByValue(List* list, int value);					// Удалить элемент списка по значению
void getListByIndex(List* list, int index);						// Получить элемент массива по индексу
void getListByValue(List* list, int value);						// Получить элемент массива по значению

Table timeTable;												// Таблица времени

int main()
{
	setlocale(LC_ALL, "russian");
	srand(time(NULL));
	int* arr = nullptr;											// Массив
	int arrSize = 0;											// Размер массива
	List list;													// Список
	menu(&list, arr, arrSize);
}

int getAns() {
	int choice = 0;
	int options = 6;
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

		if (choice == 4) cout << "-> Таблица времени" << endl;
		else  cout << "   Таблица времени" << endl;

		if (choice == 5) cout << "-> Выход" << endl;
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

void menu(List* list, int*& arr, int& arrSize) {
	int answer;
	do {
		answer = getAns();
		switch (answer)
		{
		case 0:
			fillMenu(list, arr, arrSize);
			break;
		case 1:
			insert(list, arr, arrSize);
			break;
		case 2:
			deleteMenu(list, arr, arrSize);
			break;
		case 3:
			getMenu(list, arr, arrSize);
			break;
		case 4:
			showTable();
			break;
		case 5:
			exit(0);
			break;
		}
	} while (true);
}

void deleteMenu(List* list, int*& arr, int& arrSize)
{
	int answer = getDeleteAns();
	switch (answer)
	{
	case 0:
		delByIndex(list, arr, arrSize);
		cout << "Массив после изменений:" << endl;
		outArr(arr, arrSize);
		cout << "Список после изменений:" << endl;
		outList(list);
		system("pause");
		break;
	case 1:
		delByValue(list, arr, arrSize);
		cout << "Массив после изменений:" << endl;
		outArr(arr, arrSize);
		cout << "Список после изменений:" << endl;
		outList(list);
		system("pause");
		break;
	case 2:
		return;
		break;
	}
}

void getMenu(List* list, int*& arr, int& arrSize)
{
	int answer = getGetAns();
	switch (answer)
	{
	case 0:
		getByIndex(list, arr, arrSize);
		system("pause");
		break;
	case 1:
		getByValue(list, arr, arrSize);
		system("pause");
		break;
	case 2:
		return;
		break;
	}
}

void delByValue(List* list, int*& arr, int& arrSize)
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
		auto ArrDelValStart = chrono::high_resolution_clock::now();
		deleteArrByValue(value, arr, arrSize);
		auto ArrDelValEnd = chrono::high_resolution_clock::now();
		timeTable.ArrDelVal = (ArrDelValEnd - ArrDelValStart).count();

		auto ListDelValStart = chrono::high_resolution_clock::now();
		deleteListByValue(list, value);
		auto ListDelValEnd = chrono::high_resolution_clock::now();
		timeTable.ListDelVal = (ListDelValEnd - ListDelValStart).count();
	}
	else
	{
		cerr << "Значение не найдено. Попробуйте ввести другое число." << endl;
		delByValue(list, arr, arrSize);
	}
}

void deleteArrByValue(int value, int*& arr, int& arrSize)
{
	for (int i = 0; i < arrSize; i++)
	{
		if (arr[i] == value)
		{
			deleteArrByIndex(i, arr, arrSize);
			break;
		}
	}
}

void delByIndex(List* list, int*& arr, int& arrSize)
{
	int index;
	cout << "Введите индекс: ";
	cin >> index;
	auto ArrDelIndStart = chrono::high_resolution_clock::now();
	deleteArrByIndex(index, arr, arrSize);
	auto ArrDelIndEnd = chrono::high_resolution_clock::now();
	timeTable.ArrDelInd = (ArrDelIndEnd - ArrDelIndStart).count();

	auto ListDelIndStart = chrono::high_resolution_clock::now();
	deleteListByIndex(list, index);
	auto ListDelIndEnd = chrono::high_resolution_clock::now();
	timeTable.ListDelInd = (ListDelIndEnd - ListDelIndStart).count();
}

void showTable()
{
	cout.setf(ios::fixed);
	cout.precision(3);
	cout << setw(100) << "Таблица времени выполнения действий над массивом и списком. Все данные указаны в с\n"
	<< setw(100) << "________________________________________________________________________________________________________________________\n";
	cout << setw(50) << "Массив" << setw(50) << "Список\n";
	cout << "Время создания\t\t\t\t" << setw(9) << timeTable.ArrCtn / 900000 << setw(49) << timeTable.ListCtn / 900000 << "\n";
	cout << "Время вставки элемента\t\t\t" << setw(9) << timeTable.ArrIns / 900000 << setw(49) << timeTable.ListIns / 900000 << "\n";
	cout << "Время удаления элемента по значению\t" << setw(9) << timeTable.ArrDelVal / 900000 << setw(49) << timeTable.ListDelVal / 900000 << "\n";
	cout << "Время удаления элемента по индексу\t" << setw(9) << timeTable.ArrDelInd / 900000 << setw(49) << timeTable.ListDelInd / 900000 << "\n";
	cout << "Время получения элемента по значению\t" << setw(9) << timeTable.ArrGetVal / 900000 << setw(49) << timeTable.ListGetVal / 900000 << "\n";
	cout << "Время получения элемента по индексу\t" << setw(9) << timeTable.ArrGetInd / 900000 << setw(49) << timeTable.ListGetInd / 900000 << "\n";
	cout << "\n\n";
	system("pause");
}

void getByValue(List* list, int*& arr, int& arrSize)
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
		auto ArrGetValStart = chrono::high_resolution_clock::now();
		getArrByValue(value, arr, arrSize);
		auto ArrGetValEnd = chrono::high_resolution_clock::now();
		timeTable.ArrGetVal = (ArrGetValEnd - ArrGetValStart).count();

		auto ListGetValStart = chrono::high_resolution_clock::now();
		getListByValue(list, value);
		auto ListGetValEnd = chrono::high_resolution_clock::now();
		timeTable.ListGetVal = (ListGetValEnd - ListGetValStart).count();
	}
	else
	{
		cerr << "Значение не найдено. Попробуйте ввести другое число." << endl;
		getByValue(list, arr, arrSize);
	}
}

void getArrByValue(int value, int*& arr, int& arrSize)
{
	for (int i = 0; i < arrSize; i++)
	{
		if (arr[i] == value)
		{
			getArrByIndex(i, arr, arrSize);
			break;
		}
	}
}

void getListByValue(List* list, int value)
{
	int index = 0;
	for (Node* p = list->head; p != nullptr; p = p->next, index++)
	{
		if (p->data == value) break;
	}

	cout << "Элемент " << value << " имеет индекс " << index << endl;
}

void getByIndex(List* list, int*& arr, int& arrSize)
{
	int index;
	cout << "Введите индекс: ";
	cin >> index;

	auto ArrGetIndStart = chrono::high_resolution_clock::now();
	getArrByIndex(index, arr, arrSize);
	auto ArrGetIndEnd = chrono::high_resolution_clock::now();
	timeTable.ArrGetInd = (ArrGetIndEnd - ArrGetIndStart).count();
	
	auto ListGetIndStart = chrono::high_resolution_clock::now();
	getListByIndex(list, index);
	auto ListGetIndEnd = chrono::high_resolution_clock::now();
	timeTable.ListGetInd = (ListGetIndEnd - ListGetIndStart).count();
}

void getArrByIndex(int index, int*& arr, int& arrSize)
{
	cout << "Элемент " << arr[index] << " имеет индекс " << index << endl;
}

void outArr(int*& arr, int& arrSize)
{
	for (int i = 0; i < arrSize; i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
}

void fillRand(List* list, int*& arr, int& arrSize)
{
	float arrayTime = 0;
	float listTime = 0;
	cout << "Введите размерность массива/списка: ";
	arrSize = inputCheck();
	arr = new int[arrSize];
	for (int temp, i = 0; i < arrSize; i++)
	{
		 temp = rand() % 100;

		 auto ArrRanCtnStart = chrono::high_resolution_clock::now();
		 arr[i] = temp;
		 auto ArrRanCtnEnd = chrono::high_resolution_clock::now();
		 arrayTime += (ArrRanCtnEnd - ArrRanCtnStart).count();

		 auto ListRanCtnStart = chrono::high_resolution_clock::now();
		 pushBackList(list, temp);
		 auto ListRanCtnEnd = chrono::high_resolution_clock::now();
		 listTime += (ListRanCtnEnd - ListRanCtnStart).count();
	}
	timeTable.ArrCtn = arrayTime;
	timeTable.ListCtn = listTime;
}

void fillMan(List* list, int*& arr, int& arrSize)
{
	float arrayTime = 0;
	float listTime = 0;
	cout << "Введите значения через пробел и нажмите Enter:" << endl;
	string buffer;
	string number;
	stringstream bufStream;
	getline(cin, buffer);
	bufStream << buffer;
	cin.clear();
	while (getline(bufStream, number, ' '))
	{
		auto ArrManCtnStart = chrono::high_resolution_clock::now();
		pushBackArr(stoi(number), arr, arrSize);
		auto ArrManCtnEnd = chrono::high_resolution_clock::now();
		arrayTime += (ArrManCtnEnd - ArrManCtnStart).count();

		auto ListManCtnStart = chrono::high_resolution_clock::now();
		pushBackList(list, stoi(number));
		auto ListManCtnEnd = chrono::high_resolution_clock::now();
		arrayTime += (ListManCtnEnd - ListManCtnStart).count();
	}
	timeTable.ArrCtn = arrayTime;
	timeTable.ListCtn = listTime;
}

void fillFile(List* list, int*& arr, int& arrSize)
{
	float arrayTime = 0;
	float listTime = 0;
	ifstream fin;
	try
	{
		fin.open(dataFile);
		if (!fin.is_open()) throw invalid_argument("Файл не существует");
		string buffer;
		string number;
		stringstream bufStream;
		getline(fin, buffer);
		bufStream << buffer;
		while (getline(bufStream, number, ' '))
		{
			auto ArrFileCtnStart = chrono::high_resolution_clock::now();
			pushBackArr(stoi(number), arr, arrSize);
			auto ArrFileCtnEnd = chrono::high_resolution_clock::now();
			arrayTime += (ArrFileCtnEnd - ArrFileCtnStart).count();

			auto ListFileCtnStart = chrono::high_resolution_clock::now();
			pushBackList(list, stoi(number));
			auto ListFileCtnEnd = chrono::high_resolution_clock::now();
			arrayTime += (ListFileCtnEnd - ListFileCtnStart).count();
		}
		fin.close();
	}
	catch (const invalid_argument&)
	{
		cout << "Ошибка открытия файла" << endl;
		ofstream fout;
		fout.open(dataFile);
		fout.close();
	}
	timeTable.ArrCtn = arrayTime;
	timeTable.ListCtn = listTime;
}

void insert(List* list, int*& arr, int& arrSize)
{
	int value;
	int index;

	cout << "Введите значение: ";
	value = inputCheck();
	cout << endl;

	cout << "Введите индекс, который займет значение: ";
	index = inputCheck();
	cout << endl << endl;

	auto ArrInsStart = chrono::high_resolution_clock::now();
	insertArr(value, index, arr, arrSize);
	auto ArrInsEnd = chrono::high_resolution_clock::now();
	timeTable.ArrIns = (ArrInsEnd - ArrInsStart).count();

	auto ListInsStart = chrono::high_resolution_clock::now();
	insertList(list, value, index);
	auto ListInsEnd = chrono::high_resolution_clock::now();
	timeTable.ListIns = (ListInsEnd - ListInsStart).count();

	cout << "Массив после изменений:" << endl;
	outArr(arr, arrSize);
	cout << "Список после изменений:" << endl;
	outList(list);
	system("pause");
}

void destroyArr(int*& arr, int& arrSize)
{
	delete[] arr;
	arr = nullptr;
	arrSize = 0;
}

void insertArr(int value, int index, int*& arr, int& arrSize)
{
	if (index < 0) index = 0;
	if (index >= arrSize)
	{
		pushBackArr(value, arr, arrSize);
	} 
	else 
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
}

void deleteArrByIndex(int index, int*& arr, int& arrSize)
{
	if (index < 0) index = 0;
	int* newArr = new int[arrSize - 1];

	if (index >= arrSize) index = arrSize-1;
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

void pushBackArr(int value, int*& arr, int& arrSize)
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

void fillMenu(List* list, int*& arr, int& arrSize)
{
	int answer = getFillAns();
	if (answer != 3)
	{
		destroyArr(arr, arrSize);
		destroyList(list);
	}

	switch (answer)
	{
	case 0:
		fillRand(list, arr, arrSize);
		break;
	case 1:
		fillMan(list, arr, arrSize);
		break;
	case 2:
		fillFile(list, arr, arrSize);
		break;
	case 3:
		return;
		break;
	}

	cout << "Ваш массив: ";
	outArr(arr, arrSize);
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

void pushFrontList(List* list, int data)
{
	if (list->size > 1)
	{
		Node* temp = list->head;
		list->head = newNode(data, list->head, nullptr);
		temp->prev = list->head;
	}
	else if (list->size == 1)
	{
		list->head = newNode(data, list->head, nullptr);
		list->tail->prev = list->head;
	}
	else
	{
		list->head = list->tail = newNode(data, list->head, list->tail);
	}
	list->size++;
}

void popBackList(List* list)
{
	if (list->size > 1)
	{
		Node* temp = list->tail;
		list->tail = list->tail->prev;
		list->tail->next = nullptr;
		delete temp;
	}
	else if (list->size == 1)
	{
		Node* temp = list->tail;
		list->tail = list->head = list->tail->prev;
		delete temp;
	}

	list->size--;
}

void popFrontList(List* list)
{
	if (list->size > 1)
	{
		Node* temp = list->head;
		list->head = list->head->next;
		list->head->prev = nullptr;
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

void insertList(List* list, int data, int index)
{
	if (index <= 0) pushFrontList(list, data);

	else if (index == list->size || index > list->size) pushBackList(list, data);

	else if (index <= list->size / 2)
	{
		Node* previous = list->head;
		for (int i = 0; i < index - 1; i++)
		{
			previous = previous->next;
		}

		Node* node = newNode(data, previous->next, previous);

		previous->next = node;
		Node* next = node->next;
		next->prev = node;

		list->size++;
	}

	else if (index > list->size / 2)
	{
		Node* next = list->tail;
		for (int i = list->size - 1; index < i; i--)
		{
			next = next->prev;
		}

		Node* node = newNode(data, next, next->prev);

		next->prev = node;
		Node* previous = node->prev;
		previous->next = node;

		list->size++;
	}
}

void deleteListByIndex(List* list, int index)
{
	if (index <= 0) popFrontList(list);

	else if (index >= list->size-1) popBackList(list);

	else if (index <= list->size / 2)
	{
		Node* previous = list->head;
		for (int i = 0; i < index - 1; i++)
		{
			previous = previous->next;
		}

		Node* toDelete = previous->next;
		previous->next = toDelete->next;
		Node* next = toDelete->next;
		delete toDelete;
		next->prev = previous;

		list->size--;
	}

	else if (index > list->size / 2)
	{
		Node* next = list->tail;
		for (int i = list->size - 1; index < i; i--)
		{
			next = next->prev;
		}

		Node* toDelete = next->prev;
		next->prev = toDelete->prev;
		Node* previous = toDelete->prev;
		delete toDelete;
		previous->next = next;

		list->size--;
	}
}

void deleteListByValue(List* list, int value)
{
	if (list->tail->data == value)
	{
		popBackList(list);
	}
	else if (list->head->data == value)
	{
		popFrontList(list);
	}
	else
	{
		for (Node* p = list->head->next; p != nullptr; p = p->next)
		{
			if (p->data == value)
			{
				p->prev->next = p->next;
				p->next->prev = p->prev;
				delete p;
				break;
			}
		}
	}

	list->size--;
}

void getListByIndex(List* list, int index)
{
	int number = NULL;

	if (index < 0)
	{
		cerr << "Индекс выходит за рамки списка. Пожалуйста, введите индекс >0" << endl;
		system("pause");
		return;
	}

	if (index >= list->size)
	{
		cerr << "Индекс выходит за рамки списка. Пожалуйста, введите индекс в пределах списка" << endl;
		system("pause");
		return;
	}

	if (index == 0) number = list->head->data;

	else if (index == list->size - 1) number = list->tail->data;

	else if (index <= list->size / 2)
	{
		Node* previous = list->head;
		for (int i = 0; i < index - 1; i++)
		{
			previous = previous->next;
		}

		number = previous->next->data;
	}

	else if (index > list->size / 2)
	{
		Node* next = list->tail;
		for (int i = list->size - 1; index < i; i--)
		{
			next = next->prev;
		}

		number = next->data;
	}

	cout << "Элемент " << number << " имеет индекс " << index << endl;
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
