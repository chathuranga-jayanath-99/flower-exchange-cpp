#include <string>

using namespace std;

class Order {
private:
  string clientOrderId;
  string instrument;
  int side;
  double price;
  int quantity;

public:
  Order(const string &clientOrderIdPtr, const string &instrumentPtr, int side,
        double price, int quantity);
  void printOrder();
  string getInstrument();
  int getSide();
};
