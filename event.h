

#ifndef SISTEM_CAFENEA_EVENT_H
#define SISTEM_CAFENEA_EVENT_H

#include "employees.h"
#include <string>

using namespace std;


class Event {
private:
    string eventType;
    string city;
    int noOfEmployees;
    float cost;
    float profit;
public:
    Event(string eventType, float budget, float profit, int noOfEmployees, string oras);

    string getEventType();
    float getBudget();
    float getProfit();
    int getNoOfEmployees();
    string getCity();

    void setEventType(string type);
    void setBudget(float new_budget);
    void setProfit(float new_profit);
    void setNoOfEmployees(int new_noOfEmployees);
    void setCity(string new_city);
    void addToDB(const string& filePath);

};


#endif //SISTEM_CAFENEA_EVENT_H
