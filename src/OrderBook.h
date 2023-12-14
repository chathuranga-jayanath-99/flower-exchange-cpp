#ifndef ORDER_BOOK_H
#define ORDER_BOOK_H

#include "Heap.h"
#include "Order.h"
#include "OrderEntry.h"
#include <iostream>

using namespace std;

class OrderBook {
  public:
    OrderBook(string instrument);
    ~OrderBook();
    void addOrder(const string &clientOrderIdPtr, const string &instrumentPtr,
                  int side, double price, int quantity);
    void modifyOrder(const string &clientOrderIdPtr,
                     const string &instrumentPtr, int side, double price,
                     int quantity);
    void cancelOrder(const string &clientOrderIdPtr,
                     const string &instrumentPtr, int side, double price,
                     int quantity);
    void addBuyOrder(Order &order);
    void addSellOrder(Order &order);
    Order getMaxBuyOrder();
    Order getMinSellOrder();
    void removeMaxBuyOrder();
    void removeMinSellOrder();
    void updateMaxBuyOrderQuantity(int newQuantity);
    void updateMinSellOrderQuantity(int newQuantity);
    bool isBuyersAvailable();
    bool isSellersAvailable();
    void printOrderBook();
    string &getInstrument();
    vector<OrderEntry> processOrder(Order &order);
    void addOrderEntryToVector(vector<OrderEntry> &orderEntries, Order &order,
                               int statusCode, double price, int quantity);

  private:
    MaxHeap *buySide;
    MinHeap *sellSide;
    string instrument;
};

#endif
