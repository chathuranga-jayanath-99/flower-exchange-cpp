#include "Heap.h"
#include "Order.h"
#include <iostream>

using namespace std;

class BaseOrderBook {
public:
  BaseOrderBook(const string &instrumentPtr);
  void addOrder(const string &clientOrderIdPtr, const string &instrumentPtr,
                int side, double price, int quantity);
  void modifyOrder(const string &clientOrderIdPtr, const string &instrumentPtr,
                   int side, double price, int quantity);
  void cancelOrder(const string &clientOrderIdPtr, const string &instrumentPtr,
                   int side, double price, int quantity);
  void printOrderBook();
  string &getInstrument();
  void processOrder(Order &order);

private:
  string instrument;
  MaxHeap *buySide;
  MinHeap *sellSide;
};