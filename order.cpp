

#include "order.h"
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

Order::Order(string clientName, string city, string product, int quantity, float price)
            : clientName(clientName), city(city), product(product), quantity(quantity), price(price) {};

string Order::getClientName() {
    return clientName;
}

string Order::getCity() {
    return city;
}

float Order::getPrice() {
    return price;
}

string Order::getProduct() {
    return product;
}
int Order::getQuantity() {
    return quantity;
}

void Order::addToDB(const std::string &filePath) {
    ofstream file(filePath, ios::app);

    if(!file.is_open())
    {
        cerr << "Error opening file " << filePath << endl;
        return;
    }

    file << city << "," << clientName << "," << product << "," << quantity << "," << price << endl;
    file.close();
}