#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "employees.h"
#include "products.h"
#include "order.h"
#include "report.h"
#include "event.h"

using namespace std;

///Se pot observa usor multitudinea de exemple de utilizare a claselor, obiectelor, constructorilor si destructorilor
///Astfel nu a fost comentata utilizarea lor in mod specific

void manageEmployees() {
    string fileName = "employees.csv";
    int choice;
    cout << "Employee Management:\n";
    cout << "1. Add Employee\n";
    cout << "2. Delete Employee\n";
    cout << "3. Show All Employees\n";
    cin >> choice;

    if (choice == 1) {
        string name, surname, role, city;
        int salary, start, end;
        cout << "Enter name, surname, role, salary, shift start, shift end, city:\n";
        cin >> name >> surname >> role >> salary >> start >> end >> city;

        Employee emp(name, surname, role, salary, start, end, city);
        emp.addToDB(fileName);

    } else if (choice == 2) {
        string name, surname;
        cout << "Enter name and surname of the employee to delete:\n";
        cin >> name >> surname;

        vector<Employee*> employees = Employee::readFromDB(fileName);

        ofstream outFile(fileName, ios::trunc);
        if (!outFile.is_open()) {
            cerr << "Error writing to file: " << fileName << endl;
            return;
        }

        bool found = false;
        for (const auto& emp : employees) {
            if (emp->getName() == name && emp->getSurname() == surname) {
                found = true;
                delete emp;
                continue;
            }
            outFile << emp->getName() << "," << emp->getSurname() << "," << emp->getRole() << ","
                    << emp->getSalary() << "," << emp->getShiftStart() << "," << emp->getShiftEnd() << ","
                    << emp->getCity() << "\n";
            delete emp;
        }
        outFile.close();

        if (found) {
            cout << "Employee deleted successfully.\n";
        } else {
            cout << "Employee not found.\n";
        }

    } else if (choice == 3) {
        vector<Employee*> employees = Employee::readFromDB(fileName);
        for (const auto& emp : employees) {
            cout << emp->getName() << " " << emp->getSurname() << " " << emp->getRole() << " " << emp->getSalary() << " " << emp->getShiftStart() << " " << emp->getShiftEnd() << " " <<emp->getCity() << "\n";
            delete emp;
        }
    } else {
        cout << "Invalid choice!\n";
    }
}


void manageProducts() {
    string fileName = "products.csv";
    int choice;
    cout << "Product Management:\n";
    cout << "1. Add Product\n";
    cout << "2. Delete Product\n";
    cout << "3. Show Products\n";
    cout << "4. Modify Product Quantity\n";
    cout << "5. Remove Out-of-Stock Products\n";
    cin >> choice;

    if (choice == 1) {
        string genus, type, city;
        float prod_cost, price;
        int quantity;
        cout << "Enter genus, type, city, production cost, price, quantity:\n";
        cin >> genus >> type >> city >> prod_cost >> price >> quantity;

        Product prod(genus, type, city, prod_cost, price, quantity);
        prod.addToDB(fileName);
    } else if (choice == 2) {
        string genus, type;
        cout << "Enter genus and type of product to delete:\n";
        cin >> genus >> type;

        Product prod(genus, type, "", 0, 0, 0);
        prod.removeFromDB(fileName);
    } else if (choice == 3) {
        vector<Product*> products = Product::readFromDB(fileName);
        for (const auto& prod : products) {
            cout << prod->getGenus() << " " << prod->getType() << " " << prod->getCity() << " " << prod->getProductionCost() << " " << prod->getPrice() << " " << prod->getQuantity() << "\n";
            delete prod;
        }
    } else if (choice == 4) {
        string genus, type, city;
        int quantity;
        cout << "Enter genus, type, city, and new quantity:\n";
        cin >> genus >> type >> city >> quantity;

        Product prod(genus, type, city, 0, 0, 0);
        prod.updateQuantity(fileName, quantity);
    } else if (choice == 5) {
        Product temp("", "", "", 0, 0, 0);
        temp.outOfStock(fileName);
        cout << "Out-of-stock products removed successfully.\n";
    } else {
        cout << "Invalid choice!\n";
    }
}

void manageOrders() {
    string productsFile = "products.csv";
    string ordersFile = "orders.csv";

    string clientName, city, product;
    int quantity;

    cout << "Enter client name, city, product, and quantity:\n";
    cin >> clientName >> city >> product >> quantity;

    ifstream file(productsFile);
    if (!file.is_open()) {
        cerr << "Error opening products file: " << productsFile << endl;
        return;
    }

    vector<string> lines;
    string line;
    float unitPrice = 0.0;
    bool productFound = false;

    while (getline(file, line)) {
        stringstream ss(line);
        string fileGenus, fileType, fileCity;
        float productionCost, price, profit;
        int fileQuantity;

        getline(ss, fileGenus, ',');
        getline(ss, fileType, ',');
        getline(ss, fileCity, ',');
        ss >> productionCost; ss.ignore();
        ss >> price; ss.ignore();
        ss >> profit; ss.ignore();
        ss >> fileQuantity; ss.ignore();

        if (fileType == product && fileCity == city) {
            if (fileQuantity < quantity) {
                cerr << "Error: Not enough stock available.\n";
                file.close();
                return;
            }

            fileQuantity -= quantity;
            unitPrice = price;
            productFound = true;

            lines.push_back(fileGenus + "," + fileType + "," + fileCity + ","
                            + to_string(productionCost) + "," + to_string(price) + ","
                            + to_string(profit) + "," + to_string(fileQuantity));
        } else {
            lines.push_back(line);
        }
    }
    file.close();

    if (!productFound) {
        cerr << "Error: Product not found in the specified city.\n";
        return;
    }

    ofstream outFile(productsFile, ios::trunc);
    if (outFile.is_open()) {
        for (const auto& l : lines) {
            outFile << l << "\n";
        }
        outFile.close();
    } else {
        cerr << "Error writing to products file.\n";
        return;
    }

    float totalPrice = unitPrice * quantity;

    Order order(clientName, city, product, quantity, totalPrice);
    order.addToDB(ordersFile);

    cout << "Order placed successfully! Total price: " << totalPrice << "\n";
}


void manageReports() {
    string ordersFile = "orders.csv";
    string employeesFile = "employees.csv";
    string reportFile = "reports.csv";

    string city;
    cout << "Enter city for daily report:\n";
    cin.ignore();
    getline(cin, city);

    if (city.empty()) {
        cout << "City cannot be empty. Returning to main menu.\n";
        return;
    }

    Report report;
    report.setCity(city);
    report.addOrderData(ordersFile, city);
    report.addEmployeeData(employeesFile, city);
    report.addToDB(reportFile);

    cout << "Report created for city: " << city << "\n";
}


void manageEvents() {
    string fileName = "events.csv";

    string eventType, city;
    int noOfEmployees;

    cout << "Enter event type (Music Night, Coffee Tasting, Unlimited Coffee):\n";
    cin.ignore();
    getline(cin, eventType);

    cout << "Enter city and number of employees:\n";
    cin >> city >> noOfEmployees;

    float cost = 0.0;
    if (eventType == "Music Night") {
        cost = 1000.0 + (noOfEmployees * 50.0);
    } else if (eventType == "Coffee Tasting") {
        cost = 800.0 + (noOfEmployees * 30.0);
    } else if (eventType == "Unlimited Coffee") {
        cost = 1200.0 + (noOfEmployees * 40.0);
    } else {
        cerr << "Error: Invalid event type.\n";
        return;
    }

    float profit = 1.5 * cost;

    Event event(eventType, cost, profit, noOfEmployees, city);
    event.addToDB(fileName);

    cout << "Event added successfully! Cost: " << cost << ", Profit: " << profit << "\n";
}



int main() {
    while (true) {
        cout << "Select a category:\n";
        cout << "1. Employees\n";
        cout << "2. Products\n";
        cout << "3. Order\n";
        cout << "4. Reports\n";
        cout << "5. Events\n";
        cout << "6. Exit\n";

        int category;
        cin >> category;

        switch (category) {
            case 1:
                manageEmployees();
                break;
            case 2:
                manageProducts();
                break;
            case 3:
                manageOrders();
                break;
            case 4:
                manageReports();
                break;
            case 5:
                manageEvents();
                break;
            case 6:
                cout << "Exiting...\n";
                return 0;
            default:
                cout << "Invalid category!\n";
        }
    }
}
