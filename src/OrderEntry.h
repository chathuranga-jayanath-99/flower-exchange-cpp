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
    string side;
    string execStatus;
    string price;
    string quantity;
    string reason;
    string timestamp;

  public:
    OrderEntry(const string &orderID, const string &clientOrderId,
               const string &instrument, const string side, string execStatus,
               string price, string quantity, string reason);
    void printOrderEntry();
    string getOrderID();
    string getClientOrderId();
    string getInstrument();
    string getSide();
    string getExecStatus();
    string getPrice();
    string getQuantity();
    string getReason();
    string getTimestamp();
};

#endif
