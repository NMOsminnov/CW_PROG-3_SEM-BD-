

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
		system("cls");
		cout << "Добро пожаловать в меню!\nПожалуйста, выберите раздел с действиями:\n"
			<< "1.Двери\n"
			<< "2.Заказчики\n"
			<< "3.Заказы\n"
			<< "4.Поставщики\n"
			<< "Ваш ответ:";

		cin >> answ;

		switch (answ) {
		case 1:
			while (answ != 0) {
				system("cls");
				cout << "Раздел: Действия со списками дверей.\n"
					<< "Пожалуйста, укажите действие.\n\n"
					<< "1.Считать список дверей из файла.\n"
					<< "2.Добавить дверь.\n"
					<< "3.Печать списка дверей в консоль.\n"
					<< "4.Поиск по полям.\n"
					<< "5.Удаление двери.\n"
					<< "6.Удаление списка дверей\n"
					<< "0.Выход из раздела.\n"
					<< "Ваш ответ:";
				cin >> answ;

				switch (answ) {
				case 1:
					system("cls");
					FileReadDoor(doorInputFile, &doorList);
					PrintDoor(doorList);
					system("pause");
					break;

				case 2:
					system("cls");
					AddDoor(&doorList);
					PrintDoor(doorList);
					system("pause");
					break;

				case 3:
					system("cls");
					PrintDoor(doorList);
					system("pause");
					break;

				case 4:
					if (doorList) {
						tempDoor = doorList;
						while (answ != 0) {
							system("cls");
							cout << "Раздел: Поиск "
								<< "Выберите вариант из перечисленных ниже:\n"
								<< "1.Поиск по ID.\n"
								<< "2.Поиск по типу.\n"
								<< "3.Поиск по имени.\n"
								<< "4.Поиск по времени производства.\n"
								<< "5.Поиск по типу фурнитуры.\n"
								<< "6.Поиск по цене двери.\n"
								<< "7.Поиск по цене фурнитуры.\n"
								<< "8.Вывести текущий список.\n"
								<< "9.Сброс поиска.\n"
								<< "0.Выход из раздела.\n"
								<< "Ваш ответ:";

							cin >> answ;

							switch (answ) {
							case 1:
								system("cls");
								cout << "Введите ID двери:";
								cin >> answ;
								tempDoor = GetDoor(tempDoor, answ);
								PrintDoor(tempDoor);
								system("pause");
								break;

							case 2:
								system("cls");
								cout << "Введите тип двери:";
								cin >> user_answ;
								tempDoor = FindTypeOfDoor(tempDoor, user_answ);
								PrintDoor(tempDoor);
								system("pause");
								break;

							case 3:
								system("cls");
								cout << "Введите имя элемента:";
								cin >> user_answ;
								tempDoor = FindNameOfDoor(tempDoor, user_answ);
								PrintDoor(tempDoor);
								system("pause");
								break;

							case 4:
								system("cls");
								cout << "Введите время производства двери:";
								cin >> user_answ;
								tempDoor = FindProductionTimeOfDoor(tempDoor, user_answ);
								PrintDoor(tempDoor);
								system("pause");
								break;

							case 5:
								system("cls");
								cout << "Введите тип фурнитуры:";
								cin >> user_answ;
								tempDoor = FindTypeOfAccessoriesOfDoor(tempDoor, user_answ);
								PrintDoor(tempDoor);
								system("pause");
								break;

							case 6:
								system("cls");
								cout << "Введите цену двери:";
								cin >> answ;
								tempDoor = FindPriceOfDoor(tempDoor, answ);
								PrintDoor(tempDoor);
								system("pause");
								break;

							case 7:
								system("cls");
								cout << "Введите стоимость фурнитуры:";
								cin >> answ;
								tempDoor = FindPriceOfAccessoriesOfDoor(tempDoor, answ);
								PrintDoor(tempDoor);
								system("pause");
								break;

							case 8:
								system("cls");
								PrintDoor(tempDoor);
								system("pause");
								break;

							case 9:
								if (tempDoor != doorList) {
									DeleteDoorList(&tempDoor);
									tempDoor = doorList;
									cout << "Список сброшен!\n";
									system("pause");
								}
								else {
									cout << "Внимание! Попытка удаления данного спсика удалит исходный список дверей.\n"
										<< "Для подтверждения удаления введите \"1\".\n"
										<< "Для пропуска действия введите любой другой символ или набор символов\n"
										<< "Ваш ответ:";
									cin >> user_answ;
									if (user_answ == "1") {
										DeleteDoorList(&tempDoor);
										tempDoor = NULL;
										doorList = NULL;
										cout << "Список сброшен!\n";
										system("pause");
									}
								}
							}
						}
					}
					else {
						cout << "Текущий список пуст. Пожалуйста, заполните список.\n";
						system("pause");
					}
					break;

				case 5:
					system("cls");
					PrintDoor(doorList);
					cout << "\n Введите ID удаляемого элемента:";
					cin >> answ;
					if (DeleteDoor(&doorList, answ)) {
						system("cls");
						PrintDoor(doorList);
						cout << "\n\nЭлемент c ID:" << answ << " успешно удален.\n";
					}
					else {
						system("cls");
						PrintDoor(doorList);
						cout << "\n\nЭлемент c ID:" << answ << " не найден.\n";
					}
					system("pause");
					break;

				case 6:
					system("cls");
					DeleteDoorList(&doorList);
					PrintDoor(doorList);
					cout << "Список успешно удален!\n";
					system("pause");
					break;
				}
			}
			break;

		case 2:

			while (answ != 0) {


				system("cls");
				cout << "Раздел: Действия со списками дверей.\n"
					<< "Пожалуйста, укажите действие.\n\n"
					<< "1.Считать список заказчиков из файла.\n"
					<< "2.Добавить заказчика.\n"
					<< "3.Печать списка заказчиков в консоль.\n"
					<< "4.Поиск по полям.\n"
					<< "5.Удаление заказчика.\n"
					<< "6.Удаление списка заказчиков.\n"
					<< "0.Выход из раздела.\n"
					<< "Ваш ответ:";
				cin >> answ;

				switch (answ) {
				case 1:
					system("cls");
					FileReadCustomer(customerInputFile, &customerList);
					PrintCustomer(customerList);
					system("pause");
					break;

				case 2:
					system("cls");
					AddCustomer(&customerList);
					PrintCustomer(customerList);
					system("pause");
					break;

				case 3:
					system("cls");
					PrintCustomer(customerList);
					system("pause");
					break;

				case 4:
					if (customerList) {
						tempCustomer = customerList;
						while (answ != 0) {
							system("cls");
							cout << "Раздел: Поиск "
								<< "Выберите вариант из перечисленных ниже:\n"
								<< "1.Поиск по ID.\n"
								<< "2.Поиск по имени.\n"
								<< "3.Поиск по фамилии.\n"
								<< "4.Поиск по номеру телефона.\n"
								<< "5.Вывести текущий список.\n"
								<< "6.Сброс поиска.\n"
								<< "0.Выход из раздела.\n"
								<< "Ваш ответ:";

							cin >> answ;

							switch (answ) {
							case 1:
								system("cls");
								cout << "Введите ID заказчика:";
								cin >> answ;
								tempCustomer = GetCustomer(tempCustomer, answ);
								PrintCustomer(tempCustomer);
								system("pause");
								break;

							case 2:
								system("cls");
								cout << "Введите имя заказчика:";
								cin >> user_answ;
								tempCustomer = FindNameOfCustomer(tempCustomer, user_answ);
								PrintCustomer(tempCustomer);
								system("pause");
								break;

							case 3:
								system("cls");
								cout << "Введите фамилию заказчика:";
								cin >> user_answ;
								tempCustomer = FindSurnameOfCustomer(tempCustomer, user_answ);
								PrintCustomer(tempCustomer);
								system("pause");
								break;

							case 4:
								system("cls");
								cout << "Введите номер телефона заказчика:";
								cin >> user_answ;
								tempCustomer = FindPhoneNumberOfCustomer(tempCustomer, user_answ);
								PrintCustomer(tempCustomer);
								system("pause");
								break;

							case 5:
								system("cls");
								PrintCustomer(tempCustomer);
								system("pause");
								break;

							case 6:
								if (tempCustomer != customerList) {
									DeleteCustomerList(&tempCustomer);
									tempCustomer = customerList;
									cout << "Список сброшен!\n";
									system("pause");
								}
								else {
									cout << "Внимание! Попытка удаления данного спсика удалит исходный список заказчиков!\n"
										<< "Для подтверждения удаления введите \"1\".\n"
										<< "Для пропуска действия введите любой другой символ или набор символов.\n"
										<< "Ваш ответ:";
									cin >> user_answ;
									if (user_answ == "1") {
										DeleteDoorList(&tempDoor);
										tempDoor = NULL;
										doorList = NULL;
										cout << "Список сброшен!\n";
										system("pause");
									}
								}
							}
						}
					}
					else {
						cout << "Текущий список пуст. Пожалуйста, заполните список.\n";
						system("pause");
					}
					break;

				case 5:
					system("cls");
					PrintDoor(doorList);
					cout << "\n Введите ID удаляемого элемента:";
					cin >> answ;
					if (DeleteDoor(&doorList, answ)) {
						system("cls");
						PrintDoor(doorList);
						cout << "\n\nЭлемент c ID:" << answ << " успешно удален.\n";
					}
					else {
						system("cls");
						PrintDoor(doorList);
						cout << "\n\nЭлемент c ID:" << answ << " не найден.\n";
					}
					system("pause");
					break;

				case 6:
					system("cls");
					DeleteDoorList(&doorList);
					PrintDoor(doorList);
					cout << "Список успешно удален!\n";
					system("pause");
					break;

				}
			}
			break;

		}
		answ = -1;
	}

}

