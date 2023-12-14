#include "OrderBook.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

BaseOrderBook::BaseOrderBook() {
  buySide = new MaxHeap();
  sellSide = new MinHeap();
}

BaseOrderBook::~BaseOrderBook() {
  delete buySide;
  delete sellSide;
}

Order BaseOrderBook::getMaxBuyOrder() {
  return buySide->peek_top();
}

Order BaseOrderBook::getMinSellOrder() {
  return sellSide->peek_top();
}

void BaseOrderBook::removeMaxBuyOrder(){
  buySide->pop_top();
}

void BaseOrderBook::removeMinSellOrder(){
  sellSide->pop_top();
}

void BaseOrderBook::updateMaxBuyOrderQuantity(int newQuantity) {
  buySide->update_top_item_quantity(newQuantity);
}

void BaseOrderBook::updateMinSellOrderQuantity(int newQuantity) {
  sellSide->update_top_item_quantity(newQuantity);
}

bool BaseOrderBook::isBuyersAvailable() {
  return !(buySide->is_empty());
}

bool BaseOrderBook::isSellersAvailable() {
  return !(sellSide->is_empty());
}

void BaseOrderBook::addBuyOrder(Order &order) {
  buySide->insert(order);
}

void BaseOrderBook::addSellOrder(Order &order) {
  sellSide->insert(order);
}

RoseOrderBook::RoseOrderBook() : BaseOrderBook() {
  
}

LavenderOrderBook::LavenderOrderBook() : BaseOrderBook() {
  
}

LotusOrderBook::LotusOrderBook() : BaseOrderBook() {
    
}

TulipOrderBook::TulipOrderBook() : BaseOrderBook() {
    
}

OrchidOrderBook::OrchidOrderBook() : BaseOrderBook() {
    
}

void BaseOrderBook::addOrderEntryToVector(vector<OrderEntry> &orderEntries, Order &order, int statusCode, double price, int quantity) {
  OrderEntry* orderEntryPtr = new OrderEntry(
    order.getOrderID(),
    order.getClientOrderId(),
    order.getInstrument(),
    order.getSide(),
    statusCode,
    price,
    quantity,
    -1
  );
  orderEntries.push_back(*orderEntryPtr);
}

vector<OrderEntry> BaseOrderBook::processOrder(Order &order) {
  vector<OrderEntry> processedOrderEntries;
  bool orderPartialFilled = false;
  if (order.getSide() == 1) {
    // Processing buy side logic
    while (true)
    {
      if (BaseOrderBook::isSellersAvailable() == 1) {
        double orderBuyPrice = order.getPrice();
        int orderQty = order.getQuantity();
        Order minSellOrder = BaseOrderBook::getMinSellOrder();
        if (minSellOrder.getPrice() <= orderBuyPrice) {
          // buy for min sell price
          // check available quantity
          if (orderQty == minSellOrder.getQuantity()) {
            // remove sell order
            BaseOrderBook::removeMinSellOrder();
            BaseOrderBook::addOrderEntryToVector(processedOrderEntries, order, 2, minSellOrder.getPrice(), order.getQuantity());
            BaseOrderBook::addOrderEntryToVector(processedOrderEntries, minSellOrder, 2, minSellOrder.getPrice(), minSellOrder.getQuantity());
            break;
          } 
          else if (orderQty < minSellOrder.getQuantity()) {
            BaseOrderBook::updateMinSellOrderQuantity(minSellOrder.getQuantity() - orderQty);
            BaseOrderBook::addOrderEntryToVector(processedOrderEntries, order, 2, minSellOrder.getPrice(), order.getQuantity());
            BaseOrderBook::addOrderEntryToVector(processedOrderEntries, minSellOrder, 3, minSellOrder.getPrice(), order.getQuantity());
            break;
          } 
          else {
            // update quantity
            order.setQuantity(order.getQuantity() - minSellOrder.getQuantity());
            BaseOrderBook::removeMinSellOrder();
            BaseOrderBook::addOrderEntryToVector(processedOrderEntries, order, 3, minSellOrder.getPrice(), minSellOrder.getQuantity());
            BaseOrderBook::addOrderEntryToVector(processedOrderEntries, minSellOrder, 2, minSellOrder.getPrice(), minSellOrder.getQuantity());
            orderPartialFilled = true;
          }
        } else {
          // Enter order in buy side 
          BaseOrderBook::addBuyOrder(order);
          if (!orderPartialFilled) {
            BaseOrderBook::addOrderEntryToVector(processedOrderEntries, order, 0, order.getPrice(), order.getQuantity());
          }
          break;
        }
      } else {
        // Enter order in buy side 
        BaseOrderBook::addBuyOrder(order);
        if (!orderPartialFilled) {
          BaseOrderBook::addOrderEntryToVector(processedOrderEntries, order, 0, order.getPrice(), order.getQuantity());
        }
        break;
      }
    }
  } else if (order.getSide() == 2) {
    // Processing sell side logic
    while (true)
    {
      if (BaseOrderBook::isBuyersAvailable() == 1) {
        double orderSellPrice = order.getPrice();
        int orderSellQuantity = order.getQuantity();
        Order maxBuyOrder = BaseOrderBook::getMaxBuyOrder();
        if (maxBuyOrder.getPrice() >= orderSellPrice) {
          // sell for maxBuyOrder price 
          // check available quantity
          if (orderSellQuantity == maxBuyOrder.getQuantity()) {
            BaseOrderBook::removeMaxBuyOrder();
            BaseOrderBook::addOrderEntryToVector(processedOrderEntries, order, 2, maxBuyOrder.getPrice(), order.getQuantity());
            BaseOrderBook::addOrderEntryToVector(processedOrderEntries, maxBuyOrder, 2, maxBuyOrder.getPrice(), order.getQuantity());
            break;
          } else if (orderSellQuantity < maxBuyOrder.getQuantity()) {
            BaseOrderBook::updateMaxBuyOrderQuantity(maxBuyOrder.getQuantity() - orderSellQuantity);
            BaseOrderBook::addOrderEntryToVector(processedOrderEntries, order, 2, maxBuyOrder.getPrice(), order.getQuantity());
            BaseOrderBook::addOrderEntryToVector(processedOrderEntries, maxBuyOrder, 3, maxBuyOrder.getPrice(), order.getQuantity());
            break;
          } else {
            order.setQuantity(order.getQuantity() - maxBuyOrder.getQuantity());
            BaseOrderBook::removeMaxBuyOrder();
            BaseOrderBook::addOrderEntryToVector(processedOrderEntries, order, 3, maxBuyOrder.getPrice(), maxBuyOrder.getQuantity());
            BaseOrderBook::addOrderEntryToVector(processedOrderEntries, maxBuyOrder, 2, maxBuyOrder.getPrice(), maxBuyOrder.getQuantity());
            orderPartialFilled = true;
          }
        } else {
          // Enter order in sell side 
          BaseOrderBook::addSellOrder(order);
          if (!orderPartialFilled) {
            BaseOrderBook::addOrderEntryToVector(processedOrderEntries, order, 0, order.getPrice(), order.getQuantity());
          }
          break;
        }
      } else {
        // Enter order in sell side 
        BaseOrderBook::addSellOrder(order);
        if (!orderPartialFilled) {
          BaseOrderBook::addOrderEntryToVector(processedOrderEntries, order, 0, order.getPrice(), order.getQuantity());
        }
        break;
      }
    }
  } else {
    // Invalid order side
  }
  return processedOrderEntries;
}
