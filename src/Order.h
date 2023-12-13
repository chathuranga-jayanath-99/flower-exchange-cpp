#ifndef ORDER_H 
#define ORDER_H

#include <string>

using namespace std;

class Order {
  private:
    string orderID;
    string clientOrderId;
    string instrument;
    int side;
    double price;
    int quantity;

  public:
    Order(const string &orderID, const string &clientOrderIdPtr,
          const string &instrumentPtr, int side, double price, int quantity);
    void printOrder();
    string getOrderID();
    string getClientOrderId();
    string getInstrument();
    int getSide();
    double getPrice();
    int getQuantity();

    void setQuantity(int quantity);
};

#endif
