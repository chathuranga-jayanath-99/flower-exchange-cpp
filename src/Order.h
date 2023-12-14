#ifndef ORDER_H 
#define ORDER_H

#include "./enums/Instrument.h"
#include <string>

using namespace std;

class Order {
  private:
    string orderID;
    string clientOrderId;
    Instrument instrument;
    int side;
    double price;
    int quantity;

  public:
    Order(const string &orderID, const string &clientOrderIdPtr,
          const Instrument &instrumentPtr, int side, double price, int quantity);
    void printOrder();
    string getOrderID();
    string getClientOrderId();
    Instrument getInstrument();
    int getSide();
    double getPrice();
    int getQuantity();

    void setQuantity(int quantity);

    inline bool operator<(const Order& order) const {
      return price < order.price;
    };
    inline bool operator>(const Order& order) const {
      return price > order.price;
    };
};

#endif
