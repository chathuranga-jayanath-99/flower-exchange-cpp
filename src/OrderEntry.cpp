#include "OrderEntry.h"
#include "Utils.h"
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

OrderEntry::OrderEntry(const string &orderID, const string &clientOrderId,
                       const string &instrument, const string side,
                       string execStatus, string price, string quantity,
                       string reason) {
    this->orderID = orderID;
    this->clientOrderId = clientOrderId;
    this->side = side;
    this->price = price;
    this->quantity = quantity;
    this->instrument = instrument;
    this->execStatus = execStatus;
    this->reason = reason;
    this->timestamp = getCurrentTimestamp();
};

void OrderEntry::printOrderEntry() {
    cout << "Order ID: " << orderID << "| ";
    cout << "Client Order ID: " << clientOrderId << "| ";
    cout << "Instrument: " << instrument << "| ";
    cout << "Side: " << side << "| ";
    cout << "Exec Status: " << execStatus << "| ";
    cout << "Price: " << price << "| ";
    cout << "Quantity: " << quantity << " | ";
    cout << "Reason: " << reason << endl;
    cout << "Timestamp: " << timestamp << endl;
}

string OrderEntry::getOrderID() { return orderID; };
string OrderEntry::getClientOrderId() { return clientOrderId; };
string OrderEntry::getInstrument() { return instrument; };
string OrderEntry::getSide() { return side; };
string OrderEntry::getExecStatus() { return execStatus; };
string OrderEntry::getPrice() { return price; };
string OrderEntry::getQuantity() { return quantity; };
string OrderEntry::getReason() { return reason; };
string OrderEntry::getTimestamp() { return timestamp; };