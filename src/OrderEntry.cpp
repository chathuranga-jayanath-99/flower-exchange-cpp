#include "OrderEntry.h"
#include <iostream>
#include <string>

using namespace std;

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
  cout << "Order ID: " << orderID << endl;
  cout << "Client Order ID: " << clientOrderId << endl;
  cout << "Instrument: " << instrument << endl;
  cout << "Side: " << side << endl;
  cout << "Exec Status: " << execStatus << endl;
  cout << "Price: " << price << endl;
  cout << "Quantity: " << quantity << endl;
  cout << "Reason: " << reason << endl;
}

string OrderEntry::getOrderID() { return orderID; };
string OrderEntry::getClientOrderId() { return clientOrderId; };
string OrderEntry::getInstrument() { return instrument; };
int OrderEntry::getSide() { return side; };
string OrderEntry::getExecStatus() { return execStatus; };
double OrderEntry::getPrice() { return price; };
int OrderEntry::getQuantity() { return quantity; };
string OrderEntry::getReason() { return reason; };