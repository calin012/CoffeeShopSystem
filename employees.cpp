

#include "employees.h"
#include <fstream>
#include <vector>
#include <sstream>
#include <iostream>
using namespace std;

Employee::Employee(string name, string surname, string role, int salary, int workingHours_start,
                   int workingHours_end, string city)
                   : name(name), surname(surname), role(role), salary(salary), workingHours_start(workingHours_start), workingHours_end(workingHours_end), city(city){};

string Employee::getName() { return name; }
string Employee::getSurname() { return surname; }
string Employee::getRole() { return role; }
int Employee::getSalary() { return salary; }
int Employee::getShiftStart() { return workingHours_start; }
int Employee::getShiftEnd() { return workingHours_end; }
string Employee::getCity() { return city; }


void Employee::addToDB(const string &file) const {
    ofstream fileVar(file, ios::app);
    if(fileVar.is_open()) {
        fileVar << name << "," << surname << "," << role << "," << salary << "," << workingHours_start << "," << workingHours_end << "," << city << "\n";
        fileVar.close();
    }
    else{
        cerr << "Error opening file " << file << endl;
    }
}

void Employee::removeFromDB(const string &file) const {
    ifstream fileVar(file);
    if (!fileVar.is_open()) {
        cerr << "Error opening file " << file << endl;
        return;
    }

    vector<string> lines;
    string line;
    while(getline(fileVar, line)){
        istringstream stream(line);
        string currentName, currentSurname;
        getline(stream, currentName, ',');
        getline(stream, currentSurname, ',');
        if (currentName != name || currentSurname != surname) {
            lines.push_back(line);
        }
    }
    fileVar.close();

    ofstream outFile(file, ios::trunc);
    if(outFile.is_open()) {
        for(const auto& l : lines)
        {
            outFile << l << "\n";
        }
        outFile.close();
    }
    else
        cerr << "Error writing in file " << file;
}

vector<Employee*> Employee::readFromDB(const string& fileName) {
    vector<Employee*> employees;
    ifstream file(fileName);

    ///Exceptions
    if (!file.is_open()) {
        throw runtime_error("Error opening file: " + fileName);
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string name, surname, role, city;
        int salary, shiftStart, shiftEnd;

        getline(ss, name, ',');
        getline(ss, surname, ',');
        getline(ss, role, ',');
        ss >> salary; ss.ignore();
        ss >> shiftStart; ss.ignore();
        ss >> shiftEnd; ss.ignore();
        getline(ss, city, ',');

        if (role == "Barista") {
            employees.push_back(new Barista(name, surname, salary, shiftStart, shiftEnd, city));
        } else if (role == "Manager") {
            employees.push_back(new Manager(name, surname, salary, shiftStart, shiftEnd, city));
        } else if (role == "Server") {
            employees.push_back(new Server(name, surname, salary, shiftStart, shiftEnd, city));
        } else {
            employees.push_back(new Employee(name, surname, role, salary, shiftStart, shiftEnd, city));
        }
    }

    file.close();
    return employees;
}


///Polimorfism(prin constructor) + abstractizare
Barista::Barista(string name, string surname, int salary, int workingHours_start, int workingHours_end, string city) : Employee(name, surname, "Barista", salary, workingHours_start, workingHours_end, city) {}

Manager::Manager(string name, string surname, int salary, int workingHours_start, int workingHours_end, string city) : Employee(name, surname, "Manager", salary, workingHours_start, workingHours_end, city) {}

Server::Server(string name, string surname, int salary, int workingHours_start, int workingHours_end, string city) : Employee(name, surname, "Server", salary, workingHours_start, workingHours_end, city) {}
