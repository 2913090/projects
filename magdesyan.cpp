#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;



class Guest {
private:
	int id;
	string name;
	int age;
	string phone;
	int roomNumber = -1;
	static int curId;
public:
	Guest(string name, int age, string phone) : name(name), age(age), phone(phone), id(curId++){}

	~Guest() = default;

	void setCurId(int newId) {
		curId = newId;
	}

	void setRoomNumber(int roomNumber) {
		this->roomNumber = roomNumber;
	}

	int getRoomNumber() {
		return roomNumber;
	}
	void info() {
		cout << "\tId гостя: " << id << endl;
		cout << "\tИмя гостя: " << name << endl;
		cout << "\tВозраст гостя: " << age << endl;
		cout << "\tТелефон гостя: " << phone << endl;
	}
};

class Room {
private:
	int id;
	int number;
	string title;
	int beds;
	bool status = 0;
	int price;
	vector<Guest*> guests;
protected:
	static int curId;
	Room(int number, string title, int beds, int price) : id(curId++), number(number), title(title), beds(beds), price(price){}
public:
	void checkInGuest(Guest* guest) {
		guests.push_back(guest);
		status = 1;
	}

	int getNumber() {
		return number;
	}

	bool getStatus() {
		return status;
	}

	void setStatus(bool newStatus) {
		status = newStatus;
	}

	void setNumber(int newNumber) {
		number = newNumber;
	}

	void addGuest(Guest* guest) {
		if (guests.size() < beds) {
			guests.push_back(guest);
		}
		else { throw exception("Комната уже заполнена"); }
	}

	void info() {
		cout << "Id комнаты: " << this->id << endl;
		cout << "Номер комнаты: " << this->number << endl;
		cout << "Описание комнаты: " << this->title << endl;
		cout << "Кроватей в комнате: " << this->beds << endl;
		cout << "Кто проживает в комнате: ";
		if (status) {
			cout << endl;
			for (int i = 0; i < guests.size(); i++) {
				guests[i]->info();
			}
		}
		else { cout << "никто"; }
	}
};


class StandartRoom : public Room {
public:
	StandartRoom(int number, string title, int beds) : Room(number, title, beds, 5000){}
};

class VIPRoom : public Room {
public:
	VIPRoom(int number, string title, int beds) : Room(number, title, beds, 5000) {}
};

class PremiumRoom : public Room {
public:
	PremiumRoom(int number, string title, int beds) : Room(number, title, beds, 5000) {}
};

class LuxRoom : public Room {
public:
	LuxRoom(int number, string title, int beds) : Room(number, title, beds, 5000) {}
};

class Bill {
private:
	int id;
	int idGuest;
	int idRoom;


	int amount;
	static int curId;
public:

};

class HotelManegement {
private:
	vector<Room*> rooms;
	vector<Guest*> guests;
public:
	void checkInGuest(Guest* guest, int roomNumber) {
		for (int i = 0; i < rooms.size(); i++) {
			if (rooms[i]->getNumber() == roomNumber) {
				if (!rooms[i]->getStatus()) {
					guests.push_back(guest);
					rooms[i]->checkInGuest(guest);
					return;
				}
				else { throw exception("Комната уже занята"); }
			}
		}
		throw exception("Комната не найдена");
	}

	void addRoom(int type, int number, string title, int beds) {
		for (int i = 0; i < rooms.size(); i++) {
			if (rooms[i]->getNumber() == number) {
				throw exception("Номер комнаты не должен повторяться");
			}
		}
		switch (type) {
		case 1:
			rooms.push_back(new StandartRoom(number, title, beds));
			break;
		case 2:
			rooms.push_back(new VIPRoom(number, title, beds));
			break;
		case 3:
			rooms.push_back(new PremiumRoom(number, title, beds));
			break;
		case 4:
			rooms.push_back(new LuxRoom(number, title, beds));
			break;
		default:
			throw exception("Введенное значение некорректно");
		}
	}

	void addGuest(Guest* guest, int roomNumber) {
		for (int i = 0; i < rooms.size(); i++) {
			if (rooms[i]->getNumber() == roomNumber) {
				if (rooms[i]->getStatus()) {
					guests.push_back(guest);
					rooms[i]->addGuest(guest);
					return;
				}
				else { throw exception("Комната не занята"); }
			}
		}
		throw exception("Комната не найдена");
	}

	void info() {
		for (int i = 0; i < rooms.size(); i++) {
			rooms[i]->info();
			cout << endl << endl;
		}
	}

	void infoGuests() {
		for (int i = 0; i < guests.size(); i++) {
			guests[i]->info();
		}
	}
};


int Room::curId = 1;
int Guest::curId = 1;
int Bill::curId = 1;
int main()
{
	setlocale(LC_ALL, "");
	try {
		HotelManegement manager;
		manager.addRoom(1, 123, "Отличная комната", 2);
		manager.addRoom(2, 321, "Превосходная комната", 3);
		manager.info();

		cout << endl << endl;
		Guest* guest1 = new Guest("Oleg", 23, "23456");
		Guest* guest2 = new Guest("Igor", 32, "123321");
		Guest* guest3 = new Guest("Dimon", 51, "38443");
		manager.checkInGuest(guest1, 123);
		manager.addGuest(guest2, 123);
		manager.checkInGuest(guest3, 321);
		manager.info();
	}
	catch (exception ex) {
		cout << ex.what();
	}
	catch (...) {
		cout << "Неизвестная ошибка";
	}


	//ofstream out;
	//out.open("guests.txt");
	//if (out.is_open()) {
	//	out << "text";
	//}
	//out.close();






	//string line;
	//ifstream in("guests.txt");
	//if (in.is_open()) {
	//	while (getline(in, line)) {
	//		
	//	}
	//}
}