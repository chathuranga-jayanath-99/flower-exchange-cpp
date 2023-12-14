#include "OrderBookItem.h"
#include <iostream>

using namespace std;

OrderBookItem::OrderBookItem(string orderId, int qty, double price) {
  this->orderId = orderId;
  this->qty = qty;
  this->price = price;
}

double OrderBookItem::getPrice() {
  return this->price;
}

string OrderBookItem::getOrderId() {
  return this->orderId;
}

int OrderBookItem::getQty() {
  return this->qty;
}

void OrderBookItem::setQty(int newQty) {
  this->qty = newQty;
}
