
#include <iostream>
#include <fstream>
#include <iomanip>

#include "BD.h"


using namespace std;

// Размеры (длина) ячеек таблицы соответствующих пераметров

const int numberLenght = 6;						//Индекс
const int priceLenght = 10;						//Цена
const int nameLenght = 10;						//Имя
const int typeLenght = 20;						//Тип двери
const int productionTimeLenght = 15;			//Время производства
const int phoneNumberLenght = 15;				//Номер телефона
const int surnameLenght = 10;					//Фамилия
const int priceOfAccessoriesLenght = 20;		//Траты на фурнитуру
const int typeOfAccessoriesLenght = 20;			//Тип фурнитуры
const int supplierLenght = 10;					//Поставщик
const int deliveryTimeLenght = 15;				//Срок доставки

const char verticalLine = (char)186;		// "║" - Вертикальная линия
const char horizontalLine = (char)205;		// "═" - Горизонтальная линия
const char topLeftCorner = (char)201;		// "╔" - Левый верхний угол
const char topRightCorner = (char)187;		// "╗" - Правый верхний угол
const char bottomLeftCorner = (char)200;	// "╚" - Левый нижний угол
const char bottomRightCorner = (char)188;	// "╝" - Правый нижний угол
const char leftJunction = (char)185;		// "╣" - вертикальная "труба влево"
const char rightJunction = (char)204;		// "╠" - вертикальная "труба вправо"
const char bottomJunction = (char)203;		// "╦" - Горизонтальная вниз "труба"
const char topJunction = (char)202;			// "╩" - Горизонтальная вниз "труба"
const char crossJunction = (char)206;		// "╬" - пересечение линий
const char space = (char)32;				// Пустое пространство

//Считывание данных двери с файла (однонаправленный линейный список)
void FileReadDoor(string f_name, Door** doorList) {

	bool New = false; // Флаг, говорящий нам о том новый ли это список
	Door* current;    // Текущий элемент
	string temp;	  // Временная переменная 

	if (*doorList == NULL) {	// Если список новый, то создаем его
		*doorList = new Door;
		New = true;				// И запоминаем что он новый
	}

	current = *doorList;		// Используем вспомогательный указатель, что бы двигаться по списку

	if (!New) {// Если же список не новый то идем до конца списка
		while (current->next != NULL) {
			current = current->next;
		}
	}

	ifstream ifs(f_name);  // Открываем наш файлик

	if (ifs.is_open()) {
		while (!ifs.eof()) {   // И если он открылся считываем данные из него
			ifs >> temp;
			if (temp == "") {  // Проверка на то, считается ли хоть что - нибудь
				break;
			}
			if (!New) {		   // Если список не новый, то создаем новый пустой элемент 
				current->next = new Door;
				current = current->next;  // И переходим на него
			}
			else {
				New = false;
			}
			if (!ifs.eof()) { // И если файл не кончился то считываем данные в наш пустой элемент
				current->type = temp;
				temp = "";
				ifs >> current->name;
				ifs >> current->price;
				ifs >> current->productionTime;
				ifs >> current->priceOfAccessories;
				ifs >> current->typeOfAccessories;
				ifs >> current->supplier;
			}
		}
	}
	else {
		delete* doorList;
	}
}
//Вывод в консоль списка с дверями
void PrintDoor(Door* doorList) {

	Door* current = doorList;

	int i = 1;

	if (current != NULL) { // Печатаем только если список существует
		setlocale(LC_ALL, "C"); // Переходим на таблицу с нужными символами
		// Печать шапки таблицы
		cout << endl << setfill(horizontalLine) << topLeftCorner
			<< setw(numberLenght)				<< bottomJunction
			<< setw(typeLenght)					<< bottomJunction
			<< setw(nameLenght)					<< bottomJunction
			<< setw(priceLenght)				<< bottomJunction
			<< setw(productionTimeLenght)		<< bottomJunction
			<< setw(priceOfAccessoriesLenght)	<< bottomJunction
			<< setw(typeOfAccessoriesLenght)	<< bottomJunction
			<< setw(supplierLenght)				<< topRightCorner;
		
		cout << endl << setfill(space) << verticalLine
			<< setw(numberLenght - 1)				<< "#"				<< right << verticalLine
			<< setw(typeLenght - 1)					<< "Type"			<< right << verticalLine
			<< setw(nameLenght - 1)					<< "Name"			<< right << verticalLine
			<< setw(priceLenght - 1)				<< "Price"			<< right << verticalLine
			<< setw(productionTimeLenght - 1)		<< "ProductionTime" << right << verticalLine
			<< setw(priceOfAccessoriesLenght - 1)	<< "Consumables"	<< right << verticalLine
			<< setw(typeOfAccessoriesLenght - 1)	<< "Consumables type"<< right << verticalLine
			<< setw(supplierLenght - 1)				<< "Supplier"		<< right << verticalLine;

		while (current != NULL) {  // Печать производится пока не достигнем конца списка
			// Печать верхней части ячеек.
			cout << endl << setfill(horizontalLine) << rightJunction
				<< setw(numberLenght)			    << crossJunction
				<< setw(typeLenght)				    << crossJunction
				<< setw(nameLenght)				    << crossJunction
				<< setw(priceLenght)			    << crossJunction
				<< setw(productionTimeLenght)	    << crossJunction
				<< setw(priceOfAccessoriesLenght)   << crossJunction
				<< setw(typeOfAccessoriesLenght)	<< crossJunction
				<< setw(supplierLenght)			    << leftJunction;

			// Печать самих значений и вертикальных линий (между ячейками таблицы)
			cout << endl << setfill(space)				<< verticalLine
				 << setw(numberLenght - 1)				<< i++							<< right << verticalLine
				 << setw(typeLenght - 1)				<< current->type				<< right << verticalLine
				 << setw(nameLenght - 1)				<< current->name				<< right << verticalLine
				 << setw(priceLenght - 1)				<< current->price				<< right << verticalLine
				 << setw(productionTimeLenght - 1)		<< current->productionTime		<< right << verticalLine
				 << setw(priceOfAccessoriesLenght - 1)	<< current->priceOfAccessories  << right << verticalLine
				 << setw(typeOfAccessoriesLenght - 1)	<< current->typeOfAccessories	<< right << verticalLine
				 << setw(supplierLenght - 1)			<< current->supplier		    << right << verticalLine;
			
			current = current->next;
		}

		// Закрываем таблицу
		cout << endl << setfill(horizontalLine) << bottomLeftCorner
			<< setw(numberLenght)				<< topJunction
			<< setw(typeLenght)					<< topJunction
			<< setw(nameLenght)					<< topJunction
			<< setw(priceLenght)				<< topJunction
			<< setw(productionTimeLenght)		<< topJunction
			<< setw(priceOfAccessoriesLenght)	<< topJunction
			<< setw(typeOfAccessoriesLenght) << topJunction
			<< setw(supplierLenght)				<< bottomRightCorner<<endl;



		setlocale(LC_ALL, "ru");  // Ах - да... Не забываем вернуть русскую таблицу 
	}
	else { // Если списка нет, то выводим соответствующее сообщение
		cout << "Список пуст!" << endl;
	}
}
//Добавление в конец списка двери
void AddDoor(Door** doorList){
	bool New = false; // Новый ли список
	Door* current;
	int i = 1;

	// Если списка нет то создаем его первый элемент
	if (*doorList == NULL) {
		*doorList = new Door;
		New = true;
	}

	current = *doorList;
	//Если список не новый, то идем в конец и создаем новый элемент в конце списка
	if (!New) {
		while (current->next != NULL) {
			current = current->next;
			i++;
		}
		i++;
		current->next = new Door;
		current = current->next;
	}

	// Ручной ввод значений полей
	cout << "Пожалуйста, введите тип двери:";
	cin >> current->type;
	cout << "Пожалуйста, введите имя двери:";
	cin >> current->name;
	cout << "Пожалуйста, введите стоимость двери:";
	cin >> current->price;
	cout << "Пожалуйста, введите время изготовления двери:";
	cin >> current->productionTime;
	cout << "Пожалуйста, введите траты на фурнитуру двери:";
	cin >> current->priceOfAccessories;
	cout << "Пожалуйста, введите поставщика двери:";
	cin >> current->supplier;

}                                      //!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//Удаление элемента в заданной позиции
bool DeleteDoor(Door** doorList, int position) {

	Door* current = *doorList; // Вспомогательный указатель для движения по списку
	Door* del;				   // Указатель на удаляемый элемент 

	if (position == 1) {       // Если решили удалить корень спсика
		*doorList = (*doorList)->next;
		delete current;
	}
	else {// Иначе движемся до элемента с нужным индексом (ind - 1)
		for (int i = 0; i < position-2; i++) {
			if (current->next->next != NULL) {
				current = current->next;
			}
			else {
				cout << "Элемент не обнаружен" << endl;
				return false;
			}
		}
		// И удаляем его
		del = current->next;
		current->next = current->next->next;
		delete del;

		return true;
	}
}
//Удаление списка с заказами
void DeleteDoorList(Door** doorList) {

	Door* current = * doorList; // Используем вспогательную переменную для движения по списку
	while (current != NULL) { // Пока есть элементы
		current = current->next; // Движемся по списку
		delete *doorList; // Удаляем корень
		*doorList = current;	// И обозначаем первый элемент списка как корень	
	}
}
//Копипаст...
Door* GiveDoor(Door* doorList, int position) {
	Door* current = doorList; // Вспомогательный указатель для движения по списку
	if (doorList) {	 // Если список существует	
		for (int i = 0; i < position-1; i++) { // То идем по циклу
			if (current->next) { // И если следующий элемент существует
				current = current->next; // То переходим на него
			}
			else { // Иначе возвращаем 0 т.к. элемент лежит за пределами списка
				return NULL;
			}
		}
	}
	return current;
}
Door* FindTypeOfDoor(Door* doorList, string key) {
	
	Door* newList = NULL;			// Новый список, который будет возвращаться в качестве результата
	Door* current = doorList;		// Указатель, с помощью которого движемся по основному списку
	Door* newCurrent = NULL;		// Указатель при помощи которого движемся по списку с результатами

	if (current) { // Если исходный список существует
		while (current) { // То пока не дойдем до его конца
			if (current->type == key) { // Ищем ключ
				if (!newCurrent) { // Если это первый найденный элемент 
					newCurrent = new Door; // То создаем корень нового списка
					newList = newCurrent; // Запоминаем корень который будем возвращать					
				}
				else { // Иначе создаем следующий элемент списка
					newCurrent->next = new Door;
					newCurrent = newCurrent->next;
				}
					newCurrent->type = current->type; // И копируем данные
					newCurrent->name = current->name;
					newCurrent->price = current->price;
					newCurrent->productionTime = current->productionTime;
					newCurrent->priceOfAccessories = current->priceOfAccessories;
					newCurrent->supplier = current->supplier;				
			}
			current = current->next; // Далее передвигаемся вперед по основному списку
		}
	}

	return newList; // В конце возвращаем новый список
}
Door* FindNameOfDoor(Door* doorList, string key) {


	Door* newList = NULL;			// Новый список, который будет возвращаться в качестве результата
	Door* current = doorList;		// Указатель, с помощью которого движемся по основному списку
	Door* newCurrent = NULL;		// Указатель при помощи которого движемся по списку с результатами

	if (current) { // Если исходный список существует
		while (current) { // То пока не дойдем до его конца
			if (current->name == key) { // Ищем ключ
				if (!newCurrent) { // Если это первый найденный элемент 
					newCurrent = new Door; // То создаем корень нового списка
					newList = newCurrent; // Запоминаем корень который будем возвращать					
				}
				else { // Иначе создаем следующий элемент списка
					newCurrent->next = new Door;
					newCurrent = newCurrent->next;
				}
				newCurrent->type = current->type; // И копируем данные
				newCurrent->name = current->name;
				newCurrent->price = current->price;
				newCurrent->productionTime = current->productionTime;
				newCurrent->priceOfAccessories = current->priceOfAccessories;
				newCurrent->supplier = current->supplier;
			}
			current = current->next; // Далее передвигаемся вперед по основному списку
		}
	}

	return newList; // В конце возвращаем новый список
}
Door* FindPriceOfDoor(Door* doorList, float key) {

	Door* newList = NULL;
	Door* current = doorList;
	Door* newCurrent = NULL;



	if (current) {
		while (current) {
			if (current->price == key) {
				if (!newCurrent) {
					newCurrent = new Door;
					newList = newCurrent;
					newCurrent->type = current->type;	
				}
				else {
					newCurrent->next = new Door;
					newCurrent = newCurrent->next;				
				}
				newCurrent->type = current->type;
				newCurrent->name = current->name;
				newCurrent->price = current->price;
				newCurrent->productionTime = current->productionTime;
				newCurrent->priceOfAccessories = current->priceOfAccessories;
				newCurrent->supplier = current->supplier;
			}
			current = current->next;
		}
	}

	return newList;
}
Door* FindProductionTimeOfDoor(Door* doorList, string key) {

	Door* newList = NULL;
	Door* current = doorList;
	Door* newCurrent = NULL;



	if (current) {
		while (current) {
			if (current->productionTime == key) {
				if (!newCurrent) {
					newCurrent = new Door;
					newList = newCurrent;
				}
				else {
					newCurrent->next = new Door;
					newCurrent = newCurrent->next;		
				}
				newCurrent->type = current->type;
				newCurrent->name = current->name;
				newCurrent->price = current->price;
				newCurrent->productionTime = current->productionTime;
				newCurrent->priceOfAccessories = current->priceOfAccessories;
				newCurrent->supplier = current->supplier;
			}
			current = current->next;
		}
	}

	return newList;
}
Door* FindPriceOfAccessoriesOfDoor(Door* doorList, float key) {

	Door* newList = NULL;
	Door* current = doorList;
	Door* newCurrent = NULL;



	if (current) {
		while (current) {
			if (current->priceOfAccessories == key) {
				if (!newCurrent) {
					newCurrent = new Door;
					newList = newCurrent;
				}
				else {
					newCurrent->next = new Door;
					newCurrent = newCurrent->next;
				}
				newCurrent->type = current->type;
				newCurrent->name = current->name;
				newCurrent->price = current->price;
				newCurrent->productionTime = current->productionTime;
				newCurrent->priceOfAccessories = current->priceOfAccessories;
				newCurrent->supplier = current->supplier;
			}
			current = current->next;
		}
	}

	return newList;
}
Door* FindSupplierOfDoor(Door* doorList, string key) {

	Door* newList = NULL;
	Door* current = doorList;
	Door* newCurrent = NULL;



	if (current) {
		while (current) {
			if (current->supplier == key) {
				if (!newCurrent) {
					newCurrent = new Door;
					newList = newCurrent;
				}
				else {
					newCurrent->next = new Door;
					newCurrent = newCurrent->next;
				}
				newCurrent->type = current->type;
				newCurrent->name = current->name;
				newCurrent->price = current->price;
				newCurrent->productionTime = current->productionTime;
				newCurrent->priceOfAccessories = current->priceOfAccessories;
				newCurrent->supplier = current->supplier;
			}
			current = current->next;
		}
	}

	return newList;
}
Door* FindTypeOfAccessoriesOfDoor(Door* doorList, string key) {

	Door* newList = NULL;
	Door* current = doorList;
	Door* newCurrent = NULL;



	if (current) {
		while (current) {
			if (current->typeOfAccessories == key) {
				if (!newCurrent) {
					newCurrent = new Door;
					newList = newCurrent;
				}
				else {
					newCurrent->next = new Door;
					newCurrent = newCurrent->next;
				}
				newCurrent->type = current->type;
				newCurrent->name = current->name;
				newCurrent->price = current->price;
				newCurrent->productionTime = current->productionTime;
				newCurrent->priceOfAccessories = current->priceOfAccessories;
				newCurrent->supplier = current->supplier;
			}
			current = current->next;
		}
	}

	return newList;
}


// Для списка заказчиков все так же как и для списка дверей. (копипаст)

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
				<< setw(nameLenght)		   << crossJunction
				<< setw(surnameLenght)		   << crossJunction
				<< setw(phoneNumberLenght) << leftJunction;

			cout << endl << setfill(space) << verticalLine
				<< setw(numberLenght - 1) << i++ << right << verticalLine
				<< setw(nameLenght - 1) << current->name << right << verticalLine
				<< setw(surnameLenght - 1) << current->surname << right << verticalLine
				<< setw(phoneNumberLenght - 1) << current->phoneNumber << right << verticalLine;

			current = current->next;
		} ;


		cout << endl << setfill(horizontalLine) << bottomLeftCorner
			<< setw(numberLenght) << topJunction
			<< setw(nameLenght)   << topJunction
			<< setw(surnameLenght)   << topJunction
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
Customer* GiveCustomer(Customer* customerList, int position) {
	Customer* current = customerList;
	if (customerList) {
		for (int i = 0; i < position-1; i++) {
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
				newCurrent->name = current->name;
				newCurrent->surname = current->surname;
				newCurrent->phoneNumber = current->phoneNumber;
			}
			current = current->next;
		}
	}

	return newList;
}
Customer* FindSurnameOfCustomer(Customer* customerList, string key) {

	Customer* newList = NULL;
	Customer* current = customerList;
	Customer* newCurrent = NULL;

	if (current) {
		while (current) {
			if (current->surname == key) {
				if (!newCurrent) {
					newCurrent = new Customer;
					newList = newCurrent;
				}
				else {
					newCurrent->next = new Customer;
					newCurrent = newCurrent->next;
				}
				newCurrent->name = current->name;
				newCurrent->surname = current->surname;
				newCurrent->phoneNumber = current->phoneNumber;
			}
			current = current->next;
		}
	}

	return newList;
}
Customer* FindPhoneNumberOfCustomer(Customer* customerList, string key) {

	Customer* newList = NULL;
	Customer* current = customerList;
	Customer* newCurrent = NULL;

	if (current) {
		while (current) {
			if (current->phoneNumber == key) {
				if (!newCurrent) {
					newCurrent = new Customer;
					newList = newCurrent;
				}
				else {
					newCurrent->next = new Customer;
					newCurrent = newCurrent->next;
				}
				newCurrent->name = current->name;
				newCurrent->surname = current->surname;
				newCurrent->phoneNumber = current->phoneNumber;
			}
			current = current->next;
		}
	}

	return newList;
}



// А вот тут уже начинаются кольцевые списки.

//Добавление заказа
void AddOrder(Order** orderList,Door* door,Customer* customer, string deliveryTime) {

	bool New = false;
	Order* current;
	int i = 1;
	Order* order = new Order;

	if (*orderList == NULL) {
		*orderList = new Order;
		(*orderList)->next = *orderList;
		New = true;
	}

	current = *orderList;

	if (!New) {
		while (current->next != *orderList) {
			current = current->next;
			i = current->number;
		}
		i++;
		
		order->next = current->next;
		current->next = order ;
		current = current->next;
	}

	current->number = i;
	current->customer = customer;
	current->door = door;

	current->deliveryTime = deliveryTime;

}  // !!!!!!!!!!!!!!!!!!!
//Вывод списка заказов
void PrintOrder(Order* orderList) {

	Order* current = orderList;

	if (current != NULL) {

		setlocale(LC_ALL, "C");

		cout << endl << setfill(horizontalLine) << topLeftCorner
			<< setw(numberLenght) << bottomJunction
			<< setw(typeLenght) << bottomJunction
			<< setw(nameLenght) << bottomJunction
			<< setw(priceLenght) << bottomJunction
			<< setw(productionTimeLenght) << bottomJunction
			<< setw(priceOfAccessoriesLenght) << bottomJunction
			<< setw(typeOfAccessoriesLenght) << bottomJunction
			<< setw(supplierLenght) << bottomJunction
			<< setw(deliveryTimeLenght) << bottomJunction
			<< setw(nameLenght) << bottomJunction
			<< setw(surnameLenght) << bottomJunction
			<< setw(phoneNumberLenght) << topRightCorner;

		cout << endl << setfill(space) << verticalLine
			<< setw(numberLenght - 1) << "#" << right << verticalLine
			<< setw(typeLenght - 1) << "Type" << right << verticalLine
			<< setw(nameLenght - 1) << "Name" << right << verticalLine
			<< setw(priceLenght - 1) << "Price" << right << verticalLine
			<< setw(productionTimeLenght - 1) << "ProductionTime" << right << verticalLine
			<< setw(priceOfAccessoriesLenght - 1) << "Consumables" << right << verticalLine
			<< setw(typeOfAccessoriesLenght - 1) << "Consumables type" << right << verticalLine
			<< setw(supplierLenght - 1) << "Supplier" << right << verticalLine
			<< setw(deliveryTimeLenght - 1) << "DeliveryTime" << right << verticalLine
			<< setw(nameLenght - 1) << "Name" << right << verticalLine
			<< setw(surnameLenght - 1) << "Surname" << right << verticalLine
			<< setw(phoneNumberLenght - 1) << "phoneNumber" << right << verticalLine;

		do {
			cout << endl << setfill(horizontalLine) << rightJunction
				<< setw(numberLenght) << crossJunction
				<< setw(typeLenght) << crossJunction
				<< setw(nameLenght) << crossJunction
				<< setw(priceLenght) << crossJunction
				<< setw(productionTimeLenght) << crossJunction
				<< setw(priceOfAccessoriesLenght) << crossJunction
				<< setw(typeOfAccessoriesLenght) << crossJunction
				<< setw(supplierLenght) << crossJunction
				<< setw(deliveryTimeLenght) << crossJunction
				<< setw(nameLenght) << crossJunction
				<< setw(surnameLenght) << crossJunction
				<< setw(phoneNumberLenght) << leftJunction;

			cout << endl << setfill(space) << verticalLine
				<< setw(numberLenght - 1) << current->number << right << verticalLine
				<< setw(typeLenght - 1) << current->door->type << right << verticalLine
				<< setw(nameLenght - 1) << current->door->name << right << verticalLine
				<< setw(priceLenght - 1) << current->door->price << right << verticalLine
				<< setw(productionTimeLenght - 1) << current->door->productionTime << right << verticalLine
				<< setw(priceOfAccessoriesLenght - 1) << current->door->priceOfAccessories << right << verticalLine
				<< setw(typeOfAccessoriesLenght - 1) << current->door->typeOfAccessories << right << verticalLine
				<< setw(supplierLenght - 1) << current->door->supplier << right << verticalLine
				<< setw(deliveryTimeLenght - 1) << current->deliveryTime << right << verticalLine
				<< setw(nameLenght - 1) << current->customer->name << right << verticalLine
				<< setw(surnameLenght - 1) << current->customer->surname << right << verticalLine
				<< setw(phoneNumberLenght - 1) << current->customer->phoneNumber << right << verticalLine;


			current = current->next;
		} while (current != orderList);


		cout << endl << setfill(horizontalLine) << bottomLeftCorner
			<< setw(numberLenght) << topJunction
			<< setw(typeLenght) << topJunction
			<< setw(nameLenght) << topJunction
			<< setw(priceLenght) << topJunction
			<< setw(productionTimeLenght) << topJunction
			<< setw(priceOfAccessoriesLenght) << topJunction
			<< setw(typeOfAccessoriesLenght) << topJunction
			<< setw(supplierLenght) << topJunction
			<< setw(deliveryTimeLenght) << topJunction
			<< setw(nameLenght) << topJunction
			<< setw(surnameLenght) << topJunction
			<< setw(phoneNumberLenght) << bottomRightCorner << endl;

		setlocale(LC_ALL, "ru");

	}
	else {
		cout << "Заказов не обнаружено!\n";
	}
	
}
//Удаление элемента в заданной позиции
bool DeleteOrder( Order** orderList, int position) {

	Order* current = *orderList;
	Order* del = NULL;

	if ((current)&&position>0) {
		if (current->next) {
			while ((current->next) && (current->next->number != position)) {
				current = current->next;				
			}
			if (!current->next) {
				return false;
			}
			
			del = current->next;
			current->next = current->next->next;
			delete del;
		}
		else {
			delete current;
		}
		return true;
	}
	else {
		return false;
	}
	
}
//Удаление списка заказов
void DeleteOrderList(Order** orderList, int position) {
	Order* current = (*orderList)->next;
	Order* del = current;
	while (current->next != *orderList) {
		current = current->next;
		delete del;
		del = current;
	}
	delete* orderList;
}
//КОПИПАСТ!!!
//КОПИПАСТ!!!
//КОПИПАСТ!!!
//Ну или функции поиска по полям.
Order* FindIndexOfOrder(Order* orderList, int key) {

	Order* newList = NULL;
	Order* current = orderList;
	Order* newCurrent = NULL;

	if (current) {
		 do{
			if (current->number == key) {
				if (!newCurrent) {
					newCurrent = new Order;
					newList = newCurrent;
				}
				else {
					newCurrent->next = new Order;
					newCurrent = newCurrent->next;					
				}
				newCurrent->number = current->number;
				newCurrent->door = current->door;
				newCurrent->customer = current->customer;
				newCurrent->deliveryTime = current->deliveryTime;
			}
			current = current->next;
			
		 } while (current != orderList);
	}

	return newList;
}
Order* FindDoorTypeOfOrder(Order* orderList, string key) {

	Order* newList = NULL;
	Order* current = orderList;
	Order* newCurrent = NULL;

	if (current) {
		do {
			if (current->door->type == key) {
				if (!newCurrent) {
					newCurrent = new Order;
					newList = newCurrent;
				}
				else {
					newCurrent->next = new Order;
					newCurrent = newCurrent->next;
				}
				newCurrent->number = current->number;
				newCurrent->door = current->door;
				newCurrent->customer = current->customer;
				newCurrent->deliveryTime = current->deliveryTime;
			}
			current = current->next;
		} while (current != orderList);
	}

	return newList;
}
Order* FindDoorNameOfOrder(Order* orderList, string key) {

	Order* newList = NULL;
	Order* current = orderList;
	Order* newCurrent = NULL;

	if (current) {
		do {
			if (current->door->name == key) {
				if (!newCurrent) {
					newCurrent = new Order;
					newList = newCurrent;
				}
				else {
					newCurrent->next = new Order;
					newCurrent = newCurrent->next;
				}

				newCurrent->number = current->number;
				newCurrent->door = current->door;
				newCurrent->customer = current->customer;
				newCurrent->deliveryTime = current->deliveryTime;
			}
			current = current->next;
		} while (current != orderList);
	}

	return newList;
}
Order* FindDoorPriceOfOrder(Order* orderList, float key) {

	Order* newList = NULL;
	Order* current = orderList;
	Order* newCurrent = NULL;

	if (current) {
		do {
			if (current->door->price == key) {
				if (!newCurrent) {
					newCurrent = new Order;
					newList = newCurrent;
				}
				else {
					newCurrent->next = new Order;
					newCurrent = newCurrent->next;
				}
				newCurrent->number = current->number;
				newCurrent->door = current->door;
				newCurrent->customer = current->customer;
				newCurrent->deliveryTime = current->deliveryTime;
			}
			current = current->next;
		} while (current != orderList);
	}

	return newList;
}
Order* FindDoorProductionTimeOfOrder(Order* orderList, string key) {

	Order* newList = NULL;
	Order* current = orderList;
	Order* newCurrent = NULL;

	if (current) {
		do {
			if (current->door->productionTime == key) {
				if (!newCurrent) {
					newCurrent = new Order;
					newList = newCurrent;
				}
				else {
					newCurrent->next = new Order;
					newCurrent = newCurrent->next;
				}
				newCurrent->number = current->number;
				newCurrent->door = current->door;
				newCurrent->customer = current->customer;
				newCurrent->deliveryTime = current->deliveryTime;
			}
			current = current->next;
		} while (current != orderList);
	}

	return newList;
}
Order* FindDoorPriceOfAccessoriesOfOrder(Order* orderList, float key) {

	Order* newList = NULL;
	Order* current = orderList;
	Order* newCurrent = NULL;

	if (current) {
		do {
			if (current->door->priceOfAccessories == key) {
				if (!newCurrent) {
					newCurrent = new Order;
					newList = newCurrent;
				}
				else {
					newCurrent->next = new Order;
					newCurrent = newCurrent->next;
				}
				newCurrent->number = current->number;
				newCurrent->door = current->door;
				newCurrent->customer = current->customer;
				newCurrent->deliveryTime = current->deliveryTime;
			}
			current = current->next;
		} while (current != orderList);
	}

	return newList;
}
Order* FindDoorSupplierOfOrder(Order* orderList, string key) {

	Order* newList = NULL;
	Order* current = orderList;
	Order* newCurrent = NULL;

	if (current) {
		do {
			if (current->door->supplier == key) {
				if (!newCurrent) {
					newCurrent = new Order;
					newList = newCurrent;
				}
				else {
					newCurrent->next = new Order;
					newCurrent = newCurrent->next;
				}

				newCurrent->number = current->number;
				newCurrent->door = current->door;
				newCurrent->customer = current->customer;
				newCurrent->deliveryTime = current->deliveryTime;
			}
			current = current->next;
		} while (current != orderList);
	}

	return newList;
}
Order* FindDoorTypeOfAccessoriesOfOrder(Order* orderList, string key) {

	Order* newList = NULL;
	Order* current = orderList;
	Order* newCurrent = NULL;

	if (current) {
		do {
			if (current->door->typeOfAccessories == key) {
				if (!newCurrent) {
					newCurrent = new Order;
					newList = newCurrent;
				}
				else {
					newCurrent->next = new Order;
					newCurrent = newCurrent->next;
				}
				newCurrent->number = current->number;
				newCurrent->door = current->door;
				newCurrent->customer = current->customer;
				newCurrent->deliveryTime = current->deliveryTime;
			}
			current = current->next;
		} while (current != orderList);
	}

	return newList;
}
Order* FindCustomerNameOfOrder(Order* orderList, string key) {

	Order* newList = NULL;
	Order* current = orderList;
	Order* newCurrent = NULL;

	if (current) {
		do {
			if (current->customer->name == key) {
				if (!newCurrent) {
					newCurrent = new Order;
					newList = newCurrent;
				}
				else {
					newCurrent->next = new Order;
					newCurrent = newCurrent->next;
				}
				newCurrent->number = current->number;
				newCurrent->door = current->door;
				newCurrent->customer = current->customer;
				newCurrent->deliveryTime = current->deliveryTime;
			}
			current = current->next;
		} while (current != orderList);
	}

	return newList;
}
Order* FindCustomerSurnameOfOrder(Order* orderList, string key) {

	Order* newList = NULL;
	Order* current = orderList;
	Order* newCurrent = NULL;

	if (current) {
		do {
			if (current->customer->surname == key) {
				if (!newCurrent) {
					newCurrent = new Order;
					newList = newCurrent;
				}
				else {
					newCurrent->next = new Order;
					newCurrent = newCurrent->next;
				}
				newCurrent->number = current->number;
				newCurrent->door = current->door;
				newCurrent->customer = current->customer;
				newCurrent->deliveryTime = current->deliveryTime;
			}
			current = current->next;
		} while (current != orderList);
	}

	return newList;
}
Order* FindCustomerPhoneNumberOfOrder(Order* orderList, string key) {

	Order* newList = NULL;
	Order* current = orderList;
	Order* newCurrent = NULL;

	if (current) {
		do {
			if (current->customer->phoneNumber == key) {
				if (!newCurrent) {
					newCurrent = new Order;
					newList = newCurrent;
				}
				else {
					newCurrent->next = new Order;
					newCurrent = newCurrent->next;
				}
				newCurrent->number = current->number;
				newCurrent->door = current->door;
				newCurrent->customer = current->customer;
				newCurrent->deliveryTime = current->deliveryTime;
			}
			current = current->next;
		} while (current != orderList);
	}

	return newList;
}
Order* FindDeliveryTimeOfOrder(Order* orderList, string key) {

	Order* newList = NULL;
	Order* current = orderList;
	Order* newCurrent = NULL;

	if (current) {
		do {
			if (current->deliveryTime == key) {
				if (!newCurrent) {
					newCurrent = new Order;
					newList = newCurrent;
				}
				else {
					newCurrent->next = new Order;
					newCurrent = newCurrent->next;
				}

				newCurrent->number = current->number;
				newCurrent->door = current->door;
				newCurrent->customer = current->customer;
				newCurrent->deliveryTime = current->deliveryTime;
			}
			current = current->next;
		} while (current != orderList);
	}

	return newList;
}