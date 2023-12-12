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

public:
  OrderEntry(const string &orderIDPtr, const string &clientOrderIdPtr,
             const string &instrumentPtr, const int side, int execStatusCode,
             double price, int quantity, int reasonCode);
  void printOrderEntry();
  string getOrderID();
  string getClientOrderId();
  string getInstrument();
  int getSide();
  string getExecStatus();
  double getPrice();
  int getQuantity();
  string getReason();
};
