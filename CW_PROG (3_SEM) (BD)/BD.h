
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

#ifndef BD
#define BD



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
const int customerLenght = 12;
const int supplierLenght = 10;					//Поставщик
const int deliveryTimeLenght = 15;				//Срок доставки
const int doorLenght = 10;

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


struct Door {
	int ID = NULL;
	Door* next = NULL;

	string type;
	string name;	
	string productionTime;
	float price = NULL;
	float priceOfAccessories = NULL;
	string typeOfAccessories;
};



struct Customer {

	int ID = NULL;
	Customer* next = NULL;

	string name;
	string surname;
	string phoneNumber;
};


struct Order {
	Order* next = NULL;

	int ID = NULL;

	int doorID = NULL;
	int customerID = NULL;
	string deliveryTime;
};

struct Supplier {
	int ID = NULL;

	string name;
	int quantityOrders = NULL;
	int* orderID = NULL;
	Supplier* next;
};


int* IntReSize(int* array, int oldSize, int newSize);

void FileReadDoor(string f_name, Door** doorList);
void PrintDoor(Door* doorList);
void AddDoor(Door** doorList);
bool DeleteDoor(Door** doorList, int position);
void DeleteDoorList(Door** doorList);
Door* GetDoor(Door* doorList, int position);
Door* FindTypeOfDoor(Door* doorList, string key);
Door* FindNameOfDoor(Door* doorList, string key);
Door* FindProductionTimeOfDoor(Door* doorList, string key);
Door* FindTypeOfAccessoriesOfDoor(Door* doorList, string key);
Door* FindPriceOfDoor(Door* doorList, float key);
Door* FindPriceOfAccessoriesOfDoor(Door* doorList, float key);




void FileReadCustomer(string f_name, Customer** doorList);
void PrintCustomer(Customer* doorList);
bool DeleteCustomer(Customer** customerList, int position);
void DeleteCustomerList(Customer** customerList);
Customer* GetCustomer(Customer* customerList, int position);
Customer* FindNameOfCustomer(Customer* customerList, string key);
Customer* FindSurnameOfCustomer(Customer* customerList, string key);
Customer* FindPhoneNumberOfCustomer(Customer* customerList, string key);



void FileReadSupplier(string f_name, Supplier** supplierList);
void PrintSupplier(Supplier* supplierList);
void SupplierInfo(Supplier* supplier, Order* orderList);



void AddOrder(Order** orderList, int doorID, int customerID,string deliveryTime);
void PrintOrder(Order* orderList);
bool DeleteOrder(Order** orderList, int position);
void DeleteOrderList(Order** orderList, int position);
Order* GetOrder(Order* orderList, int key);


#endif