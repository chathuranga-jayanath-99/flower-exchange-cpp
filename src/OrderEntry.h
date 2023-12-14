#ifndef ORDER_ENTRY_H
#define ORDER_ENTRY_H

#include "./enums/ExecutionStatus.h"
#include "./enums/Instrument.h"
#include "./enums/Reason.h"
#include <string>

using namespace std;

class OrderEntry {
  private:
    string orderID;
    string clientOrderId;
    string instrument;
    int side;
    string execStatus;
    double price;
    int quantity;
    string reason;
    string timestamp;

  public:
    OrderEntry(const string &orderID, const string &clientOrderId,
               const Instrument &instrument, const int side,
               ExecutionStatus execStatus, double price, int quantity,
               Reason reason);
    OrderEntry(const string &orderID, const string &clientOrderId,
               const string &instrument, const int side, string execStatus,
               double price, int quantity, string reason);
    void printOrderEntry();
    string getOrderID();
    string getClientOrderId();
    string getInstrument();
    int getSide();
    string getExecStatus();
    double getPrice();
    int getQuantity();
    string getReason();
    string getTimestamp();
};

#endif
