#ifndef ORDER_BOOK_H 
#define ORDER_BOOK_H

#include "Heap.h"
#include "Order.h"
#include <iostream>

using namespace std;

class BaseOrderBook {
  public:
    BaseOrderBook();
    void addOrder(const string &clientOrderIdPtr, const string &instrumentPtr,
                  int side, double price, int quantity);
    void modifyOrder(const string &clientOrderIdPtr, const string &instrumentPtr,
                    int side, double price, int quantity);
    void cancelOrder(const string &clientOrderIdPtr, const string &instrumentPtr,
                    int side, double price, int quantity);
    void addBuyOrder(Order &order);
    void addSellOrder(Order &order);
    OrderBookItem getMaxBuyOrderItem();
    OrderBookItem getMinSellOrderItem();
    void removeMaxBuyOrderItem();
    void removeMinSellOrderItem();
    void updateMaxBuyOrderItemQuantity(int newQuantity);
    void updateMinSellOrderItemQuantity(int newQuantity);
    bool isBuyersAvailable();
    bool isSellersAvailable();
    void printOrderBook();
    string &getInstrument();
    void processOrder(Order &order);
  
  private:
    MaxHeap* buySide;
    MinHeap* sellSide;
};

class RoseOrderBook : public BaseOrderBook {
  public:
    RoseOrderBook();
};

class LavenderOrderBook : public BaseOrderBook {
  public:
    LavenderOrderBook();
};

class LotusOrderBook : public BaseOrderBook {
  public:
    LotusOrderBook();
};

class TulipOrderBook : public BaseOrderBook {
  public:
    TulipOrderBook();
};

class OrchidOrderBook : public BaseOrderBook {
  public:
    OrchidOrderBook();
};

#endif
