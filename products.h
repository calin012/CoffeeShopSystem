//
// Created by user on 06/01/2025.
//

#include <string>
#include <vector>
#ifndef SISTEM_CAFENEA_PRODUCTS_H
#define SISTEM_CAFENEA_PRODUCTS_H
using namespace std;

class Product{
protected:

    string genus;
    string type;
    string city;
    float production_cost;
    float price;
    float profit;
    int quantity;
public:

    Product(string genus, string type, string city, float prod_cost, float price, int quantity);
    virtual ~Product() = default;

    string getGenus();
    string getType();
    float getProductionCost();
    float getPrice();
    float getProfit();
    int getQuantity();
    string getCity();

    void setGenus(string new_genus);
    void setType(string new_type);
    void setCity(string new_city);
    void setCost(float new_cost);
    void setPrice(float new_price);
    void addToDB(const string& filePath) const;
    void removeFromDB(const string& filePath) const;
    static vector<Product*> readFromDB(const string& filePath);
    void updateQuantity(const string& filePath, int newQuantity);
    void outOfStock(const string& filename); ///Remove items with 0 quantity from DB
};

class Coffee : public Product{
public:
    Coffee(string type, string city, float prod_cost, float price, float profit, int quantity, bool in_stock);
};

class Tea : public Product{
public:
    Tea(string type, string city, float prod_cost, float price, float profit, int quantity, bool in_stock);
};

class Sandwich : public Product{
public:
    Sandwich(string type, string city, float prod_cost, float price, float profit, int quantity, bool in_stock);
};

class Dessert : public Product{
public:
    Dessert(string type, string city, float prod_cost, float price, float profit, int quantity, bool in_stock);
};


#endif //SISTEM_CAFENEA_PRODUCTS_H
