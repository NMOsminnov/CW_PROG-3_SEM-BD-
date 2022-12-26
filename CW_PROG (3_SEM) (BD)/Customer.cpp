
#include "BD.h"

//Считывание данных заказчика с файла (однонаправленный линейный список)
void FileReadCustomer(string f_name, Customer** customerList) {

	bool New = false;
	Customer* current;
	string temp;

	if (*customerList == NULL) {
		*customerList = new Customer;
		New = true;
	}

	current = *customerList;

	if (!New) {
		while (current->next != NULL) {
			current = current->next;
		}
	}

	ifstream ifs(f_name);

	while (!ifs.eof()) {
		ifs >> temp;

		if (temp == "") {
			break;
		}
		if (!New) {
			current->next = new Customer;
			current = current->next;
		}
		else {
			New = false;
		}
		if (!ifs.eof()) {
			current->name = temp;
			temp = "";
			ifs >> current->surname;
			ifs >> current->phoneNumber;
		}
	}
}
//Вывод в консоль списка с заказчиками
void PrintCustomer(Customer* doorList) {

	Customer* current = doorList;

	int i = 1;

	if (current != NULL) {
		setlocale(LC_ALL, "C");

		cout << endl << setfill(horizontalLine) << topLeftCorner
			<< setw(numberLenght) << bottomJunction
			<< setw(nameLenght) << bottomJunction
			<< setw(surnameLenght) << bottomJunction
			<< setw(phoneNumberLenght) << topRightCorner;

		cout << endl << setfill(space) << verticalLine
			<< setw(numberLenght - 1) << "#" << right << verticalLine
			<< setw(nameLenght - 1) << "Name" << right << verticalLine
			<< setw(surnameLenght - 1) << "Type" << right << verticalLine
			<< setw(phoneNumberLenght - 1) << "Price" << right << verticalLine;


		while (current != NULL) {
			cout << endl << setfill(horizontalLine) << rightJunction
				<< setw(numberLenght) << crossJunction
				<< setw(nameLenght) << crossJunction
				<< setw(surnameLenght) << crossJunction
				<< setw(phoneNumberLenght) << leftJunction;

			cout << endl << setfill(space) << verticalLine
				<< setw(numberLenght - 1) << i++ << right << verticalLine
				<< setw(nameLenght - 1) << current->name << right << verticalLine
				<< setw(surnameLenght - 1) << current->surname << right << verticalLine
				<< setw(phoneNumberLenght - 1) << current->phoneNumber << right << verticalLine;

			current = current->next;
		};


		cout << endl << setfill(horizontalLine) << bottomLeftCorner
			<< setw(numberLenght) << topJunction
			<< setw(nameLenght) << topJunction
			<< setw(surnameLenght) << topJunction
			<< setw(phoneNumberLenght) << bottomRightCorner << endl;



		setlocale(LC_ALL, "ru");
	}
	else {
		cout << "Список пуст!" << endl;
	}
}
//Удаление элемента в заданной позиции
bool DeleteCustomer(Customer** customerList, int position) {

	Customer* current = *customerList;
	Customer* del;

	if (position == 1) {
		*customerList = (*customerList)->next;
		delete current;
	}
	else {
		for (int i = 0; i < position - 2; i++) {
			if (current->next->next != NULL) {
				current = current->next;
			}
			else {
				cout << "Элемент не обнаружен" << endl;
				return false;
			}
		}

		del = current->next;
		current->next = current->next->next;
		delete del;
		return true;
	}
	return true;
}
//Удаление списка с заказчиками
void DeleteCustomerList(Customer** customerList) {

	Customer* current = *customerList;
	while (current != NULL) {
		current = current->next;
		delete* customerList;
		*customerList = current;
	}
}
//Копипаст!
Customer* GetCustomer(Customer* customerList, int position) {
	Customer* current = customerList;
	if (customerList) {
		for (int i = 0; i < position - 1; i++) {
			if (current->next) {
				current = current->next;
			}
			else {
				return NULL;
			}
		}
	}
	return current;
}
Customer* FindNameOfCustomer(Customer* customerList, string key) {

	Customer* newList = NULL;
	Customer* current = customerList;
	Customer* newCurrent = NULL;

	if (current) {
		while (current) {
			if (current->name == key) {
				if (!newCurrent) {
					newCurrent = new Customer;
					newList = newCurrent;
				}
				else {
					newCurrent->next = new Customer;
					newCurrent = newCurrent->next;
				}
				newCurrent->ID = current->ID;
				newCurrent->name = current->name;
				newCurrent->surname = current->surname;
				newCurrent->phoneNumber = current->phoneNumber;
			}
			current = current->next;
		}
	}

	return newList;
}


