
#include "BD.h"

// Door.cpp
// ������ ������ �������
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

void FileReadSupplier(string f_name, Supplier** supplierList, Order* orderList) {
	ifstream ifs(f_name);
	if (ifs.is_open()) {
	bool New = false;
	Supplier* current;
	Order* tempOrder;
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

					tempOrder = FindOrderID(orderList, stoi(temp));
					
					if (tempOrder&&!(tempOrder->is_used)) {
						size++;
						current->orderID = IntReSize(current->orderID, size - 1, size);
						current->orderID[size - 1] = stoi(temp);
						SwitchUsedFlag(tempOrder);
					}
				}


				current->ID = ID++;
				current->quantityOrders = size;
				New = false;
			}
		}
		current->next = *supplierList;
	}
	else {
		std::cout << "���� �� ������\n.";
	}
}
void PrintSupplier(Supplier* supplierList) {
	Supplier* current = supplierList;

	if (current) {

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
		cout << "����������� �� ����������!\n";
	}
}

bool DeleteSupplier(Supplier** supplierList, int position) {

	Supplier* current = *supplierList;
	Supplier* del;				   // ��������� �� ��������� ������� 

	if (supplierList) {
		if (position == 1) {
			del = *supplierList;
			*supplierList = (*supplierList)->next;
			while (current->next != del) { current = current->next; }
			current->next = *supplierList;
			delete del;
			return true;
		}
		else {
			while ((current->next) && (current->next->ID != position)) {
				current = current->next;
			}

			if (current->next) {
				del = current->next;
				current->next = current->next->next;
				delete[] del->orderID;
				delete del;
				return true;
			}
			else {
				return false;
			}
		}
	}
	else {
		return false;
	}
}
//�������� ������ � �����������
void DeleteSupplierList(Supplier** supplierList) {

	if (*supplierList) {
		Supplier* current = (*supplierList)->next;
		Supplier* del = current;
		while (current->next != *supplierList) {
			current = current->next;
			delete del;
			del = current;
		}
		delete* supplierList;
		*supplierList = NULL;
	}
}
//��������!
void AddSupplier(Supplier** supplierList,Order* orderList) {
	bool New = false; // ����� �� ������
	Supplier* current;
	Order* tempOrder = NULL;
	int i = 1;
	int temp;

	// ���� ������ ��� �� ������� ��� ������ �������
	if (*supplierList == NULL) {
		*supplierList = new Supplier;
		New = true;
	}

	current = *supplierList;
	//���� ������ �� �����, �� ���� � ����� � ������� ����� ������� � ����� ������
	if (!New) {
		while (current->next != *supplierList) {
			current = current->next;

		} ;
		current->next = NULL;
		i = current->ID+1;
		current->next = new Supplier;
		current = current->next;
	}

	// ������ ���� �������� �����
	current->ID = i++;
	cout << "����������, ������� ��� ����������:";
	cin >> current->name;
	cout << "����������, ������� ���������� ������� ����������:";
	cin >> current->quantityOrders;
	int cicle = current->quantityOrders;
	for (int i = 0; i < cicle;i++) {
		cout << "����������, ������� ID ������:";
		cin >> temp;
		tempOrder = FindOrderID(orderList, temp);
		if (!(tempOrder->is_used)) {
			IntReSize(current->orderID, i + 1, current->quantityOrders);
			current->orderID[i] = temp;
			SwitchUsedFlag(tempOrder);
		}
		else {
			current->quantityOrders--;
		}
		
	}
	current->next = *supplierList;
}                                      //!!!!!!!!!!!!!!!!!!!!!!!!!!!!



void SupplierInfo(Supplier* supplier, Order* orderList) {

	Order* current;

	if (supplier) {

		setlocale(LC_ALL, "C");
		cout << endl << setfill(horizontalLine) << topLeftCorner
			<< setw(numberLenght + nameLenght + customerLenght + deliveryTimeLenght)
			<< topRightCorner;

		cout << endl << setfill(space) << verticalLine
			<< setw(numberLenght + nameLenght + customerLenght + deliveryTimeLenght - 1)
			<< supplier->name << right << verticalLine;

		cout << endl << setfill(horizontalLine) << rightJunction
			<< setw(numberLenght) << bottomJunction
			<< setw(nameLenght) << bottomJunction
			<< setw(customerLenght) << bottomJunction
			<< setw(deliveryTimeLenght) << leftJunction;

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
	Supplier* newCurrent;
	if (current) {
		do {
			if (current->ID == key) {
				newCurrent = new Supplier;
				SupplierCopyData(newCurrent, current);
				return newCurrent;
			}
			current = current->next;
		} while (current->next != supplierList);
	}
	return NULL;
}

Supplier* FindSupplierID(Supplier* supplierList, int key) {
	Supplier* current = supplierList;

	if (current) {
		do {
			if (current->ID == key) {
				return current;
			}
			current = current->next;
		} while (current->next != supplierList);
	}
	return NULL;
}
Supplier* FindSupplierName(Supplier* supplierList, string key) {
	Supplier* newList = NULL;			// ����� ������, ������� ����� ������������ � �������� ����������
	Supplier* current = supplierList;		// ���������, � ������� �������� �������� �� ��������� ������
	Supplier* newCurrent = NULL;		// ��������� ��� ������ �������� �������� �� ������ � ������������

	if (current) { // ���� �������� ������ ����������
		do { // �� ���� �� ������ �� ��� �����
			if (current->name == key) { // ���� ����
				if (!newCurrent) { // ���� ��� ������ ��������� ������� 
					newCurrent = new Supplier; // �� ������� ������ ������ ������
					newList = newCurrent; // ���������� ������ ������� ����� ����������					
				}
				else { // ����� ������� ��������� ������� ������
					newCurrent->next = new Supplier;
					newCurrent = newCurrent->next;
				}
				SupplierCopyData(newCurrent, current);
			}
			current = current->next; // ����� ������������� ������ �� ��������� ������
		} while (current->next != supplierList);

		if (newCurrent) {
			newCurrent->next = newList;
		}
	}

	return newList; // � ����� ���������� ����� ������
}
Supplier* FindQuantityOrders(Supplier* supplierList, int key) {
	Supplier* newList = NULL;			// ����� ������, ������� ����� ������������ � �������� ����������
	Supplier* current = supplierList;		// ���������, � ������� �������� �������� �� ��������� ������
	Supplier* newCurrent = NULL;		// ��������� ��� ������ �������� �������� �� ������ � ������������

	if (current) { // ���� �������� ������ ����������
		do { // �� ���� �� ������ �� ��� �����
			if (current->quantityOrders == key) { // ���� ����
				if (!newCurrent) { // ���� ��� ������ ��������� ������� 
					newCurrent = new Supplier; // �� ������� ������ ������ ������
					newList = newCurrent; // ���������� ������ ������� ����� ����������					
				}
				else { // ����� ������� ��������� ������� ������
					newCurrent->next = new Supplier;
					newCurrent = newCurrent->next;
				}
				SupplierCopyData(newCurrent, current);
			}
			current = current->next; // ����� ������������� ������ �� ��������� ������
		} while (current->next!=supplierList);

		if (newCurrent) {
			newCurrent->next = newList;
		}
	}
	
	return newList; // � ����� ���������� ����� ������
}
Supplier* FindOrderID(Supplier* supplierList, int key) {
	Supplier* newList = NULL;			// ����� ������, ������� ����� ������������ � �������� ����������
	Supplier* current = supplierList;		// ���������, � ������� �������� �������� �� ��������� ������
	Supplier* newCurrent = NULL;		// ��������� ��� ������ �������� �������� �� ������ � ������������

	if (current) { // ���� �������� ������ ����������
		do { // �� ���� �� ������ �� ��� �����
			for (int i = 0; i < current->quantityOrders;i++) {
				if (current->orderID[i] == key) { // ���� ����
					if (!newCurrent) { // ���� ��� ������ ��������� ������� 
						newCurrent = new Supplier; // �� ������� ������ ������ ������
						newList = newCurrent; // ���������� ������ ������� ����� ����������					
					}
					else { // ����� ������� ��������� ������� ������
						newCurrent->next = new Supplier;
						newCurrent = newCurrent->next;
					}
					break;
					SupplierCopyData(newCurrent, current);
				}
			}
			current = current->next; // ����� ������������� ������ �� ��������� ������
		} while (current->next != supplierList);
		if (newCurrent) {
			newCurrent->next = newList;
		}
	}

	return newList; // � ����� ���������� ����� ������
}