#include"wendingMachine.hpp"
#include<iostream>
#include<vector>
#include<limits>
#include<cmath>

using namespace std;

void showItems(vector<Item>& items) {
    short index = 1;
    for (auto& item : items) {
        string itemAvailability = (item.isAvailable()) ? "" : "(unavailable)";
        cout << index << ". "
            << item.getItemName() << " @ Rs."
            << item.getItemPrice() << " qty - "
            << item.getItemQty() << " "
            << itemAvailability << endl;
        index++;
    }
}

short selectItem(short range) {

    short userInput;
    string error = "Please select a valid option!!!\n";

    cout << "Select: ";
    cin >> userInput;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (cin.fail()) {
        cerr << error;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return -1;
    }
    else if (userInput <= 0 || userInput > range) {
        cerr << error;
        return -1;
    }
    return userInput;

}

bool userQtyValidation(short itemQty) {
    return (itemQty < 0);
}

short selectItemQty(string itemName, short itemQty) {
    short qty;
    string error = "Negative quantity error.\n";
    do
    {
        cout << "Enter qty: ";
        cin >> qty;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (cin.fail()) {
            cerr << "Please enter a valid input.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        else if (userQtyValidation(qty)) {
            cerr << error;
            qty = 0;
            continue;
        }
        else if (qty == 0) {
            cerr << "Please enter a number greater than 0.\n";
            continue;
        }
        else if (qty > itemQty)
            cout << "Only " << itemQty << " " << itemName << " available\n"
            << "Please Select quantity less than  or equal to " << itemQty << endl;
        else
            break;
    } while (true);
    return qty;
}

bool orderConfirmation() {
    char userconfirm;
    string error = "Enter valid input\n";

    do {
        cout << "Press [y] to confirm or [n] to cancel: ";
        cin >> userconfirm;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (tolower(userconfirm) == 'y' || tolower(userconfirm) == 'n') {
            if (tolower(userconfirm) == 'n') {
                cerr << "Order Cancelled!!!\n";
                return false;
            }
            else
                return true;
        }
        else {
            cerr << error;
            continue;
        }

    } while (true);
}

bool userCashValidation(float userPaidCash) {
    return (userPaidCash < 0);
}

float takeCash(float price) {
    float userPaidCash = 0;
    float tempCash = 0;
    do {
        cout << "Insert Cash: ";
        cin >> tempCash;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (cin.fail()) {
            cout << "Please enter valid amout!!\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        else if (userCashValidation(tempCash)) {
            cerr << "Negative Cash input Error!\n"
                << "Please provide valid input\n";
            tempCash = 0;
            continue;
        }
        userPaidCash += tempCash;
        if (userPaidCash < price) {
            float difference = round(price - userPaidCash);
            cout << "Insufficient amount!!!\n"
                << "You need Rs." << difference << " more to complete the order." << endl;
        }
        else
            break;
    } while (true);
    return userPaidCash;
}

int main() {
    WendingMachine machine;

    //List of items
    vector<Item> items{
        {"Candy", 5, 1},
        {"Chips", 10, 10},
        {"Cola", 15, 0},
    };

    while (machine.isWorking(items)) {

        showItems(items);

        short user = selectItem(items.capacity());

        if (user == -1)
            continue;

        Item& item = items[user - 1];

        if (!item.isAvailable()) {
            cout << "Sorry " << item.getItemName() << " is unavailable at the moment.\n";
            continue;
        }

        cout << "You selected " << item.getItemName() << endl
            << "How much do you want?\n";

        short qty = selectItemQty(item.getItemName(), item.getItemQty());
        float total = item.getItemPrice() * qty;

        cout << "---Bill---\n"
            << qty << " " << item.getItemName()
            << " @ Rs." << item.getItemPrice() << endl
            << "Your Total is Rs." << total << endl;

        if (!orderConfirmation())
            continue;
        float cash = takeCash(total);

        machine.processOrder(item, cash, total, qty);

        cout << "Cash on Machine Rs." << machine.getCashOnMachine() << endl;
    }

    cout << "The machine is out of order!!!\n";

    return 0;
}