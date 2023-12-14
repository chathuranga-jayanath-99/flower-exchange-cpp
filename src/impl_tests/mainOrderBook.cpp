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
  vector<OrderEntry> orderEntries;  
  RoseOrderBook rob;
  cout << rob.isBuyersAvailable() << endl;
  
  // 2 sell orders followed with buy
  // Order o1("a1","c1","rose",2,55,100);
  // Order o2("a2","c2","rose",2,45,150);
  // Order o3("a3","c3","rose",1,45,150);

  // 2 sell, 1 buy
  // Order o1("a1","c1","rose",2,55,100);
  // Order o2("a2","c2","rose",2,45,150);
  // Order o3("a3","c3","rose",1,70,200);

  // 2 buy, 1 sell
  Order o1("a1","c1","rose",1,55,100);
  Order o2("a2","c2","rose",1,45,150);
  Order o3("a3","c3","rose",2,45,200);
  
  orderEntries = rob.processOrder(o1);
  for (size_t i = 0; i < orderEntries.size(); i++)
  {
    completeReport.push_back(orderEntries[i]);
  }
  
  orderEntries = rob.processOrder(o2);
  for (size_t i = 0; i < orderEntries.size(); i++)
  {
    completeReport.push_back(orderEntries[i]);
  }
  orderEntries = rob.processOrder(o3);
  for (size_t i = 0; i < orderEntries.size(); i++)
  {
    completeReport.push_back(orderEntries[i]);
  }

  cout << "Print Order Book" << endl;
  cout << "==========================" << endl;
  cout << "buy side" << endl;
  if (rob.isBuyersAvailable()) {
    cout << rob.getMaxBuyOrder().getOrderID() << " | " << rob.getMaxBuyOrder().getQuantity() << endl;
  } else {
    cout << "empty" << endl;
  }

  cout << "sell side" << endl;
  if (rob.isSellersAvailable()) {
    cout << rob.getMinSellOrder().getOrderID() << " | " << rob.getMinSellOrder().getQuantity() << endl;
  } else {
    cout << "empty" << endl;
  }

  cout << endl;
  cout << endl;
  cout << "execution report";
  cout << "==========================" << endl;
  for (size_t i = 0; i < completeReport.size(); i++)
  {
    completeReport[i].printOrderEntry();
  }
  return 0;
}