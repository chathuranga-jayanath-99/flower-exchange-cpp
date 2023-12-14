#include "OrderEntry.h"
#include <chrono>
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

std::string getCurrentTimestamp() {
    auto now = std::chrono::system_clock::now();
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);

    std::tm localTime = *std::localtime(&currentTime);

    auto us = std::chrono::duration_cast<std::chrono::microseconds>(
                  now.time_since_epoch()) %
              1000000;

    std::ostringstream oss;
    oss << std::put_time(&localTime, "%Y%m%d-%H%M%S") << '.'
        << std::setfill('0') << std::setw(6) << us.count();
    return oss.str();
}

OrderEntry::OrderEntry(const string &orderIDPtr, const string &clientOrderIdPtr,
                       const string &instrumentPtr, int side,
                       int execStatusCode, double price, int quantity,
                       int reasonCode) {
    orderID = orderIDPtr;
    clientOrderId = clientOrderIdPtr;
    instrument = instrumentPtr;
    this->side = side;
    this->price = price;
    this->quantity = quantity;
    this->timestamp = getCurrentTimestamp();

    switch (execStatusCode) {
    case 0:
        execStatus = "New";
        break;
    case 1:
        execStatus = "Rejected";
        break;
    case 2:
        execStatus = "Fill";
        break;
    case 3:
        execStatus = "Pfill";
        break;
    }

    switch (reasonCode) {
    case 0:
        reason = "Invalid instrument";
        break;
    case 1:
        reason = "Invalid side";
        break;
    case 2:
        reason = "Invalid price";
        break;
    case 3:
        reason = "Invalid size";
        break;
    }
};

void OrderEntry::printOrderEntry() {
    cout << "Order ID: " << orderID << "| ";
    cout << "Client Order ID: " << clientOrderId << "| ";
    cout << "Instrument: " << instrument << "| ";
    cout << "Side: " << side << "| ";
    cout << "Exec Status: " << execStatus << "| ";
    cout << "Price: " << price << "| ";
    cout << "Quantity: " << quantity << "| ";
    cout << "Reason: " << reason << endl;
    cout << "Timestamp: " << timestamp << endl;
}

string OrderEntry::getOrderID() { return orderID; };
string OrderEntry::getClientOrderId() { return clientOrderId; };
string OrderEntry::getInstrument() { return instrument; };
int OrderEntry::getSide() { return side; };
string OrderEntry::getExecStatus() { return execStatus; };
double OrderEntry::getPrice() { return price; };
int OrderEntry::getQuantity() { return quantity; };
string OrderEntry::getReason() { return reason; };
string OrderEntry::getTimestamp() { return timestamp; };