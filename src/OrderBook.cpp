#include "OrderBook.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

BaseOrderBook::BaseOrderBook() {
  MaxHeap buyHeap();
  MinHeap sellHeap();
  buySide = &buyHeap;
  sellSide = &sellHeap;
}

OrderBookItem BaseOrderBook::getMaxBuyOrderItem() {
  return buySide.peek_top();
}

OrderBookItem BaseOrderBook::getMinSellOrderItem() {
  return sellSide.peek_top();
}

void BaseOrderBook::removeMaxBuyOrderItem(){
  buySide.pop_top();
}

void BaseOrderBook::removeMinSellOrderItem(){
  sellSide.pop_top();
}

void updateMaxBuyOrderItemQuantity() {

}

void updateMinSellOrderItemQuantity() {

}

bool BaseOrderBook::isBuyersAvailable() {
  return buySide.is_empty();
}

bool BaseOrderBook::isSellersAvailable() {
  return sellSide.is_empty();
}

void BaseOrderBook::addBuyOrder(Order &order) {
  // OrderBookItem orderBookItem(order.getId(), order.getQty(), order.getPrice());
  OrderBookItem orderBookItem("s1", 100, 100.0);
  buySide.insert(orderBookItem);
}

void BaseOrderBook::addSellOrder(Order &order) {
  // OrderBookItem orderBookItem(order.getId(), order.getQty(), order.getPrice());
  OrderBookItem orderBookItem("s2", 100, 50.0);
  sellSide.insert(orderBookItem);
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
    if (BaseOrderBook::isSellersAvailable() === 1) {
      double orderBuyPrice = order.getPrice();
      int orderQty = order.getQuantity();
      OrderBookItem minSellOrderItem = BaseOrderBook::getMinSellOrderItem();
      if (minSellOrderItem.getPrice() <= orderBuyPrice) {
        // buy for min sell price
        // check available quantity
        if (orderQty == minSellOrderItem.getQty()) {
          // remove sell order
          BaseOrderBook::removeMinSellOrderItem();
        } 
        else if (orderQty < minSellOrderItem.getQty()) {
          BaseOrderBook::updateMinSellOrderItemQuantity(minSellOrderItem.getQty() - orderQty);
        } 
        else {
          // update quantity
          // order.setQuantity(order.getQuantity() - minSellOrderItem.getQty());
          BaseOrderBook::removeMinSellOrderItem();
        }
      } else {
        // Enter order in buy side 
        BaseOrderBook::addBuyOrder(order);
      }
    } else {
      // Enter order in buy side 
      BaseOrderBook::addBuyOrder(order);
    }
  } else if (order.getSide == 2) {
    // Processing sell side logic
    if (BaseOrderBook::isBuyersAvailable() === 1) {
      double orderSellPrice = order.getPrice();
      int orderSellQuantity = order.getQuantity();
      OrderBookItem maxBuyOrderItem = BaseOrderBook::getMaxBuyOrderItem();
      if (maxBuyOrderItem.getPrice() >= orderSellPrice) {
        // sell for maxBuyOrderItem price 
        // check available quantity
        if (orderSellQuantity == maxBuyOrderItem.getQty()) {
          BaseOrderBook::removeMaxBuyOrderItem();
        } else if (orderSellQuantity < maxBuyOrderItem.getQty()) {
          BaseOrderBook::updateMaxBuyOrderItemQuantity(maxBuyOrderItem.getQty() - orderSellQuantity);
        } else {
          // order.setQuantity(order.getQuantity() - maxBuyOrderItem.getQtty());
          BaseOrderBook::removeMaxBuyOrderItem();
        }
      } else {
        // Enter order in sell side 
        BaseOrderBook::addSellOrder(order);
      }
    } else {
      // Enter order in sell side 
      BaseOrderBook::addSellOrder(order);
    }
  } else {
    // Invalid order side
  }
}
