#ifndef ORDER_BOOK_H
#define ORDER_BOOK_H

#include "Heap.h"
#include "Order.h"
#include "./enums/Instrument.h"
#include "./enums/ExecutionStatus.h"
#include "OrderEntry.h"
#include <iostream>

using namespace std;

class OrderBook {
  public:
    OrderBook(Instrument instrument);
    ~OrderBook();
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
                               ExecutionStatus execStatus, double price, int quantity);

  private:
    MaxHeap *buySide;
    MinHeap *sellSide;
    Instrument instrument;
};

#endif
