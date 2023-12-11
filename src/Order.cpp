#include "Order.h"
#include <iostream>
#include <string>

Order::Order(const string &clientOrderIdPtr, const string &instrumentPtr,
             int side, double price, int quantity) {
  this->clientOrderId = clientOrderIdPtr;
  this->instrument = instrumentPtr;
  this->side = side;
  this->price = price;
  this->quantity = quantity;
}

void Order::printOrder() {
  cout << "Client Order ID: " << this->clientOrderId << endl;
  cout << "Instrument: " << this->instrument << endl;
  cout << "Side: " << this->side << endl;
  cout << "Price: " << this->price << endl;
  cout << "Quantity: " << this->quantity << endl;
}

string Order::getInstrument() { return this->instrument; };
int Order::getSide() { return this->side; };
