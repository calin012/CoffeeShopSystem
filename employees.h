#

#include <string>
#include <vector>
#ifndef SISTEM_CAFENEA_EMPLOYEES_H
#define SISTEM_CAFENEA_EMPLOYEES_H
using namespace std;


class Employee{
    ///Incapsulare
protected:
    string name;
    string surname;
    string role;
    int salary;
    int workingHours_start;
    int workingHours_end;
    string city;


public:
    Employee(string name, string surname, string role, int salary, int workingHours_start, int workingHours_end, string city);
    virtual ~Employee() = default;

    string getName();
    string getSurname();
    string getRole();
    int getSalary();
    int getShiftStart();
    int getShiftEnd();
    string getCity();
    void addToDB(const string& file) const;
    void removeFromDB(const string& file) const;
    static vector<Employee*> readFromDB(const string& file);
};


///Mostenire

class Barista : public Employee{
public:
    Barista(string name, string surname, int salary, int workingHours_start, int workingHours_end, string city);
};

class Manager : public Employee{
public:
    Manager(string name, string surname, int salary, int workingHours_start, int workingHours_end, string city);
};

class Server : public Employee{
public:
    Server(string name, string surname, int salary, int workingHours_start, int workingHours_end, string city);
};


#endif //SISTEM_CAFENEA_EMPLOYEES_H
