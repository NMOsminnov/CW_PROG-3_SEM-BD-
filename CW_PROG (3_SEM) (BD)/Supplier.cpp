
#include "BD.h"

// Door.cpp
// Меняет размер массива
int* IntReSize(int* array, int oldSize, int newSize) {
	int* newArr = new int[newSize];
	if (array) {
		for (int i = 0; (i < oldSize) && (i < newSize); i++) {
			newArr[i] = array[i];
		}
		delete[] array;
	}

	return newArr;
}

void SupplierCopyData(Supplier* newCurrent, Supplier* current) {
	newCurrent->ID = current->ID;
	newCurrent->name = current->name;
	newCurrent->quantityOrders = current->quantityOrders;
	newCurrent->orderID = new int[current->quantityOrders];
	for (int i = 0; i < current->quantityOrders; i++) {
		newCurrent->orderID[i] = current->orderID[i];
	}
}

bool ChekOrderID(int orderID, Supplier* supplierList) {
	Supplier* current = supplierList;
	if (supplierList && orderID > 0) {
		do {
			for (int i = 0; i < current->quantityOrders; i++) {
				if (current->orderID[i] == orderID) {
					return false;
				}
			}
		} while (current->next != supplierList);
		return true;
	}
	else {
		return false;
	}
} //!!!!!!!!!

void FileReadSupplier(string f_name, Supplier** supplierList) {

	bool New = false;
	Supplier* current;
	string temp;
	char t;
	int size = 0;
	int ID = 1;

	if (*supplierList == NULL) {
		*supplierList = new Supplier;
		New = true;
	}

	current = *supplierList;

	if (!New) {
		while (current->next != NULL) {
			current = current->next;
			ID = current->ID;
		}
	}

	ifstream ifs(f_name);

	while (!ifs.eof()) {
		size = 0;
		ifs >> temp;
		if (temp != "") {
			if (!New) {
				current->next = new Supplier;
				current = current->next;
			}
			current->name = temp;

			ifs.get(t);
			while (t != '\n' && !ifs.eof()) {
				temp = "";
				ifs.get(t);
				while (t != ' ' && !ifs.eof() && t != '\n') {
					temp += t;
					ifs.get(t);
				}
				size++;
				current->orderID = IntReSize(current->orderID, size - 1, size);
				current->orderID[size - 1] = stoi(temp);
			}

			current->ID = ID++;
			current->quantityOrders = size;
			New = false;
		}
	}
	current->next = *supplierList;
}
void PrintSupplier(Supplier* supplierList) {
	Supplier* current = supplierList;

	if (current != NULL) {

		setlocale(LC_ALL, "C");

		cout << endl << setfill(horizontalLine) << topLeftCorner
			<< setw(numberLenght) << bottomJunction
			<< setw(nameLenght) << bottomJunction
			<< setw(numberLenght) << topRightCorner;

		cout << endl << setfill(space) << verticalLine
			<< setw(numberLenght - 1) << "ID" << right << verticalLine
			<< setw(nameLenght - 1) << "Name" << right << verticalLine
			<< setw(numberLenght - 1) << "QNT" << right << verticalLine;

		do {
			cout << endl << setfill(horizontalLine) << rightJunction
				<< setw(numberLenght) << crossJunction
				<< setw(nameLenght) << crossJunction
				<< setw(numberLenght) << leftJunction;

			cout << endl << setfill(space) << verticalLine
				<< setw(numberLenght - 1) << current->ID << right << verticalLine
				<< setw(nameLenght - 1) << current->name << right << verticalLine
				<< setw(numberLenght - 1) << current->quantityOrders << right << verticalLine;


			current = current->next;
		} while (current != supplierList);


		cout << endl << setfill(horizontalLine) << bottomLeftCorner
			<< setw(numberLenght) << topJunction
			<< setw(nameLenght) << topJunction
			<< setw(numberLenght) << bottomRightCorner << endl;

		setlocale(LC_ALL, "ru");

	}
	else {
		cout << "Заказов не обнаружено!\n";
	}
}

bool DeleteSupplier(Supplier** customerList, int position) {

	Supplier* current = *customerList;
	Supplier* del;				   // Указатель на удаляемый элемент 

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
void DeleteSupplierList(Supplier** customerList) {

	Supplier* current = *customerList;
	while (current != NULL) {
		current = current->next;
		delete* customerList;
		*customerList = current;
	}
}
//Копипаст!




void SupplierInfo(Supplier* supplier, Order* orderList) {

	Order* current;

	if (supplier) {

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


		for (int i = 0; i < supplier->quantityOrders; i++) {
			current = GetOrder(orderList, supplier->orderID[i]);
			if (current) {
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

			}
		}

		cout << endl << setfill(horizontalLine) << bottomLeftCorner
			<< setw(numberLenght) << topJunction
			<< setw(doorLenght) << topJunction
			<< setw(customerLenght) << topJunction
			<< setw(deliveryTimeLenght) << bottomRightCorner << endl;

		setlocale(LC_ALL, "ru");
	}
}
Supplier* GetSupplier(Supplier* supplierList, int key) {

	Supplier* current = supplierList;

	if (current) {
		do {
			if (current->ID == key) {
				return current;
			}
		} while (current->next != supplierList);
	}
	return NULL;
}