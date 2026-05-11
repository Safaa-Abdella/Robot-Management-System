// Robot Management System🤖.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
//Developed by Safaa Yasser// C++ OOP Project - University Assignment


#include <iostream>
#include <string>
#include "Robot.h"
using namespace std;

class Robot {
protected:
	int id;
	int batteryLevel;
	string name;
	string status;
	string lastMaintenance;
	string maintenanceSchedule;

public:
	// Constructor 
	Robot(int i,int bL, string n, string s, string mDate, string schedule) {
		id = i;
		name = n;
		setStatus(s);
		lastMaintenance = mDate;
		maintenanceSchedule = schedule;
		batteryLevel = bL;
	}

	// Getters 
	int getID() { return id; }
	int getBatteryLevel() { return batteryLevel; }
	string getName() { return name; }
	string getStatus() { return status; }
	string getMaintenance() { return lastMaintenance; }
	string getMaintenanceSchedule() { return maintenanceSchedule; }

	// Setters 

	void setBatteryLevel(int bL) {
		if (bL >= 0 && bL <= 100) {
			batteryLevel = bL;
		}
		else {
			cout << "Error: Battery Level must be between 0 and 100!" << endl;
		}
	}

	void setStatus(string s) {
		if (s == "Working" || s == "In maintenance" || s == "Charging" || s =="Stopped") {
			status = s;
		}
		else {
			cout << "Error: This status is not recognized!" << endl;
		}
	}

	void setMaintenance(string mDate, string time) {
		lastMaintenance = "Date  " + mDate + " at " + time;
	}

	void setMaintenanceSchedule(string schedule) {
		maintenanceSchedule = schedule;
	}

	// Display 
	void display() {
		cout << "   ****************   " << endl;
		cout << "ID: " << id << endl;
		cout << "Name: " << name << endl;
		cout << "Status: " << status << endl;
		cout << "Battery Level: " << batteryLevel << "%" << endl;
		cout << "Last Maintenance : " << lastMaintenance << endl;
		cout << "Maintenance Schedule: << " << maintenanceSchedule <<" >>" << endl;
		cout << "   ****************   " << endl;
	}

	// Default task  
	virtual void task() {
		cout << "Robot " << name << " has no specific task assigned." << endl;
	}

	// Default update
	virtual void updateMaintenance() {
		cout << "No maintenance update available." << endl;
	}
};

// Cleaning Robot 
class CleaningRobot : public Robot {
public:
	CleaningRobot(int i, int bL ,string n, string mDate, string schedule, string s )
		: Robot(i, bL, n, s, mDate, schedule) {
	}

	void task() override {
		cout << "Task Assigned: Robot " << name << " is vacuuming and mopping floors." << endl;
	}

	void updateMaintenance() override {
		setMaintenanceSchedule("Daily: Clean brushes and empty dust bin.");
		cout << "Maintenance Schedule updated for: " << name << endl;
		cout << getMaintenanceSchedule() << endl;
	}
};

// Security Robot 
class SecurityRobot : public Robot {
public:
	SecurityRobot(int i, int bL ,string n, string mDate, string schedule, string s )
		: Robot(i, bL ,n, s, mDate, schedule) {
	}

	void task() override {
		cout << "Task Assigned: Robot " << name << " is scanning the perimeter for intruders." << endl;
	}

	void updateMaintenance() override {
		setMaintenanceSchedule("Weekly: Check camera sensors and night vision.");
		cout << "Maintenance Schedule updated for: " << name << endl;
		cout << "Schedule " << getMaintenanceSchedule() << endl;
	}
};

// Delivery Robot 
class DeliveryRobot : public Robot {
public:

	// We add default value in case user didn't enter any value

	DeliveryRobot(int i, int bL ,string n, string mDate, string schedule, string s)
		: Robot(i, bL, n, s, mDate, schedule) {
	}

	void task() override {
		cout << "Task Assigned: Robot " << name << " is navigating to deliver the package." << endl;
	}

	void updateMaintenance() override {
		setMaintenanceSchedule("Every 50 miles: Check wheel alignment and battery health.");
		cout << "Maintenance Schedule updated for: " << name << endl;
		cout << "Schedule " << getMaintenanceSchedule() << endl;
	}
};
// Main function 
int main(){

	Robot* robots[100];
	int count = 0;
	int choice;
	do {
		cout << "==============================================\n";
		cout << "|           Robot Managment System           |\n";
		cout << "==============================================\n";
		cout << "1. Add New Robot                             |\n";
		cout << "2. Assign Task                               |\n";
		cout << "3. Set Maintenance Schedule                  |\n";
		cout << "4. Charge & Status Update                    |\n";
		cout << "5. Search for Robot by ID                    |\n";
		cout << "6. Emergency Shutdown                        |\n";
		cout << "7. Delete Robot                              |\n";
		cout << "8. Display All Robots                        |\n";
		cout << "0. Exit                                      |\n";
		cout << "==============================================\n";
		cout << "Enter Choice: ";
		cin >> choice;

		// Add 
		switch (choice) {
		case 1: {
			int type, id, batteryLevel;
			string name, status, date, schedule;
			cout << "Choose Type:( 1- Cleaning  2- Security  3- Delivery ) : ";
			cin >> type;

			cout << "Enter ID: ";
			cin >> id;

			cout << "Enter Name: ";
			cin.ignore();//CLEARING THE INPUT BUFFER
			getline(cin, name);

			cout << "Enter Status (Working / In maintenance / Charging / Stopped) :";
			getline(cin, status);

			cout << "Enter Initial Battery Level (0 - 100):";
			cin >> batteryLevel;

			cout << "Enetr Last Maintenance Date : ";
			cin.ignore();
			getline(cin, date);


			if (type == 1)
				robots[count++] = new CleaningRobot(id, batteryLevel, name, date, schedule, status);
			else if (type == 2)
				robots[count++] = new SecurityRobot(id, batteryLevel, name, date, schedule, status);
			else
				robots[count++] = new DeliveryRobot(id, batteryLevel, name, date, schedule, status);
			break;
		}


			  // Tasks 				
		case 2: {
			int id;
			cout << "Enter Robot ID to Assign Task: ";
			cin >> id;
			bool found = false;

			for (int i = 0; i < count; i++) {
				if (robots[i]->getID() == id) {

					if (robots[i]->getBatteryLevel() <= 20) {
						cout << "Ohhh ,The Battery is Low!" << endl;
						cout << "Robot [ " << robots[i]->getName() << " ] " << " Battery is " << robots[i]->getBatteryLevel() << " %\n";
						cout << "You Must Charge The Robot Before Assign any Task." << endl;
						found = true;
					}
					else {
						robots[i]->task();
						cout << "-------------------------------\n";
					}

				}
				if (!found) cout << "Robot Not found!" << endl;
			}
			break;
		}

			  // Maintenance 
		case 3: {
			int id;
			string date, time;

			cout << "Enter ID: ";
			cin >> id;

			cout << "Date: ";
			cin >> date;

			cout << "Time: ";
			cin >> time;

			bool found = false;

			for (int i = 0; i < count; i++) {
				if (robots[i]->getID() == id) {
					robots[i]->setMaintenance(date, time);
					robots[i]->updateMaintenance();
					found = true;
				}
			}
			if (!found)
				cout << "Robot Not Found" << endl;
			else
				cout << "Maintenance Updated!\n";

			break;
		}

			  //Charge & Status Update
		case 4: {
			int id;
			cout << "Enter Robot ID to Charge: ";
			cin >> id;

			bool found = false;

			for (int i = 0; i < count; i++) {
				if (robots[i]->getID() == id) {
					robots[i]->setBatteryLevel(100);
					robots[i]->setStatus("Charging");

					cout << "Robot: " << robots[i]->getName() << " is now Charging" << endl;
					cout << "Battery Level is now: " << robots[i]->getBatteryLevel() << "%" << endl;
					found = true;
				}
			}
			if (!found)
				cout << "Robot Not Found" << endl;
			break;
		}

			  //Search
		case 5: {
			int id;
			cout << "Enter Robot ID: ";
			cin >> id;

			bool found = false;
			for (int i = 0; i < count; i++) {
				if (robots[i]->getID() == id) {
					robots[i]->display();

					found = true;
				}
			}
			if (!found)
				cout << "Robot Not Found" << endl;

			break;
		}

			  //Emergency Shutdown
		case 6: {

			int id;
			cout << "Enter Robot ID: ";
			cin >> id;

			for (int i = 0; i < count; i++) {
				if (robots[i]->getID() == id) {
					robots[i]->setStatus("Stopped");
				}
			}
			cout << "Robot Stopped!\n";

			break;
		}

			  //Delete
		case 7: {
			int id;
			cout << "Enter Robot ID to Delete: ";
			cin >> id;

			for (int i = 0; i < count; i++) {
				if (robots[i]->getID() == id) {
					robots[i] = robots[count - 1];
					cout << "Robot Deleted Succssfully." << endl;
				}
			}
			break;
		}

			  //Disply
		case 8: {
			for (int i = 0; i < count; i++) {
				robots[i]->display();
				cout << "-------------------------------\n";
			}
			break;
		}

		default: {
			cout << "Invalid choise";
		}

		}
		} while (choice != 0);
		return 0;
	}