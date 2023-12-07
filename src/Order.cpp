#include <string>
#include "Order.h"

Order::Order(const string& clientOrderIdPtr, const string& instrumentPtr, int side, double price, int quantity) {
    this->clientOrderId = clientOrderIdPtr;
    this->instrument = instrumentPtr;
    this->side = side;
    this->price = price;
    this->quantity = quantity;
}