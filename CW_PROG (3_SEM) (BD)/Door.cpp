


#include "BD.h"





void DoorCopyData(Door* newCurrent, Door* current) {
	newCurrent->ID = current->ID;
	newCurrent->type = current->type; // И копируем данные
	newCurrent->name = current->name;
	newCurrent->price = current->price;
	newCurrent->productionTime = current->productionTime;
	newCurrent->priceOfAccessories = current->priceOfAccessories;
	newCurrent->typeOfAccessories = current->typeOfAccessories;
}

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
				current->ID = stoi(temp);
				temp = "";
				ifs >> current->type;
				ifs >> current->name;
				ifs >> current->price;
				ifs >> current->productionTime;
				ifs >> current->priceOfAccessories;
				ifs >> current->typeOfAccessories;
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
			<< setw(typeOfAccessoriesLenght)	<< topRightCorner;
		
		cout << endl << setfill(space) << verticalLine
			<< setw(numberLenght - 1)				<< "#"				<< right << verticalLine
			<< setw(typeLenght - 1)					<< "Type"			<< right << verticalLine
			<< setw(nameLenght - 1)					<< "Name"			<< right << verticalLine
			<< setw(priceLenght - 1)				<< "Price"			<< right << verticalLine
			<< setw(productionTimeLenght - 1)		<< "ProductionTime" << right << verticalLine
			<< setw(priceOfAccessoriesLenght - 1)	<< "Consumables"	<< right << verticalLine
			<< setw(typeOfAccessoriesLenght - 1)	<< "Consumables type"<< right << verticalLine;

		while (current != NULL) {  // Печать производится пока не достигнем конца списка
			// Печать верхней части ячеек.
			cout << endl << setfill(horizontalLine) << rightJunction
				<< setw(numberLenght)			    << crossJunction
				<< setw(typeLenght)				    << crossJunction
				<< setw(nameLenght)				    << crossJunction
				<< setw(priceLenght)			    << crossJunction
				<< setw(productionTimeLenght)	    << crossJunction
				<< setw(priceOfAccessoriesLenght)   << crossJunction
				<< setw(typeOfAccessoriesLenght)	<< leftJunction;

			// Печать самих значений и вертикальных линий (между ячейками таблицы)
			cout << endl << setfill(space)				<< verticalLine
				 << setw(numberLenght - 1)				<< current->ID							<< right << verticalLine
				 << setw(typeLenght - 1)				<< current->type				<< right << verticalLine
				 << setw(nameLenght - 1)				<< current->name				<< right << verticalLine
				 << setw(priceLenght - 1)				<< current->price				<< right << verticalLine
				 << setw(productionTimeLenght - 1)		<< current->productionTime		<< right << verticalLine
				 << setw(priceOfAccessoriesLenght - 1)	<< current->priceOfAccessories  << right << verticalLine
				 << setw(typeOfAccessoriesLenght - 1)	<< current->typeOfAccessories	<< right << verticalLine;
			
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
			<< setw(typeOfAccessoriesLenght) <<  bottomRightCorner<<endl;



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
			
		}
		i = current->ID;
		current->next = new Door;
		current = current->next;
	}

	// Ручной ввод значений полей
	current->ID = i++;
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
}                                      //!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//Удаление элемента в заданной позиции
bool DeleteDoor(Door** doorList, int position) {

	Door* current = *doorList;
	Door* del;				   // Указатель на удаляемый элемент 

	if (doorList) {
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
Door* GetDoor(Door* doorList, int position) {
	Door* current = doorList; // Вспомогательный указатель для движения по списку
	Door* newCurrent;
	if (doorList) {	 // Если список существует	
		while (current) {
			if (current->ID == position) {
				newCurrent = new Door;
				DoorCopyData(newCurrent, current);
				return current;
			}
			current = current->next;
		}
	}
	return NULL;
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
				DoorCopyData(newCurrent, current);
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
				DoorCopyData(newCurrent, current); // И копируем данные
			}
			current = current->next; // Далее передвигаемся вперед по основному списку
		}
	}

	return newList; // В конце возвращаем новый список
}
Door* FindProductionTimeOfDoor(Door* doorList, string key) {

	Door* newList = NULL;			// Новый список, который будет возвращаться в качестве результата
	Door* current = doorList;		// Указатель, с помощью которого движемся по основному списку
	Door* newCurrent = NULL;		// Указатель при помощи которого движемся по списку с результатами

	if (current) { // Если исходный список существует
		while (current) { // То пока не дойдем до его конца
			if (current->productionTime == key) { // Ищем ключ
				if (!newCurrent) { // Если это первый найденный элемент 
					newCurrent = new Door; // То создаем корень нового списка
					newList = newCurrent; // Запоминаем корень который будем возвращать					
				}
				else { // Иначе создаем следующий элемент списка
					newCurrent->next = new Door;
					newCurrent = newCurrent->next;
				}
				DoorCopyData(newCurrent, current); // И копируем данные
			}
			current = current->next; // Далее передвигаемся вперед по основному списку
		}
	}

	return newList; // В конце возвращаем новый список
}
Door* FindTypeOfAccessoriesOfDoor(Door* doorList, string key) {

	Door* newList = NULL;			// Новый список, который будет возвращаться в качестве результата
	Door* current = doorList;		// Указатель, с помощью которого движемся по основному списку
	Door* newCurrent = NULL;		// Указатель при помощи которого движемся по списку с результатами

	if (current) { // Если исходный список существует
		while (current) { // То пока не дойдем до его конца
			if (current->typeOfAccessories == key) { // Ищем ключ
				if (!newCurrent) { // Если это первый найденный элемент 
					newCurrent = new Door; // То создаем корень нового списка
					newList = newCurrent; // Запоминаем корень который будем возвращать					
				}
				else { // Иначе создаем следующий элемент списка
					newCurrent->next = new Door;
					newCurrent = newCurrent->next;
				}
				 
				DoorCopyData(newCurrent, current);// И копируем данные
			}
			current = current->next; // Далее передвигаемся вперед по основному списку
		}
	}

	return newList; // В конце возвращаем новый список
}
Door* FindPriceOfDoor(Door* doorList, float key) {

	Door* newList = NULL;			// Новый список, который будет возвращаться в качестве результата
	Door* current = doorList;		// Указатель, с помощью которого движемся по основному списку
	Door* newCurrent = NULL;		// Указатель при помощи которого движемся по списку с результатами

	if (current) { // Если исходный список существует
		while (current) { // То пока не дойдем до его конца
			if (current->price == key) { // Ищем ключ
				if (!newCurrent) { // Если это первый найденный элемент 
					newCurrent = new Door; // То создаем корень нового списка
					newList = newCurrent; // Запоминаем корень который будем возвращать					
				}
				else { // Иначе создаем следующий элемент списка
					newCurrent->next = new Door;
					newCurrent = newCurrent->next;
				}
				DoorCopyData(newCurrent, current); // И копируем данные
			}
			current = current->next; // Далее передвигаемся вперед по основному списку
		}
	}

	return newList; // В конце возвращаем новый список
}
Door* FindPriceOfAccessoriesOfDoor(Door* doorList, float key) {

	Door* newList = NULL;			// Новый список, который будет возвращаться в качестве результата
	Door* current = doorList;		// Указатель, с помощью которого движемся по основному списку
	Door* newCurrent = NULL;		// Указатель при помощи которого движемся по списку с результатами

	if (current) { // Если исходный список существует
		while (current) { // То пока не дойдем до его конца
			if (current->priceOfAccessories == key) { // Ищем ключ
				if (!newCurrent) { // Если это первый найденный элемент 
					newCurrent = new Door; // То создаем корень нового списка
					newList = newCurrent; // Запоминаем корень который будем возвращать					
				}
				else { // Иначе создаем следующий элемент списка
					newCurrent->next = new Door;
					newCurrent = newCurrent->next;
				}
				DoorCopyData(newCurrent, current); // И копируем данные
			}
			current = current->next; // Далее передвигаемся вперед по основному списку
		}
	}

	return newList; // В конце возвращаем новый список
}

