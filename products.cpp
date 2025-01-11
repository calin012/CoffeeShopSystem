

#include "products.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

using namespace std;

Product::Product(string genus, string type, string city, float production_cost, float price, int quantity)
        : genus(genus), type(type), city(city), production_cost(production_cost), price(price), quantity(quantity){
    profit = price - production_cost;
}

string Product::getGenus(){
    return genus;
}

string Product::getType(){
    return type;
}

float Product::getProductionCost(){
    return production_cost;
}

float Product::getPrice(){
    return price;
}

int Product::getQuantity(){
    return quantity;
}

string Product::getCity() {
    return city;
}

float Product::getProfit(){
    return profit;
}

void Product::setCost(float new_cost) {
    production_cost = new_cost;
}

void Product::setPrice(float new_price) {
    price = new_price;
}


void Product::addToDB(const string &filePath) const {
    ofstream file(filePath, ios::app);
    if (file.is_open()) {
        file << genus << "," << type << "," << city << "," << production_cost << "," << price << "," << profit << "," << quantity  << endl;
        file.close();
    } else {
        cerr << "Error writing in file " << filePath << endl;
    }
}

void Product::removeFromDB(const string &filePath) const {
    ifstream file(filePath);
    if (!file.is_open()) {
        cerr << "Error opening file " << filePath << endl;
        return;
    }

    vector<string> lines;
    string line;
    while (getline(file, line)) {
        istringstream stream(line);
        string fileGenus, fileType;
        getline(stream, fileGenus, ',');
        getline(stream, fileType, ',');

        if (fileGenus != genus || fileType != type) {
            lines.push_back(line);
        }
    }
    file.close();

    ofstream outFile(filePath, ios::trunc);
    if (outFile.is_open()) {
        for (const auto& l : lines) {
            outFile << l << "\n";
        }
        outFile.close();
    } else {
        cerr << "Error writing in file " << filePath << endl;
    }
}

vector<Product*> Product::readFromDB(const string& filePath) {
    vector<Product*> products;
    ifstream file(filePath);

    if (!file.is_open()) {
        cerr << "Error opening file: " << filePath << endl;
        return products;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string genus, type, city;
        float production_cost, price, profit;
        int quantity;

        getline(ss, genus, ',');
        getline(ss, type, ',');
        getline(ss, city, ',');
        ss >> production_cost; ss.ignore();
        ss >> price; ss.ignore();
        ss >> profit; ss.ignore();
        ss >> quantity; ss.ignore();

        if (genus == "Coffee") {
            products.push_back(new Coffee(type, city, production_cost, price, profit, quantity, true));
        } else if (genus == "Tea") {
            products.push_back(new Tea(type, city, production_cost, price, profit, quantity, true));
        } else if (genus == "Sandwich") {
            products.push_back(new Sandwich(type, city, production_cost, price, profit, quantity, true));
        } else if (genus == "Dessert") {
            products.push_back(new Dessert(type, city, production_cost, price, profit, quantity, true));
        }
    }

    file.close();
    return products;
}

void Product::updateQuantity(const string& filePath, int newQuantity) {
    ifstream file(filePath);
    if (!file.is_open()) {
        cerr << "Error opening file " << filePath << endl;
        return;
    }

    vector<string> lines;
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string fileGenus, fileType, fileCity;
        float fileProductionCost, filePrice, fileProfit;
        int fileQuantity;

        // Parse the line
        getline(ss, fileGenus, ',');
        getline(ss, fileType, ',');
        getline(ss, fileCity, ',');
        ss >> fileProductionCost; ss.ignore();
        ss >> filePrice; ss.ignore();
        ss >> fileProfit; ss.ignore();
        ss >> fileQuantity; ss.ignore();

        if (fileGenus == genus && fileType == type) {
            lines.push_back(fileGenus + "," + fileType + "," + fileCity + ","
                            + to_string(fileProductionCost) + "," + to_string(filePrice) + ","
                            + to_string(fileProfit) + "," + to_string(newQuantity));
        } else {
            lines.push_back(line);
        }
    }
    file.close();

    ofstream outFile(filePath, ios::trunc);
    if (outFile.is_open()) {
        for (const auto& l : lines) {
            outFile << l << "\n";
        }
        outFile.close();
    } else {
        cerr << "Error writing to file " << filePath << endl;
    }
}

void Product::outOfStock(const string& filePath) {
    ifstream file(filePath);
    if (!file.is_open()) {
        cerr << "Error opening file " << filePath << endl;
        return;
    }

    vector<string> lines;
    string line;
    while (getline(file, line)) {
        istringstream stream(line);
        string fileGenus, fileType, fileCity;
        float fileProductionCost, filePrice, fileProfit;
        int fileQuantity;

        getline(stream, fileGenus, ',');
        getline(stream, fileType, ',');
        getline(stream, fileCity, ',');
        stream >> fileProductionCost; stream.ignore();
        stream >> filePrice; stream.ignore();
        stream >> fileProfit; stream.ignore();
        stream >> fileQuantity; stream.ignore();

        if (fileQuantity != 0) {
            lines.push_back(line);
        }
    }
    file.close();

    ofstream outFile(filePath, ios::trunc);
    if (outFile.is_open()) {
        for (const auto& l : lines) {
            outFile << l << "\n";
        }
        outFile.close();
    } else {
        cerr << "Error writing in file " << filePath << endl;
    }
}

Coffee::Coffee(string type, string city, float prod_cost, float price, float profit, int quantity, bool in_stock)
        : Product("Coffee", type, city, prod_cost, price, quantity) {}

Tea::Tea(string type, string city, float prod_cost, float price, float profit, int quantity, bool in_stock)
        : Product("Tea", type, city, prod_cost, price, quantity) {}

Sandwich::Sandwich(string type, string city, float prod_cost, float price, float profit, int quantity, bool in_stock)
        : Product("Sandwich", type, city, prod_cost, price, quantity) {}

Dessert::Dessert(string type, string city, float prod_cost, float price, float profit, int quantity, bool in_stock)
        : Product("Dessert", type, city, prod_cost, price, quantity) {}
