#include "Order.h"
#include <iostream>
#include <string>

Order::Order(const string &orderID, const string &clientOrderId,
             const Instrument &instrument, int side, double price,
             int quantity) {
    this->orderID = orderID;
    this->clientOrderId = clientOrderId;
    this->instrument = instrument;
    this->side = side;
    this->price = price;
    this->quantity = quantity;
}

void Order::printOrder() {
    cout << "Order ID: " << this->orderID << endl;
    cout << "Client Order ID: " << this->clientOrderId << endl;
    cout << "Instrument: " << this->instrument << endl;
    cout << "Side: " << this->side << endl;
    cout << "Price: " << this->price << endl;
    cout << "Quantity: " << this->quantity << endl;
}

string Order::getOrderID() { return this->orderID; };
string Order::getClientOrderId() { return this->clientOrderId; };
Instrument Order::getInstrument() { return this->instrument; };
int Order::getSide() { return this->side; };
double Order::getPrice() { return this->price; };
int Order::getQuantity() { return this->quantity; };

void Order::setQuantity(int quantity) { this->quantity = quantity; };
