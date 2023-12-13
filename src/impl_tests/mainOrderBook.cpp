#include "../Heap.h"
#include "../Order.h"
#include "../OrderBook.h"
#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  cout << "statr main order book" << endl;
  RoseOrderBook rob;
  cout << rob.isBuyersAvailable() << endl;
  
  cout << "define orders" << endl;
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

  cout << "add orders to order book" << endl;
  rob.processOrder(o1);
  rob.processOrder(o2);
  rob.processOrder(o3);

  cout << "after buy" << endl;
  cout << "buy side" << endl;
  cout << rob.getMaxBuyOrder().getOrderID() << " | " << rob.getMaxBuyOrder().getQuantity() << endl;

  cout << "sell side" << endl;
  cout << rob.getMinSellOrder().getOrderID() << " | " << rob.getMinSellOrder().getQuantity() << endl;
  
  return 0;
}