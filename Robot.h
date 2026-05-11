#ifndef ROBOT_H

#define ROBOT_H

#include<iostream>
#include<string>
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
	
	Robot(int i, int bL, string n, string s, string mDate, string schedule);

	 
	int getID();
	int getBatteryLevel();
	string getName();
	string getStatus();
	string getMaintenance();
	string getMaintenanceSchedule();

	

	void setBatteryLevel(int bL);
	void setStatus(string s);
	void setMaintenance(string mDate, string time);
	void setMaintenanceSchedule(string schedule);

	
	void display();

	
	virtual void task();
	virtual void updateMaintenance ();
};


//Child Clases

class CleaningRobot : public Robot {
public:
	CleaningRobot(int i, int bL, string n, string mDate, string schedule, string s);

	void task() override;

	void updateMaintenance() override;
};



class SecurityRobot : public Robot {
public:
	SecurityRobot(int i, int bL, string n, string mDate, string schedule, string s);

	void task() override;

	void updateMaintenance() override;
	};

	 
class DeliveryRobot : public Robot {
public:
	DeliveryRobot(int i, int bL, string n, string mDate, string schedule, string s);

	void task() override;

	void updateMaintenance() override;
};

#endif