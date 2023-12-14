#include "../Heap.h"
#include "../Order.h"
#include "../OrderBook.h"
#include "../OrderEntry.h"
#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  vector<OrderEntry> completeReport;  
  OrderBook rob("ROSE");
  
  Order o1("","aa13","rose",2,55,100);
  Order o2("","aa14","rose",2,45,100);
  Order o3("","aa15","rose",1,45,200);
  
  vector<OrderEntry> orderEntries1 = rob.processOrder(o1);
  for (size_t i = 0; i < orderEntries1.size(); i++)
  {
    completeReport.push_back(orderEntries1[i]);
  }
  vector<OrderEntry> orderEntries2 = rob.processOrder(o2);
  for (size_t i = 0; i < orderEntries2.size(); i++)
  {
    completeReport.push_back(orderEntries2[i]);
  }
  vector<OrderEntry> orderEntries3 = rob.processOrder(o3);
  for (size_t i = 0; i < orderEntries3.size(); i++)
  {
    completeReport.push_back(orderEntries3[i]);
  }

  
  
  cout << "Print Order Book" << endl;
  cout << "==========================" << endl;
  cout << "buy side" << endl;
  cout << "-----------------------------" << endl;
  if (rob.isBuyersAvailable()) {
    while (rob.isBuyersAvailable()) {
      cout << rob.getMaxBuyOrder().getClientOrderId() << " | " << rob.getMaxBuyOrder().getPrice() << " | " << rob.getMaxBuyOrder().getQuantity() << endl;
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