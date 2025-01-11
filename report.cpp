

#include "report.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "employees.h"
#include "order.h"

using namespace std;

float Report::getSales() {
    return sales;
}

string Report::getCity() {
    return city;
}

float Report::getEmployeeCost() {
    return employee_cost;
}

void Report::setCity(string new_city) {
    city = new_city;
}

void Report::setSales(float new_sales) {
    sales = new_sales;
}

void Report::setEmployeeCost(float new_employeeCost) {
    employee_cost = new_employeeCost;
}

void Report::addOrderData(const string &filePath, string targetCity) {
   ifstream file(filePath);

   if(!file.is_open()){
       cerr << "Error opening file " << filePath << endl;
       return;
   }

   float sales = 0.0;
   string line;

   while(getline(file, line)) {
       stringstream ss(line);
       string city, clientName, product, quantity, price;

       getline(ss, city, ',');
       getline(ss, clientName, ',');
       getline(ss, product, ',');
       getline(ss, quantity, ',');
       getline(ss, price, ',');

       if(city == targetCity)
       {
           sales += stof(price);
       }
   }

   file.close();
    setSales(sales);

}

void Report::addEmployeeData(const string &filePath, string targetCity) {
    ifstream file(filePath);

    if(!file.is_open()){
        cerr << "Error opening file " << filePath << endl;
        return;
    }

    float cost = 0.0;
    string line;

    while(getline(file, line)) {
        stringstream ss(line);
        string role, name, surname, city;
        int salary, shiftStart, shiftEnd;

        getline(ss, role, ',');
        getline(ss, name, ',');
        getline(ss, surname, ',');
        ss >> salary; ss.ignore();
        ss >> shiftStart; ss.ignore();
        ss >> shiftEnd; ss.ignore();
        getline(ss, city, ',');

        if(city == targetCity)
        {
            cost += salary/30;
        }
    }
    setEmployeeCost(cost);

    file.close();
}

void Report::addToDB(const std::string &filePath) {
    ofstream file(filePath, ios::app);

    if(!file.is_open())
    {
        cerr << "Error opening file " << filePath << endl;
        return;
    }

    file << city << "," << sales << "," << employee_cost << endl;
    file.close();

}


