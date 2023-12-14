#include "OrderBook.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

OrderBook::OrderBook(Instrument instrument) {
    buySide = new MaxHeap();
    sellSide = new MinHeap();
    this->instrument = instrument;
}

OrderBook::~OrderBook() {
    delete buySide;
    delete sellSide;
}

Order OrderBook::getMaxBuyOrder() { return buySide->peek_top(); }

Order OrderBook::getMinSellOrder() { return sellSide->peek_top(); }

void OrderBook::removeMaxBuyOrder() { buySide->pop_top(); }

void OrderBook::removeMinSellOrder() { sellSide->pop_top(); }

void OrderBook::updateMaxBuyOrderQuantity(int newQuantity) {
    buySide->update_top_item_quantity(newQuantity);
}

void OrderBook::updateMinSellOrderQuantity(int newQuantity) {
    sellSide->update_top_item_quantity(newQuantity);
}

bool OrderBook::isBuyersAvailable() { return !(buySide->is_empty()); }

bool OrderBook::isSellersAvailable() { return !(sellSide->is_empty()); }

void OrderBook::addBuyOrder(Order &order) { buySide->insert(order); }

void OrderBook::addSellOrder(Order &order) { sellSide->insert(order); }

void OrderBook::addOrderEntryToVector(vector<OrderEntry> &orderEntries,
                                      Order &order, ExecutionStatus execStatus,
                                      double price, int quantity) {
    OrderEntry *orderEntryPtr = new OrderEntry(
        order.getOrderID(), order.getClientOrderId(), order.getInstrument(),
        order.getSide(), execStatus, price, quantity, Reason::EMPTY);
    orderEntries.push_back(*orderEntryPtr);
}

vector<OrderEntry> OrderBook::processOrder(Order &order) {
    vector<OrderEntry> processedOrderEntries;
    bool orderPartialFilled = false;
    if (order.getSide() == 1) {
        // Processing buy side logic
        while (true) {
            if (OrderBook::isSellersAvailable() == 1) {
                double orderBuyPrice = order.getPrice();
                int orderQty = order.getQuantity();
                Order minSellOrder = OrderBook::getMinSellOrder();
                if (minSellOrder.getPrice() <= orderBuyPrice) {
                    // buy for min sell price
                    // check available quantity
                    if (orderQty == minSellOrder.getQuantity()) {
                        // remove sell order
                        OrderBook::removeMinSellOrder();
                        OrderBook::addOrderEntryToVector(
                            processedOrderEntries, order, ExecutionStatus::FILL,
                            minSellOrder.getPrice(), order.getQuantity());
                        OrderBook::addOrderEntryToVector(
                            processedOrderEntries, minSellOrder, ExecutionStatus::FILL,
                            minSellOrder.getPrice(),
                            minSellOrder.getQuantity());
                        break;
                    } else if (orderQty < minSellOrder.getQuantity()) {
                        OrderBook::updateMinSellOrderQuantity(
                            minSellOrder.getQuantity() - orderQty);
                        OrderBook::addOrderEntryToVector(
                            processedOrderEntries, order, ExecutionStatus::FILL,
                            minSellOrder.getPrice(), order.getQuantity());
                        OrderBook::addOrderEntryToVector(
                            processedOrderEntries, minSellOrder, ExecutionStatus::PFILL,
                            minSellOrder.getPrice(), order.getQuantity());
                        break;
                    } else {
                        // update quantity
                        order.setQuantity(order.getQuantity() -
                                          minSellOrder.getQuantity());
                        OrderBook::removeMinSellOrder();
                        OrderBook::addOrderEntryToVector(
                            processedOrderEntries, order, ExecutionStatus::PFILL,
                            minSellOrder.getPrice(),
                            minSellOrder.getQuantity());
                        OrderBook::addOrderEntryToVector(
                            processedOrderEntries, minSellOrder, ExecutionStatus::FILL,
                            minSellOrder.getPrice(),
                            minSellOrder.getQuantity());
                        orderPartialFilled = true;
                    }
                } else {
                    // Enter order in buy side
                    OrderBook::addBuyOrder(order);
                    if (!orderPartialFilled) {
                        OrderBook::addOrderEntryToVector(
                            processedOrderEntries, order, ExecutionStatus::NEW, order.getPrice(),
                            order.getQuantity());
                    }
                    break;
                }
            } else {
                // Enter order in buy side
                OrderBook::addBuyOrder(order);
                if (!orderPartialFilled) {
                    OrderBook::addOrderEntryToVector(processedOrderEntries,
                                                     order, ExecutionStatus::NEW, order.getPrice(),
                                                     order.getQuantity());
                }
                break;
            }
        }
    } else if (order.getSide() == 2) {
        // Processing sell side logic
        while (true) {
            if (OrderBook::isBuyersAvailable() == 1) {
                double orderSellPrice = order.getPrice();
                int orderSellQuantity = order.getQuantity();
                Order maxBuyOrder = OrderBook::getMaxBuyOrder();
                if (maxBuyOrder.getPrice() >= orderSellPrice) {
                    // sell for maxBuyOrder price
                    // check available quantity
                    if (orderSellQuantity == maxBuyOrder.getQuantity()) {
                        OrderBook::removeMaxBuyOrder();
                        OrderBook::addOrderEntryToVector(
                            processedOrderEntries, order, ExecutionStatus::FILL,
                            maxBuyOrder.getPrice(), order.getQuantity());
                        OrderBook::addOrderEntryToVector(
                            processedOrderEntries, maxBuyOrder, ExecutionStatus::FILL,
                            maxBuyOrder.getPrice(), order.getQuantity());
                        break;
                    } else if (orderSellQuantity < maxBuyOrder.getQuantity()) {
                        OrderBook::updateMaxBuyOrderQuantity(
                            maxBuyOrder.getQuantity() - orderSellQuantity);
                        OrderBook::addOrderEntryToVector(
                            processedOrderEntries, order, ExecutionStatus::FILL,
                            maxBuyOrder.getPrice(), order.getQuantity());
                        OrderBook::addOrderEntryToVector(
                            processedOrderEntries, maxBuyOrder, ExecutionStatus::PFILL,
                            maxBuyOrder.getPrice(), order.getQuantity());
                        break;
                    } else {
                        order.setQuantity(order.getQuantity() -
                                          maxBuyOrder.getQuantity());
                        OrderBook::removeMaxBuyOrder();
                        OrderBook::addOrderEntryToVector(
                            processedOrderEntries, order, ExecutionStatus::PFILL,
                            maxBuyOrder.getPrice(), maxBuyOrder.getQuantity());
                        OrderBook::addOrderEntryToVector(
                            processedOrderEntries, maxBuyOrder, ExecutionStatus::FILL,
                            maxBuyOrder.getPrice(), maxBuyOrder.getQuantity());
                        orderPartialFilled = true;
                    }
                } else {
                    // Enter order in sell side
                    OrderBook::addSellOrder(order);
                    if (!orderPartialFilled) {
                        OrderBook::addOrderEntryToVector(
                            processedOrderEntries, order, ExecutionStatus::NEW, order.getPrice(),
                            order.getQuantity());
                    }
                    break;
                }
            } else {
                // Enter order in sell side
                OrderBook::addSellOrder(order);
                if (!orderPartialFilled) {
                    OrderBook::addOrderEntryToVector(processedOrderEntries,
                                                     order, ExecutionStatus::NEW, order.getPrice(),
                                                     order.getQuantity());
                }
                break;
            }
        }
    } else {
        // Invalid order side
    }
    return processedOrderEntries;
}
