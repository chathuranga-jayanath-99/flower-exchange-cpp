#include "OrderBook.h"
#include <iostream>
#include <string>

using namespace std;

void BaseOrderBook::processOrder(Order &order) {
  if (order.getSide() == 1) {
    // Processing logic
  }
}