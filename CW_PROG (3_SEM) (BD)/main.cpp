

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
	Order* orderList = NULL;

	string doorInputFile = "inputDoor.txt";
	string customerInputFile = "inputCustomer.txt";
	string user_answ;



	int answ = -1;
	while (answ != 0) {
		cout << "Добро пожаловать в меню!\nПожалуйста, выберите действие:\n"
			<< "1.Считать список дверей из файла.\n"
			<< "2.Считать список заказчиков из файла.\n"
			<< "3.Добавить заказ.\n"
			<< "4.Удалить дверь.\n"
			<< "5.Удалить все двери\n"
			<< "6.Удалить заказ\n"
			<< "7.Найти все двери с заданным типом.\n"
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

			system("cls");

			if (customerList && doorList) {
				
				tempDoor = NULL;
				tempCustomer = NULL;

				PrintDoor(doorList);
				cout << "Пожалуйста, выберите элемент для формирования заказа:";
				cin >> answ;
				tempDoor = GiveDoor(doorList, answ);

				PrintCustomer(customerList);
				cout << "Пожалуйста, выберите элемент для формирования заказа:";
				cin >> answ;
				tempCustomer = GiveCustomer(customerList, answ);

				if (tempDoor && tempCustomer) {
					cout << "Пожалуста, введите дату доставки:";
					cin >> user_answ;
					cout << "Формирование заказа\n";
					AddOrder(&orderList, tempDoor, tempCustomer,user_answ);
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
			
		case 4:
			system("cls");
			PrintDoor(doorList);
			cout << endl << "Укажите номер двери:";
			cin >> answ;
			system("cls");
			DeleteDoor(&doorList, answ);
			PrintDoor(doorList);
			system("pause");

		case 5:
			system("cls");
			DeleteDoorList(&doorList);
			PrintDoor(doorList);			
			break;

		case 6:
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

		case 7:

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

