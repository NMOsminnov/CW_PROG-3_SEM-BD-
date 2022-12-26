
#include "BD.h"
// Копирование данных
void CustomerCopyData(Customer* newCurrent, Customer* current) {
	newCurrent->ID = current->ID;
	newCurrent->name = current->name;
	newCurrent->surname = current->surname;
	newCurrent->phoneNumber = current->phoneNumber;
}
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

void AddCustomer(Customer** customerList) {
	bool New = false; // Новый ли список
	Customer* current;
	int i = 1;

	// Если списка нет то создаем его первый элемент
	if (*customerList == NULL) {
		*customerList = new Customer;
		New = true;
	}

	current = *customerList;
	//Если список не новый, то идем в конец и создаем новый элемент в конце списка
	if (!New) {
		while (current->next != NULL) {
			current = current->next;
			
		}
		i = current->ID;
		current->next = new Customer;
		current = current->next;
	}

	// Ручной ввод значений полей
	current->ID = i++;
	cout << "Пожалуйста, введите имя заказчика:";
	cin >> current->name;
	cout << "Пожалуйста, введите фамилию заказчика:";
	cin >> current->surname;
	cout << "Пожалуйста, введите номер телефона заказчика:";
	cin >> current->phoneNumber;

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
	Customer* del;				   // Указатель на удаляемый элемент 

	if (customerList) {
		while ((current->next) && (current->next->ID != position)) {
			current = current->next;
		}

		if (current->next) {
			del = current->next;
			current->next = current->next->next;
			delete del;
			return true;
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
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
	Customer* newCurrent;
	if (customerList) {
		while (current) {
			if (current->ID == position) {
				newCurrent = new Customer;
				CustomerCopyData(newCurrent, current);
				return newCurrent;
			}
			current = current->next;
		}
	}
	return NULL;
}
Customer* FindNameOfCustomer(Customer* customerList, string key) {

	Customer* newList = NULL;			// Новый список, который будет возвращаться в качестве результата
	Customer* current = customerList;		// Указатель, с помощью которого движемся по основному списку
	Customer* newCurrent = NULL;		// Указатель при помощи которого движемся по списку с результатами

	if (current) { // Если исходный список существует
		while (current) { // То пока не дойдем до его конца
			if (current->name == key) { // Ищем ключ
				if (!newCurrent) { // Если это первый найденный элемент 
					newCurrent = new Customer; // То создаем корень нового списка
					newList = newCurrent; // Запоминаем корень который будем возвращать					
				}
				else { // Иначе создаем следующий элемент списка
					newCurrent->next = new Customer;
					newCurrent = newCurrent->next;
				}
				CustomerCopyData(newCurrent, current); // И копируем данные
			}
			current = current->next; // Далее передвигаемся вперед по основному списку
		}
	}
	DeleteCustomerList(&customerList);
	return newList; // В конце возвращаем новый список
}
Customer* FindSurnameOfCustomer(Customer* customerList, string key) {

	Customer* newList = NULL;			// Новый список, который будет возвращаться в качестве результата
	Customer* current = customerList;		// Указатель, с помощью которого движемся по основному списку
	Customer* newCurrent = NULL;		// Указатель при помощи которого движемся по списку с результатами

	if (current) { // Если исходный список существует
		while (current) { // То пока не дойдем до его конца
			if (current->name == key) { // Ищем ключ
				if (!newCurrent) { // Если это первый найденный элемент 
					newCurrent = new Customer; // То создаем корень нового списка
					newList = newCurrent; // Запоминаем корень который будем возвращать					
				}
				else { // Иначе создаем следующий элемент списка
					newCurrent->next = new Customer;
					newCurrent = newCurrent->next;
				}
				CustomerCopyData(newCurrent, current); // И копируем данные
			}
			current = current->next; // Далее передвигаемся вперед по основному списку
		}
	}
	DeleteCustomerList(&customerList);
	return newList; // В конце возвращаем новый список
}
Customer* FindPhoneNumberOfCustomer(Customer* customerList, string key) {

	Customer* newList = NULL;			// Новый список, который будет возвращаться в качестве результата
	Customer* current = customerList;		// Указатель, с помощью которого движемся по основному списку
	Customer* newCurrent = NULL;		// Указатель при помощи которого движемся по списку с результатами

	if (current) { // Если исходный список существует
		while (current) { // То пока не дойдем до его конца
			if (current->name == key) { // Ищем ключ
				if (!newCurrent) { // Если это первый найденный элемент 
					newCurrent = new Customer; // То создаем корень нового списка
					newList = newCurrent; // Запоминаем корень который будем возвращать					
				}
				else { // Иначе создаем следующий элемент списка
					newCurrent->next = new Customer;
					newCurrent = newCurrent->next;
				}
				CustomerCopyData(newCurrent, current); // И копируем данные			
			}
			current = current->next; // Далее передвигаемся вперед по основному списку
		}
	}
	DeleteCustomerList(&customerList);
	return newList; // В конце возвращаем новый список
}

