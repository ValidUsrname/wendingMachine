#include "wendingMachine.hpp"
#include<iostream>
#include<cmath>
using namespace std;
//--------------------------------------------Constructor--------------------------------------------
Item::Item(const string& itemName, float itemPrice, short itemQty) {
    setItemName(itemName);
    setItemPrice(itemPrice);
    setItemQty(itemQty);
}

//--------------------------------------------Getter (Accessor)--------------------------------------
string Item::getItemName() {
    return itemName;
}

short Item::getItemPrice() {
    return itemPrice;
}

short Item::getItemQty() {
    return itemQty;
}

int WendingMachine::getCashOnMachine() {
    return cashOnMachine;
}
//--------------------------------------------Setter (Mutator)---------------------------------------
void Item::setItemName(string itemName) {
    this->itemName = itemName;
}

void Item::setItemPrice(float itemPrice) {
    if (itemPrice < 0)
        throw invalid_argument("itemPrice");
    this->itemPrice = itemPrice;
}

void Item::setItemQty(short itemQty) {
    if (itemQty < 0)
        throw invalid_argument("itemQty");
    this->itemQty = itemQty;
}

void WendingMachine::setCashOnMachine(double cash) {
    if (cash < 0)
        throw invalid_argument("cash");
    else if (cash == 0)
        cout << "Machine is out of money!\n";
    else
        this->cashOnMachine = cash;
}
//--------------------------------------------Methods------------------------------------------------
bool Item::isAvailable() {
    return (getItemQty() > 0) ? true : false;
}

bool WendingMachine::verifyOrder(float cashPaidByUser, float itemPrice) {
    return (cashPaidByUser == itemPrice) ? true : false;
}

void WendingMachine::processOrder(Item& item, float cash, float total, short qty) {
    cout << "Processing order...\n";
    short cashPaidByUser = calculateCash(cash, total);
    if (verifyOrder(cashPaidByUser, total)) {
        cashOnMachine += cashPaidByUser;
        item.setItemQty(item.getItemQty() - qty);
    }
}

float WendingMachine::calculateCash(float userPaidCash, float price) {
    float tempCash;
    if (userPaidCash == price) {
        tempCash += userPaidCash;
    }
    else {
        float change = round(userPaidCash - price);
        cout << "Returning Change Rs." << change << endl;
        tempCash += (userPaidCash - change);
    }
    return round(tempCash);
}

bool WendingMachine::isWorking(vector<Item>& items) {
    for (auto& item : items) {
        if (item.isAvailable())
            return true;
    }
    return false;
}


