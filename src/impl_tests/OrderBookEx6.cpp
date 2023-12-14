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
  RoseOrderBook rob;
  
  Order o1("","aa13","rose",1,55,100);
  Order o2("","aa14","rose",1,65,100);
  Order o3("","aa15","rose",2,1,300);
  Order o4("","aa16","rose",1,2,100);
  
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
  vector<OrderEntry> orderEntries4 = rob.processOrder(o4);
  for (size_t i = 0; i < orderEntries4.size(); i++)
  {
    completeReport.push_back(orderEntries4[i]);
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