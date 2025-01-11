

#ifndef SISTEM_CAFENEA_REPORT_H
#define SISTEM_CAFENEA_REPORT_H
#include <string>

using namespace std;

class Report {
private:
    string city;
    float sales;
    float employee_cost;
public:
    float getSales();
    float getEmployeeCost();
    string getCity();

    void setSales(float new_profit);
    void setEmployeeCost(float new_employeeCost);
    void setCity(string new_city);
    void addOrderData(const string& filePath, string targetCity);
    void addEmployeeData(const string& filePath, string targetCity);
    void addToDB(const string& filePath);
};


#endif //SISTEM_CAFENEA_REPORT_H
