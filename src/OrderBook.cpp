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

OrderBookItem BaseOrderBook::getMaxBuyOrderItem() {
  return buySide->peek_top();
}

OrderBookItem BaseOrderBook::getMinSellOrderItem() {
  return sellSide->peek_top();
}

void BaseOrderBook::removeMaxBuyOrderItem(){
  buySide->pop_top();
}

void BaseOrderBook::removeMinSellOrderItem(){
  sellSide->pop_top();
}

void BaseOrderBook::updateMaxBuyOrderItemQuantity(int newQuantity) {
  buySide->update_top_item_quantity(newQuantity);
}

void BaseOrderBook::updateMinSellOrderItemQuantity(int newQuantity) {
  sellSide->update_top_item_quantity(newQuantity);
}

bool BaseOrderBook::isBuyersAvailable() {
  return !(buySide->is_empty());
}

bool BaseOrderBook::isSellersAvailable() {
  return !(sellSide->is_empty());
}

void BaseOrderBook::addBuyOrder(Order &order) {
  OrderBookItem orderBookItem(order.getOrderID(), order.getQuantity(), order.getPrice());
  buySide->insert(orderBookItem);
}

void BaseOrderBook::addSellOrder(Order &order) {
  OrderBookItem orderBookItem(order.getOrderID(), order.getQuantity(), order.getPrice());
  sellSide->insert(orderBookItem);
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
            order.setQuantity(order.getQuantity() - minSellOrderItem.getQty());
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
    }
  } else if (order.getSide() == 2) {
    // Processing sell side logic
    while (true)
    {
      if (BaseOrderBook::isBuyersAvailable() == 1) {
        double orderSellPrice = order.getPrice();
        int orderSellQuantity = order.getQuantity();
        OrderBookItem maxBuyOrderItem = BaseOrderBook::getMaxBuyOrderItem();
        if (maxBuyOrderItem.getPrice() >= orderSellPrice) {
          // sell for maxBuyOrderItem price 
          // check available quantity
          if (orderSellQuantity == maxBuyOrderItem.getQty()) {
            BaseOrderBook::removeMaxBuyOrderItem();
            break;
          } else if (orderSellQuantity < maxBuyOrderItem.getQty()) {
            BaseOrderBook::updateMaxBuyOrderItemQuantity(maxBuyOrderItem.getQty() - orderSellQuantity);
            break;
          } else {
            order.setQuantity(order.getQuantity() - maxBuyOrderItem.getQty());
            BaseOrderBook::removeMaxBuyOrderItem();
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
