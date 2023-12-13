#ifndef ORDER_BOOK_ITEM_H
#define ORDER_BOOK_ITEM_H

#include <iostream>

using namespace std;

class OrderBookItem {
    private:
        string orderId;
        int qty;
        double price;
    
    public:
        OrderBookItem(string orderId, int qty, double price);
        double getPrice();
        string getOrderId();
        int getQty();
        void setQty(int newQty);
        bool operator<(const OrderBookItem& orderBookItem) const {
            return price < orderBookItem.price;
        };
        bool operator>(const OrderBookItem& orderBookItem) const {
            return price > orderBookItem.price;
        };
};

#endif