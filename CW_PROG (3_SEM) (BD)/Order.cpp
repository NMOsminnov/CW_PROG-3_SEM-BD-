
#include "BD.h"

// А вот тут уже начинаются кольцевые списки.
void OrderCopyData(Order* newCurrent, Order* current) {
	newCurrent->ID = current->ID;
	newCurrent->doorID = current->doorID;
	newCurrent->customerID = current->customerID;
	newCurrent->deliveryTime = current->deliveryTime;
}
//Добавление заказа
void FileReadOrder(string f_name, Order** orderList) {
	ifstream ifs(f_name);
	if (ifs.is_open()) {
		bool New = false;
		Order* current;
		string temp;

		if (*orderList == NULL) {
			*orderList = new Order;
			New = true;
		}

		current = *orderList;

		if (!New) {
			while (current->next != *orderList) {
				current = current->next;
				current->next = NULL;
			}
		}



		while (!ifs.eof()) {
			ifs >> temp;

			if (temp == "") {
				break;
			}
			if (!New) {
				current->next = new Order;
				current = current->next;
			}
			else {
				New = false;
			}
			if (!ifs.eof()) {
				current->ID = stoi(temp);
				temp = "";
				ifs >> current->doorID;
				ifs >> current->customerID;
				ifs >> current->deliveryTime;
			}
		}
		current->next = *orderList;
	}
	else {
		std::cout << "Файл не найден\n.";
	}
}

void AddOrder(Order** orderList, int doorID, int customerID, string deliveryTime) {

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
			i = current->ID;
		}
		i++;

		order->next = current->next;
		current->next = order;
		current = current->next;
	}

	current->ID = i;
	current->customerID = customerID;
	current->doorID = doorID;

	current->deliveryTime = deliveryTime;

}  // !!!!!!!!!!!!!!!!!!!
//Вывод списка заказов
void PrintOrder(Order* orderList) {

	Order* current = orderList;

	if (current != NULL) {

		setlocale(LC_ALL, "C");

		cout << endl << setfill(horizontalLine) << topLeftCorner
			<< setw(numberLenght) << bottomJunction
			<< setw(nameLenght) << bottomJunction
			<< setw(customerLenght) << bottomJunction
			<< setw(deliveryTimeLenght) << topRightCorner;

		cout << endl << setfill(space) << verticalLine
			<< setw(numberLenght - 1) << "ID" << right << verticalLine
			<< setw(doorLenght - 1) << "DoorID" << right << verticalLine
			<< setw(customerLenght - 1) << "CustomerID" << right << verticalLine
			<< setw(deliveryTimeLenght - 1) << "DeliveryTime" << right << verticalLine;

		do {
			cout << endl << setfill(horizontalLine) << rightJunction
				<< setw(numberLenght) << crossJunction
				<< setw(doorLenght) << crossJunction
				<< setw(customerLenght) << crossJunction
				<< setw(deliveryTimeLenght) << leftJunction;

			cout << endl << setfill(space) << verticalLine
				<< setw(numberLenght - 1) << current->ID << right << verticalLine
				<< setw(doorLenght - 1) << current->doorID << right << verticalLine
				<< setw(customerLenght - 1) << current->customerID << right << verticalLine
				<< setw(deliveryTimeLenght - 1) << current->deliveryTime << right << verticalLine;


			current = current->next;
		} while (current != orderList);


		cout << endl << setfill(horizontalLine) << bottomLeftCorner
			<< setw(numberLenght) << topJunction
			<< setw(doorLenght) << topJunction
			<< setw(customerLenght) << topJunction
			<< setw(deliveryTimeLenght) << bottomRightCorner << endl;

		setlocale(LC_ALL, "ru");

	}
	else {
		cout << "Заказов не обнаружено!\n";
	}

}
//Удаление элемента в заданной позиции
bool DeleteOrder(Order** orderList, int position) {

	Order* current = *orderList;
	Order* del;				   // Указатель на удаляемый элемент 

	if (*orderList) {		
	
			while ((current->next) && (current->next->ID != position)) {
				current = current->next;
			}

			if (current->next) {
				if (current->next == *orderList) {
					del = *orderList;
					*orderList = ( * orderList)->next;
					current->next = *orderList;
				}
				else {
					del = current->next;
					current->next = current->next->next;
				}
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

	return false;
}
//Удаление списка заказов
void DeleteOrderList(Order** orderList) {
	if (*orderList) {
		Order* current = (*orderList)->next;
		Order* del = current;
		while (current->next != *orderList) {
			current = current->next;
			delete del;
			del = current;
		}
		delete* orderList;
		*orderList = NULL;
	}
}

void SwitchUsedFlag(Order* order) {
	if (order) {
		if (order->is_used) {
			order->is_used = false;
		}
		else {
			order->is_used = true;
		}
	}
}

Order* FindOrderID(Order*orderList,int key) {
	Order* current = orderList;

	if (current) {
		do {
			if (current->ID == key) {
				return current;
			}
			current = current->next;
		} while (current->next != orderList);
	}
	return NULL;
}

Order* GetOrder(Order* orderList, int key) {

	Order* current = orderList;
	Order* newCurrent = NULL;
	if (current) {
		do {			
			if (current->ID == key) {
				newCurrent = new Order;
				OrderCopyData(newCurrent, current);
				newCurrent->next = newCurrent;
				return newCurrent;
			}
			current = current->next;
			
		} while (current->next != orderList);
	}
	return NULL;
}
Order* FindDoorID(Order* orderList, int key) {
	Order* newList = NULL;			// Новый список, который будет возвращаться в качестве результата
	Order* current = orderList;		// Указатель, с помощью которого движемся по основному списку
	Order* newCurrent = NULL;		// Указатель при помощи которого движемся по списку с результатами

	if (current) { // Если исходный список существует
		 do{ // То пока не дойдем до его конца
			if (current->doorID == key) { // Ищем ключ
				if (!newCurrent) { // Если это первый найденный элемент 
					newCurrent = new Order; // То создаем корень нового списка
					newList = newCurrent; // Запоминаем корень который будем возвращать					
				}
				else { // Иначе создаем следующий элемент списка
					newCurrent->next = new Order;
					newCurrent = newCurrent->next;
				}
				OrderCopyData(newCurrent, current);
			}
			current = current->next; // Далее передвигаемся вперед по основному списку
		 } while (current->next!= orderList);
		 if (newCurrent) {
			 newCurrent->next = newList;
		 }
	}
	
	return newList; // В конце возвращаем новый список
}
Order* FindCustomerID(Order* orderList, int key) {
	Order* newList = NULL;			// Новый список, который будет возвращаться в качестве результата
	Order* current = orderList;		// Указатель, с помощью которого движемся по основному списку
	Order* newCurrent = NULL;		// Указатель при помощи которого движемся по списку с результатами

	if (current) { // Если исходный список существует
		do { // То пока не дойдем до его конца
			if (current->customerID == key) { // Ищем ключ
				if (!newCurrent) { // Если это первый найденный элемент 
					newCurrent = new Order; // То создаем корень нового списка
					newList = newCurrent; // Запоминаем корень который будем возвращать					
				}
				else { // Иначе создаем следующий элемент списка
					newCurrent->next = new Order;
					newCurrent = newCurrent->next;
				}
				OrderCopyData(newCurrent, current);
			}
			current = current->next; // Далее передвигаемся вперед по основному списку
		} while (current->next != orderList);
		if (newCurrent) {
			newCurrent->next = newList;
		}
	}
	
	return newList; // В конце возвращаем новый список
}
Order* FindDeliveryTime(Order* orderList, string key) {
	Order* newList = NULL;			// Новый список, который будет возвращаться в качестве результата
	Order* current = orderList;		// Указатель, с помощью которого движемся по основному списку
	Order* newCurrent = NULL;		// Указатель при помощи которого движемся по списку с результатами

	if (current) { // Если исходный список существует
		do { // То пока не дойдем до его конца
			if (current->deliveryTime == key) { // Ищем ключ
				if (!newCurrent) { // Если это первый найденный элемент 
					newCurrent = new Order; // То создаем корень нового списка
					newList = newCurrent; // Запоминаем корень который будем возвращать					
				}
				else { // Иначе создаем следующий элемент списка
					newCurrent->next = new Order;
					newCurrent = newCurrent->next;
				}
				OrderCopyData(newCurrent, current);
			}
			current = current->next; // Далее передвигаемся вперед по основному списку
		} while (current->next != orderList);
		if (newCurrent) {
			newCurrent->next = newList;
		}
	}
	
	return newList; // В конце возвращаем новый список
}

