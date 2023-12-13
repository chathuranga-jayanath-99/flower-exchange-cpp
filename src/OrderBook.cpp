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

void BaseOrderBook::processOrder(Order &order) {
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
            break;
          } 
          else if (orderQty < minSellOrder.getQuantity()) {
            BaseOrderBook::updateMinSellOrderQuantity(minSellOrder.getQuantity() - orderQty);
            break;
          } 
          else {
            // update quantity
            order.setQuantity(order.getQuantity() - minSellOrder.getQuantity());
            BaseOrderBook::removeMinSellOrder();
          }
        } else {
          // Enter order in buy side 
          BaseOrderBook::addBuyOrder(order);
          break;
        }
      } else {
        // Enter order in buy side 
        BaseOrderBook::addBuyOrder(order);
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
        Order maxBuyOrderItem = BaseOrderBook::getMaxBuyOrder();
        if (maxBuyOrderItem.getPrice() >= orderSellPrice) {
          // sell for maxBuyOrderItem price 
          // check available quantity
          if (orderSellQuantity == maxBuyOrderItem.getQuantity()) {
            BaseOrderBook::removeMaxBuyOrder();
            break;
          } else if (orderSellQuantity < maxBuyOrderItem.getQuantity()) {
            BaseOrderBook::updateMaxBuyOrderQuantity(maxBuyOrderItem.getQuantity() - orderSellQuantity);
            break;
          } else {
            order.setQuantity(order.getQuantity() - maxBuyOrderItem.getQuantity());
            BaseOrderBook::removeMaxBuyOrder();
          }
        } else {
          // Enter order in sell side 
          BaseOrderBook::addSellOrder(order);
          break;
        }
      } else {
        // Enter order in sell side 
        BaseOrderBook::addSellOrder(order);
        break;
      }
    }
    
    
  } else {
    // Invalid order side
  }
}
