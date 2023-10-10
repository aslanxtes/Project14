#include <iostream> 
#include <fstream> 
#include <string> 
#include <cstdlib> 
#include <locale> 

using namespace std;

struct todo {
	int id;
	string task;
};

int ID;

void addtodo();
void print(todo s);
void readData();
int searchData();
void deleteData();
void updateData();

void addtodo() {
	setlocale(LC_ALL, "Russian");
	system("cls");
	cout << "\t\t\t Добро пожаловать в ваш список дел " << endl;
	todo newTodo;
	cout << "\n\tВведите крайний срок выполнения, затем новую задачу через двоеточие: ";
	cin.ignore();
	getline(cin, newTodo.task);
	ID++;
	ofstream write;
	write.open("todo.txt", ios::app);
	write << "\n" << ID;
	write << "\n" << newTodo.task;
	write.close();

	write.open("id.txt");
	write << ID;
	write.close();

	char ch;
	cout << "Вы хотите добавить еще одну задачу? (y/n)" << endl;
	cin >> ch;

	if (ch == 'y') {
		addtodo();
	}
	else {
		cout << "\n\tЗадача успешно добавлена";
		return;
	}
}

void print(todo s) {
	cout << "\n\tID is: " << s.id;
	cout << "\n\tTask is: " << s.task << "\n\t";
}

void readData() {
	system("cls");
	setlocale(LC_ALL, "Russian");
	cout << "\t\t\t Добро пожаловать в ваш список дел " << endl;
	todo newTodo;
	ifstream read;
	read.open("todo.txt");
	cout << "\n\t Ваши текущие задачи в списке";

	while (read >> newTodo.id) {
		read.ignore();
		getline(read, newTodo.task);
		print(newTodo);
	}
	read.close();
	system("pause");
}

int searchData() {
	setlocale(LC_ALL, "Russian");
	system("cls");
	cout << "\t\t\t Добро пожаловать в ваш список дел " << endl;
	int id;
	cout << "\n\t Введите идентификатор задачи: ";
	cin >> id;
	todo newTodo;
	ifstream read;
	read.open("todo.txt");

	while (read >> newTodo.id) {
		read.ignore();
		getline(read, newTodo.task);
		if (newTodo.id == id) {
			print(newTodo);
			return id;
		}
	}
	read.close();
	return -1;
}

void deleteData() {
	system("cls");
	cout << "\t\t\t Добро пожаловать в ваш список дел " << endl;

	int id = searchData();
	setlocale(LC_ALL, "Russian");
	cout << "\n\tВы хотите удалить эту задачу (y/n) :";
	char choice;
	cin >> choice;
	if (choice == 'y') {
		todo newTodo;
		ofstream tempFile;
		tempFile.open("temp.txt");
		ifstream read;
		read.open("todo.txt");
		while (read >> newTodo.id) {
			read.ignore();
			getline(read, newTodo.task);
			if (newTodo.id != id) {
				tempFile << "\n" << newTodo.id;
				tempFile << "\n" << newTodo.task;
			}
		}
		read.close();
		tempFile.close();
		remove("todo.txt");
		rename("temp.txt", "todo.txt");
		cout << "\n\tЗадача успешно удалена";
	}
	else {
		cout << "\n\tЗапись не удалена";
	}
}

void updateData() {
	setlocale(LC_ALL, "Russian");
	system("cls");
	cout << "\t\t\t Добро пожаловать в ваш список дел " << endl;
	int id = searchData();
	cout << "\n\tВы хотите обновить эту задачу (y/n) : ";
	char choice;
	cin >> choice;

	if (choice == 'y') {
		todo newData;
		cout << "\n\tВведите текущую задачу : ";
		cin.ignore();
		getline(cin, newData.task);
		todo newTodo;
		ofstream tempFile;
		tempFile.open("temp.txt");
		ifstream read;
		read.open("todo.txt");
		while (read >> newTodo.id) {
			read.ignore();
			getline(read, newTodo.task);
			if (newTodo.id != id) {
				tempFile << "\n" << newTodo.id;
				tempFile << "\n" << newTodo.task;
			}
			else {
				tempFile << "\n" << newTodo.id;
				tempFile << "\n" << newData.task;
			}
		}
		read.close();
		tempFile.close();         remove("todo.txt");
		rename("temp.txt", "todo.txt");         cout << "\n\tЗадача успешно обновлена";
	}
	else {
		cout << "\n\tЗапись не обновлена";
	}
}
int main() {
	setlocale(LC_ALL, "Russian");
	system("cls");     cout << "\t\t\t Добро пожаловать в ваш список дел " << endl;
	ifstream read;     read.open("id.txt");
	read >> ID;     read.close();
	char ch;
	do {
		system("cls");
		cout << "\t\t\t Добро пожаловать в ваш список дел " << endl;         cout << "\n\t1. Просмотреть список дел";
		cout << "\n\t2. Добавить задачу";         cout << "\n\t3. Удалить задачу";
		cout << "\n\t4. Обновить задачу";         cout << "\n\t5. Выйти";
		cout << "\n\n\tВыберите действие: ";         cin >> ch;
		switch (ch) {
		case '1':             readData();
		break;         case '2':
			addtodo();             break;
		case '3':             deleteData();
		break;         case '4':
			updateData();             break;
		case '5':             exit(0);
		default:             cout << "\n\tНеверный ввод. Попробуйте еще раз.";
		}         system("pause");
	} while (ch != '5');
	return 0;
}

