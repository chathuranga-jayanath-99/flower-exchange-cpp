#include "../Heap.h"
#include "../Order.h"
#include "../OrderBook.h"
#include "../OrderEntry.h"
#include "../enums/Instrument.h"
#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  vector<OrderEntry> completeReport;  
  vector<OrderEntry> orderEntries;  
  OrderBook rob(Instrument::ROSE);
  cout << rob.isBuyersAvailable() << endl;
  
  Order o1("","aa13",Instrument::ROSE,2,55,100);
  
  orderEntries = rob.processOrder(o1);
  for (size_t i = 0; i < orderEntries.size(); i++)
  {
    completeReport.push_back(orderEntries[i]);
  }
  
  cout << "Print Order Book" << endl;
  cout << "==========================" << endl;
  cout << "buy side" << endl;
  cout << "-----------------------------" << endl;
  if (rob.isBuyersAvailable()) {
    while (rob.isBuyersAvailable()) {
      cout << rob.getMaxBuyOrder().getOrderID() << " | " << rob.getMaxBuyOrder().getQuantity() << endl;
      rob.removeMaxBuyOrder();
    }
  } else {
    cout << "empty" << endl;
  }
  cout << endl;
  cout << "sell side" << endl;
  cout << "-----------------------------" << endl;
  if (rob.isSellersAvailable()) {
    while (rob.isSellersAvailable())
    {
      cout << rob.getMinSellOrder().getClientOrderId() << " | " << rob.getMinSellOrder().getPrice() << " | " << rob.getMinSellOrder().getQuantity() << endl;
      rob.removeMinSellOrder();
    }
  } else {
    cout << "empty" << endl;
  }

  cout << endl;
  cout << endl;
  cout << "execution report" << endl;
  cout << "==========================" << endl;
  for (size_t i = 0; i < completeReport.size(); i++)
  {
    completeReport[i].printOrderEntry();
  }
  return 0;
}