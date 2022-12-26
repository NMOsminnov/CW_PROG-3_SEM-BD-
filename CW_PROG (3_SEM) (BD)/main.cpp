

#include <iostream>

#include "BD.h"



using namespace std;

int main()
{
	setlocale(LC_ALL, "ru");
	Door* doorList = NULL;
	Door* tempDoor = NULL;
	Customer* customerList = NULL;
	Customer* tempCustomer = NULL;
	Supplier* supplierList = NULL;
	Supplier* tempSupplier = NULL;
	Order* orderList = NULL;

	string doorInputFile = "inputDoor.txt";
	string customerInputFile = "inputCustomer.txt";
	string supplierInputFile = "inputSupplier.txt";
	string user_answ;



	int answ = -1;
	int answ1 = 0;
	while (answ != 0) {
		cout << "Добро пожаловать в меню!\nПожалуйста, выберите действие:\n"
			<< "1.Считать список дверей из файла.\n"
			<< "2.Считать список заказчиков из файла.\n"
			<< "3.Считать список поставщиков.\n"
			<< "4.Добавить заказ.\n"
			<< "5.Удалить дверь.\n"
			<< "6.Удалить все двери\n"
			<< "7.Удалить заказ\n"
			<< "8.Найти все двери с заданным типом.\n"
			<< "Ваш ответ:";

		cin >> answ;

		switch (answ) {
		case 1:
			system("cls");
			FileReadDoor(doorInputFile, &doorList);
			PrintDoor(doorList);
			break;

		case 2:
			system("cls");
			FileReadCustomer(customerInputFile,&customerList);
			PrintCustomer(customerList);

			break;
			
		case 3:
			FileReadSupplier(supplierInputFile,&supplierList);
			PrintSupplier(supplierList);
			break;

		case 4:

			system("cls");

			if (customerList && doorList) {
				
				tempDoor = NULL;
				tempCustomer = NULL;

				PrintDoor(doorList);
				cout << "Пожалуйста, выберите элемент для формирования заказа:";
				cin >> answ;
				tempDoor = GetDoor(doorList, answ);
				

				PrintCustomer(customerList);
				cout << "Пожалуйста, выберите элемент для формирования заказа:";
				cin >> answ1;
				tempCustomer = GetCustomer(customerList, answ1);
				

				if (tempDoor && tempCustomer) {
					cout << "Пожалуста, введите дату доставки:";
					cin >> user_answ;
					cout << "Формирование заказа\n";
					AddOrder(&orderList, answ, answ1,user_answ);
					PrintOrder(orderList);
				}
				else {
					if (!tempDoor) {
						cout << "Указанная дверь не найдена\n";
					}
					if (!tempCustomer) {
						cout << "Указанный заказчик не найден\n";
					}
				}
			}
			else {
				if (!doorList) {
					cout << "Нет списка дверей.\n";
				}
				if (!customerList) {
					cout << "Нет списка заказчиков.\n";
				}
			}
			break;
			
		case 5:
			system("cls");
			PrintDoor(doorList);
			cout << endl << "Укажите номер двери:";
			cin >> answ;
			system("cls");
			DeleteDoor(&doorList, answ);
			PrintDoor(doorList);
			system("pause");

		case 6:
			system("cls");
			DeleteDoorList(&doorList);
			PrintDoor(doorList);			
			break;

		case 7:
			system("cls");
			if (orderList) {
				PrintOrder(orderList);
				cout << "ВЫберите элемент для удаления:";
				cin >> answ;
				if (DeleteOrder(&orderList, answ)) {
					system("cls");
					PrintOrder(orderList);
					cout << "Удален элемент с номером " << answ << " .\n";
				}
				else {
					cout << "Элемент не найден.\n";
				}
		
			}
			break;

		case 8:

			if (doorList) {
				cout << "Пожалуйста, введите ключ:";
				cin >> user_answ;

				tempDoor = FindTypeOfDoor(doorList, user_answ);
				PrintDoor(tempDoor);
			}

			break;
			
			answ = -1;
		}
	}

}

