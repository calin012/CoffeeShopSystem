
#include "event.h"
#include <iostream>
#include <fstream>

using namespace std;


Event::Event(string eventType, float budget, float profit, int noOfEmployees, string city)
        : eventType(eventType), cost(budget), profit(profit), noOfEmployees(noOfEmployees), city(city) {}

string Event::getEventType() {
    return eventType;
}

float Event::getBudget() {
    return cost;
}

float Event::getProfit() {
    return profit;
}

int Event::getNoOfEmployees() {
    return noOfEmployees;
}

string Event::getCity() {
    return city;
}

void Event::setEventType(string type) {
    eventType = type;
}

void Event::setBudget(float new_budget) {
    cost = new_budget;
}

void Event::setProfit(float new_profit) {
    profit = new_profit;
}

void Event::setNoOfEmployees(int new_noOfEmployees) {
    noOfEmployees = new_noOfEmployees;
}

void Event::setCity(string new_city) {
    city = new_city;
}

void Event::addToDB(const string &filePath) {
    ofstream file(filePath, ios::app);

    if (!file.is_open()) {
        cerr << "Error opening file: " << filePath << endl;
        return;
    }

    file << eventType << "," << cost << "," << profit << ","
         << noOfEmployees << "," << city << endl;

    file.close();
}
