

#ifndef SISTEM_CAFENEA_ORDER_H
#define SISTEM_CAFENEA_ORDER_H

#include <string>
using namespace std;

class Order{
private:
    string clientName;
    string city;
    string product;
    int quantity;
    float price;
public:
    Order(string clientName, string city, string product, int quantity, float price);

    string getClientName();
    string getCity();
    string getProduct();
    int getQuantity();
    float getPrice();

    void addToDB(const string& filePath);

};


#endif //SISTEM_CAFENEA_ORDER_H
