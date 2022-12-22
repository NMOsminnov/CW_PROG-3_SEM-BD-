
#include <iostream>

using namespace std;

#ifndef BD
#define BD

struct Door {
	Door* next = NULL;

	string type;
	string name;
	float price = NULL;
	string productionTime;
	float priceOfAccessories = NULL;
	string supplier;
	string typeOfAccessories;	
};

struct Customer {
	Customer* next = NULL;

	string name;
	string surname;
	string phoneNumber;
};


struct Order {
	Order* next = NULL;

	int number = NULL;

	Door* door = NULL;
	Customer* customer = NULL;
	string deliveryTime;
};


void FileReadDoor(string f_name, Door** doorList);
void PrintDoor(Door* doorList);
bool DeleteDoor(Door** doorList, int position);
void DeleteDoorList(Door** doorList);
Door* GiveDoor(Door* doorList, int position);
Door* FindTypeOfDoor(Door* doorList, string key);
Door* FindNameOfDoor(Door* doorList, string key);
Door* FindPriceOfDoor(Door* doorList, float key);
Door* FindProductionTimeOfDoor(Door* doorList, string key);
Door* FindPriceOfAccessoriesOfDoor(Door* doorList, float key);
Door* FindSupplierOfDoor(Door* doorList, string key);
Door* FindTypeOfAccessoriesOfDoor(Door* doorList, string key);

void FileReadCustomer(string f_name, Customer** doorList);
void PrintCustomer(Customer* doorList);
bool DeleteCustomer(Customer** customerList, int position);
void DeleteCustomerList(Customer** customerList);
Customer* GiveCustomer(Customer* customerList, int position);
Customer* FindNameOfCustomer(Customer* customerList, string key);
Customer* FindSurnameOfCustomer(Customer* customerList, string key);
Customer* FindPhoneNumberOfCustomer(Customer* customerList, string key);


void AddOrder(Order** orderList, Door* door, Customer* customer,string deliveryTime);
void PrintOrder(Order* orderList);
bool DeleteOrder(Order** orderList, int position);
void DeleteOrderList(Order** orderList, int position);
Order* FindIndexOfOrder(Order* orderList, int key);
Order* FindDoorTypeOfOrder(Order* orderList, string key);
Order* FindDoorNameOfOrder(Order* orderList, string key);
Order* FindDoorPriceOfOrder(Order* orderList, float key);
Order* FindDoorProductionTimeOfOrder(Order* orderList, string key);
Order* FindDoorPriceOfAccessoriesOfOrder(Order* orderList, float key);
Order* FindDoorSupplierOfOrder(Order* orderList, string key);
Order* FindDoorTypeOfAccessoriesOfOrder(Order* orderList, string key);
Order* FindCustomerNameOfOrder(Order* orderList, string key);
Order* FindCustomerSurnameOfOrder(Order* orderList, string key);
Order* FindCustomerPhoneNumberOfOrder(Order* orderList, string key);
Order* FindDeliveryTimeOfOrder(Order* orderList, string key);

#endif