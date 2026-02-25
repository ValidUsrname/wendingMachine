#ifndef WENDING_MACHINE_H
#define WENDING_MACHINE_H

#include<string>
#include<vector>

class Item {
public:
    //Constructor
    Item() = default;
    Item(const std::string& itemName, float itemPrice, short itemQty);
    //Getter (Accessor)
    std::string getItemName();
    short getItemPrice();
    short getItemQty();
    //Setter (Mutator)
    void setItemName(std::string itemName);
    void setItemPrice(float itemPrice);
    void setItemQty(short itemQty);
    //Methods
    bool isAvailable();
private:
    std::string itemName;
    float itemPrice = 0;
    short itemQty = 0;
};

class WendingMachine {
public:
    //Getter (Accessor)
    int getCashOnMachine();
    //Setter (Mutator)
    void setCashOnMachine(double cash);
    //Methods
    void processOrder(Item& item, float price, float total, short qty);
    bool verifyOrder(float cashPaidByUser, float itemPrice);
    bool isWorking(std::vector<Item>& items);
private:
    double cashOnMachine = 0;
    float calculateCash(float cash, float price);
};



#endif