#include <iostream>
#include <vector>

using namespace std;

class customer {
private:
	string firstName, lastName;
	int age, cnp;
	string address;
	int bookedRoomNumber;
public:
	void setCustomerDetails(string firstName, string lastName, int age, int cnp, string address) {
		this->firstName = firstName;
		this->lastName = lastName;
		this->age = age;
		this->cnp = cnp;
		this->address = address;
		this->bookedRoomNumber = -1;
	}

	int getBookedRoomNumber() const {
		return bookedRoomNumber;
	}

	void bookRoom(int roomNumber) {
		bookedRoomNumber = roomNumber;
	}

	string getFirstName() const {
		return firstName;
	}

	string getLastName() const {
		return lastName;
	}

	int getAge() const {
		return age;
	}

	int getCNP() const {
		return cnp;
	}

	string getAddress() const {
		return address;
	}
};

class employee {
private:
	int employeePin;
public:
	void setPin() {
		cout << "Set the access PIN: ";
		cin >> employeePin;
	}
	int getPinFromEmployee() {
		int enteredPIN;
		cout << "Enter the access PIN: ";
		cin >> enteredPIN;
		return enteredPIN;
	}
	int getPin() {
		return employeePin;
	}
};

class room {
private:
	int roomNumber;
	string type;
	int capacity;
public:
	void setRoomDetails(int roomNumber, string type, int capacity) {
		this->roomNumber = roomNumber;
		this->type = type;
		this->capacity = capacity;
	}

	int getRoomNumber() const {
		return roomNumber;
	}

	string getRoomType() const {
		return type;
	}
};

void manageRooms(vector<room>& rooms) {
	int roomNumber, capacity;
	string type;
	int ok = 1;
	int roomCount = 0;
	int option;
	do {
		cout << "1. Add room." << endl;
		cout << "2. Delete room." << endl;
		cout << "3. Exit." << endl;
		cout << "Enter your option: " << endl;
		cin >> option;
		switch (option)
		{
		case 1:
			cout << "Enter room number: ";
			cin >> roomNumber;
			cout << "Enter room type: ";
			cin >> type;
			cout << "Enter room capacity: ";
			cin >> capacity;
			rooms.push_back(room());
			rooms.back().setRoomDetails(roomNumber, type, capacity);
			roomCount++;
			break;
		case 2:
			if (!rooms.empty()) {
				rooms.pop_back();
				roomCount--;
			}
			else
				cout << "No rooms to delete.";
			break;
		case 3:
			ok = 0;
			break;
		default:
			cout << "Invalid option. Please try again." << endl;
		}
	} while (ok == 1);
}

void checkin(vector<customer>& checkedInCustomers, vector<room>& rooms) {
	string firstName, lastName, address;
	int age, cnp;
	cout << "Enter first name: ";
	cin >> firstName;
	cout << "Enter last name: ";
	cin >> lastName;
	cout << "Enter age: ";
	cin >> age;
	cout << "Enter personal number: ";
	cin >> cnp;
	cout << "Enter address: (only city)";
	cin >> address;
	checkedInCustomers.push_back(customer());
	checkedInCustomers.back().setCustomerDetails(firstName, lastName, age, cnp, address);

	if (checkedInCustomers.back().getBookedRoomNumber() == -1) {
		bool roomAssigned = false;
		for (room& r : rooms) {
			if (r.getRoomNumber() != -1) {
				checkedInCustomers.back().bookRoom(r.getRoomNumber());
				r.setRoomDetails(r.getRoomNumber(), r.getRoomType(), -1);
				cout << "Customer " << firstName << " " << lastName << " booked room number " << r.getRoomNumber() << "." << endl;
				roomAssigned = true;
				break;
			}
		}

		if (!roomAssigned) {
			cout << "Sorry, no rooms are available at the moment." << endl;
		}
	}
	else {
		cout << "Customer " << firstName << " " << lastName << " is already booked in room number "
			<< checkedInCustomers.back().getBookedRoomNumber() << "." << endl;
	}
	
} 

void searchCustomer(const vector<customer>& customers) {
	string searchFirstName, searchLastName;
	cout << "Enter the first name of the customer: ";
	cin >> searchFirstName;
	cout << "Enter the last name of the customer: ";
	cin >> searchLastName;

	bool customerFound = false;

	for (const customer& c : customers) {
		if (c.getFirstName() == searchFirstName && c.getLastName() == searchLastName) {
			cout << "Customer " << c.getFirstName() << " " << c.getLastName()
				<< " " << c.getAge() << " " << c.getCNP() << " " << c.getAddress()
				<< " is booked in room number " << c.getBookedRoomNumber() << endl;
			customerFound = true;
			break;
		}
	}

	if (!customerFound) {
		cout << "Customer not found." << endl;
	}
}

void cancelReservation(vector<room>& rooms, vector<customer>& checkedInCustomers) {
	string firstName, lastName;
	int cancelledRoom;
	cout << "Enter the first name: ";
	cin >> firstName;
	cout << "Enter the last name: ";
	cin >> lastName;

	bool reservationCanceled = false;

	for (const customer& c : checkedInCustomers) {
		if (c.getFirstName() == firstName && c.getLastName() == lastName) {
			for (room& r : rooms) {
				cancelledRoom = c.getBookedRoomNumber();
				reservationCanceled = true;
			}
		}
	}

	cout << "You have canceled the reservation for room: " << cancelledRoom;
}

void checkout(vector<room>&rooms, vector<customer>&checkedInCustomers) {
	string firstName, lastName;
	int totalBill = 0;
	int totalStay;
	cout << "Enter the first name: ";
	cin >> firstName;
	cout << "Enter the last name: ";
	cin >> lastName;

	bool customerFound = false;

	for (const customer& c : checkedInCustomers) {
		if (c.getFirstName() == firstName && c.getLastName() == lastName) {
			customerFound = true;
			for (const room& r : rooms) {
				if (r.getRoomNumber() == c.getBookedRoomNumber()) {
					string roomType = r.getRoomType();

					cout << "Please enter the length of the stay: ";
					cin >> totalStay;

					if (roomType == "standard") {
						totalBill = totalStay * 160;
					}
					else {
						totalBill = totalStay * 250;
					}
					cout << "The final bill will be: " << totalBill << " RON" << endl;	
					}
				}
				break;
			}
		}
	if (!customerFound) {
		cout << "Customer not found or not checked in." << endl;
		}
	}


int main() {
	int option;
	employee a;
	a.setPin();
	int enteredPIN = a.getPinFromEmployee();
	if (enteredPIN == a.getPin())
		cout << "Welcome!" << endl;
	else {
		cout << "Incorrect PIN." << endl;
		exit(0);
	}

	vector<room> rooms;
	vector<customer> customers;

	customer customer;
	room room;

	do {
		cout << "--------------------" << endl;
		cout << "Hotel Management App" << endl;
		cout << "--------------------" << endl;
		cout << "1. Manage rooms." << endl;
		cout << "2. Check-in Details." << endl;
		cout << "3. Cancel reservation." << endl;
		cout << "4. Check-out Details." << endl;
		cout << "5. Search customer." << endl;
		cout << "6. Exit." << endl;
		cout << "Enter your option: " << endl;
		cin >> option;
			switch (option)
			{
			case 1:
				manageRooms(rooms);
				break;
			case 2:
				checkin(customers, rooms);
				break;
			case 3:
				cancelReservation(rooms, customers);
				break;
			case 4:
				checkout(rooms, customers);
				break;
			case 5:
				searchCustomer(customers);
				break;
			case 6:
				cout << "Shutting down..." << endl;
				exit(0);
				break;
			default:
				cout << "Invalid option. Please try again." << endl;
				break;
			}
	} while (1);

	return 0;
}
