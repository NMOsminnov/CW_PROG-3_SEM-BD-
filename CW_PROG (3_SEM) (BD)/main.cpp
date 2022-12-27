

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
	Order* tempOrder = NULL;

	string doorInputFile = "inputDoor.txt";
	string customerInputFile = "inputCustomer.txt";
	string supplierInputFile = "inputSupplier.txt";
	string orderInputFile = "inputOrder.txt";
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
			<< "5.Считать все что только можно.\n"
			<< "0.Выход из программы\n"
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
				cout << "Раздел: Действия со списками заказчиков.\n"
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
					PrintCustomer(customerList);
					cout << "\n Введите ID удаляемого элемента:";
					cin >> answ;
					if (DeleteCustomer(&customerList, answ)) {
						system("cls");
						PrintCustomer(customerList);
						cout << "\n\nЭлемент c ID:" << answ << " успешно удален.\n";
					}
					else {
						system("cls");
						PrintCustomer(customerList);
						cout << "\n\nЭлемент c ID:" << answ << " не найден.\n";
					}
					system("pause");
					break;

				case 6:
					system("cls");
					DeleteCustomerList(&customerList);
					PrintCustomer(customerList);
					cout << "Список успешно удален!\n";
					system("pause");
					break;

				}
			}
			break;

		case 3:

			while (answ != 0) {


				system("cls");
				cout << "Раздел: Действия со списками заказов.\n"
					<< "Пожалуйста, укажите действие.\n\n"
					<< "1.Считать список заказов из файла.\n"
					<< "2.Добавить заказ.\n"
					<< "3.Печать списка заказов в консоль.\n"
					<< "4.Поиск по полям.\n"
					<< "5.Удаление заказа.\n"
					<< "6.Удаление списка заказов.\n"
					<< "0.Выход из раздела.\n"
					<< "Ваш ответ:";
				cin >> answ;

				switch (answ) {
				case 1:
					system("cls");
					FileReadOrder(orderInputFile, &orderList);
					PrintOrder(orderList);
					system("pause");
					break;

				case 2:
					system("cls");
					if (doorList && customerList) {
						PrintDoor(doorList);
						cout << "Пожалуйста, введите ID двери:";
						cin >> answ;

						tempDoor = GetDoor(doorList, answ);
						system("cls");
						if (!tempDoor) {
							cout << "Дверь не найдена\n";
							system("pause");
							break;
						}
						PrintCustomer(customerList);
						cout << "Пожалуйста, введите ID заказчика:";
						cin >> answ1;

						tempCustomer = GetCustomer(customerList, answ1);
						if (!tempCustomer) {
							cout << "Заказчик не найден\n";
							system("pause");
							break;
						}
						cout << "Пожалуйста, введите срок доставки.\n";
						cin >> user_answ;
						system("cls");
						AddOrder(&orderList, answ, answ1, user_answ);
						PrintOrder(orderList);
						system("pause");
					}
					else {
						if (!doorList) {
							cout << "Нет списка дверей\n";
						}
						if (!customerList) {
							cout << "Нет списка заказчиков\n";
						}
					}
					break;

				case 3:
					system("cls");
					PrintOrder(orderList);
					system("pause");
					break;

				case 4:
					if (orderList) {
						tempOrder = orderList;
						while (answ != 0) {
							system("cls");
							cout << "Раздел: Поиск в заказах "
								<< "Выберите вариант из перечисленных ниже:\n"
								<< "1.Поиск по ID.\n"
								<< "2.Поиск по ID двери.\n"
								<< "3.Поиск по ID поставщика.\n"
								<< "4.Поиск по сроку доставки.\n"
								<< "5.Вывести текущий список.\n"
								<< "6.Сброс поиска.\n"
								<< "0.Выход из раздела.\n"
								<< "Ваш ответ:";

							cin >> answ;

							switch (answ) {
							case 1:
								system("cls");
								cout << "Введите ID заказа:";
								cin >> answ;
								tempOrder = GetOrder(tempOrder, answ);
								PrintOrder(tempOrder);
								system("pause");
								break;

							case 2:
								system("cls");
								cout << "Введите ID двери:";
								cin >> answ;
								tempOrder = FindDoorID(tempOrder, answ);
								PrintOrder(tempOrder);
								system("pause");
								break;

							case 3:
								system("cls");
								cout << "Введите ID заказчика:";
								cin >> answ;
								tempOrder = FindCustomerID(tempOrder, answ);
								PrintOrder(tempOrder);
								system("pause");
								break;

							case 4:
								system("cls");
								cout << "Введите срок доставки:";
								cin >> user_answ;
								tempOrder = FindDeliveryTime(tempOrder, user_answ);
								PrintOrder(tempOrder);
								system("pause");
								break;

							case 5:
								system("cls");
								PrintOrder(tempOrder);
								system("pause");
								break;

							case 6:
								if (tempOrder != orderList) {
									DeleteOrderList(&tempOrder);
									tempOrder = orderList;
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
										DeleteOrderList(&tempOrder);
										tempOrder = NULL;
										orderList = NULL;
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
					PrintOrder(orderList);
					cout << "\n Введите ID удаляемого элемента:";
					cin >> answ;
					if (DeleteOrder(&orderList, answ)) {
						system("cls");
						PrintOrder(orderList);
						cout << "\n\nЭлемент c ID:" << answ << " успешно удален.\n";
					}
					else {
						system("cls");
						PrintOrder(orderList);
						cout << "\n\nЭлемент c ID:" << answ << " не найден.\n";
					}
					system("pause");
					break;

				case 6:
					system("cls");
					DeleteOrderList(&orderList);
					PrintOrder(orderList);
					cout << "Список успешно удален!\n";
					system("pause");
					break;

				}
			}
			break;

		case 4:
			if (orderList) {
				while (answ != 0) {

					system("cls");
					cout << "Раздел: Действия со списками поставщиков.\n"
						<< "Пожалуйста, укажите действие.\n\n"
						<< "1.Считать список поставщиков из файла.\n"
						<< "2.Добавить поставщика.\n"
						<< "3.Печать списка поставщиков в консоль.\n"
						<< "4.Поиск по полям.\n"
						<< "5.Вывод ифнормации о поставщике.\n"
						<< "6.Удаление поставщика.\n"
						<< "7.Удаление списка поставщиков.\n"
						<< "0.Выход из раздела.\n"
						<< "Ваш ответ:";
					cin >> answ;

					switch (answ) {
					case 1:
						system("cls");

						FileReadSupplier(supplierInputFile, &supplierList, orderList);
						PrintSupplier(supplierList);
						system("pause");
						break;

					case 2:
						system("cls");
						AddSupplier(&supplierList, orderList);
						break;

					case 3:
						system("cls");
						PrintSupplier(supplierList);
						system("pause");
						break;

					case 4:
						if (supplierList) {
							tempSupplier = supplierList;
							while (answ != 0) {
								system("cls");
								cout << "Раздел: Поиск в поставщиках "
									<< "Выберите вариант из перечисленных ниже:\n"
									<< "1.Поиск по ID поставщика.\n"
									<< "2.Поиск по имени поставщика.\n"
									<< "3.Поиск по количеству заказов.\n"
									<< "4.Поиск по ID заказа.\n"
									<< "5.Вывести текущий список.\n"
									<< "6.Сброс поиска.\n"
									<< "0.Выход из раздела.\n"
									<< "Ваш ответ:";

								cin >> answ;

								switch (answ) {
								case 1:
									system("cls");
									cout << "Введите ID поставщика:";
									cin >> answ;
									tempSupplier = FindSupplierID(tempSupplier, answ);
									PrintSupplier(tempSupplier);
									system("pause");
									break;

								case 2:
									system("cls");
									cout << "Введите ID двери:";
									cin >> user_answ;
									tempSupplier = FindSupplierName(tempSupplier, user_answ);
									PrintSupplier(tempSupplier);
									system("pause");
									break;

								case 3:
									system("cls");
									cout << "Введите количество заказов:";
									cin >> answ;
									tempSupplier = FindQuantityOrders(tempSupplier, answ);
									PrintSupplier(tempSupplier);
									system("pause");
									break;

								case 4:
									system("cls");
									cout << "Введите срок доставки:";
									cin >> user_answ;
									tempSupplier = FindOrderID(tempSupplier, answ);
									PrintSupplier(tempSupplier);
									system("pause");
									break;

								case 5:
									system("cls");
									PrintSupplier(tempSupplier);
									system("pause");
									break;

								case 6:
									if (tempSupplier != supplierList) {
										DeleteSupplierList(&tempSupplier);
										tempSupplier = supplierList;
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
											DeleteSupplierList(&tempSupplier);
											tempSupplier = NULL;
											supplierList = NULL;
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
						PrintSupplier(supplierList);
						cout << "Введите ID элемента:";
						cin >> answ;
						tempSupplier = FindSupplierID(supplierList, answ);
						SupplierInfo(tempSupplier,orderList);
						system("pause");
						break;
					case 6:
						system("cls");
						PrintSupplier(supplierList);
						cout << "\n Введите ID удаляемого элемента:";
						cin >> answ;
						if (DeleteSupplier(&supplierList, answ)) {
							system("cls");
							PrintSupplier(supplierList);
							cout << "\n\nЭлемент c ID:" << answ << " успешно удален.\n";
						}
						else {
							system("cls");
							PrintSupplier(supplierList);
							cout << "\n\nЭлемент c ID:" << answ << " не найден.\n";
						}
						system("pause");
						break;

					case 7:
						system("cls");
						DeleteSupplierList(&supplierList);
						PrintSupplier(supplierList);
						cout << "Список успешно удален!\n";
						system("pause");
						break;
					}

				}
			}
			else {
			system("cls");
			cout << "Сначала необходимо создать список заказов.\n";
			system("pause");
			}
			break;
		case 5: // Меня достало заново все считывать! Пусть все считывается 1 кнопкой!
			FileReadDoor(doorInputFile, &doorList);
			FileReadCustomer(customerInputFile, &customerList);
			FileReadOrder(orderInputFile, &orderList);
			FileReadSupplier(supplierInputFile, &supplierList, orderList);
			break;
		case 0:
			exit(0);
			break;
		}
		answ = -1;
	}

}

