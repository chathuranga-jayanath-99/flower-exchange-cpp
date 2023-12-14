#include "Utils.h"
#include "OrderEntry.h"
#include <iostream>
#include <string>

using namespace std;

OrderEntry::OrderEntry(const string &orderID, const string &clientOrderId,
                       const Instrument &instrument, int side,
                       ExecutionStatus execStatus, double price, int quantity,
                       Reason reason) {
  this->orderID = orderID;
  this->clientOrderId = clientOrderId;
  this->side = side;
  this->price = price;
  this->quantity = quantity;
  this->instrument = Utils::getStrFromInstrument(instrument);
  this->execStatus = Utils::getStrFromExecutionStatus(execStatus);
  this->reason = Utils::getStrFromReason(reason);
};

OrderEntry::OrderEntry(const string &orderID, const string &clientOrderId,
                      const string &instrument, const int side, string execStatus,
                      double price, int quantity, string reason) {
  this->orderID = orderID;
  this->clientOrderId = clientOrderId;
  this->side = side;
  this->price = price;
  this->quantity = quantity;
  this->instrument = instrument; 
  this->execStatus = execStatus;
  this->reason = reason;
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
}

string OrderEntry::getOrderID() { return orderID; };
string OrderEntry::getClientOrderId() { return clientOrderId; };
string OrderEntry::getInstrument() { return instrument; };
int OrderEntry::getSide() { return side; };
string OrderEntry::getExecStatus() { return execStatus; };
double OrderEntry::getPrice() { return price; };
int OrderEntry::getQuantity() { return quantity; };
string OrderEntry::getReason() { return reason; };