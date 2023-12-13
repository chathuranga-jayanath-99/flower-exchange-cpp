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
  cout << rob.isBuyersAvailable() << endl;
  cout << rob.isBuyersAvailable() << endl;
  
  // cout << "define orders" << endl;
  // Order o1("a1","c1","rose",2,55,100);
  // Order o2("a2","c2","rose",2,45,150);

  // cout << "add orders to order book" << endl;
  // rob.addSellOrder(o1);
  // rob.addSellOrder(o2);

  // cout << "check orders" << endl;
  // cout << rob.getMinSellOrderItem().getOrderId() << endl;

  return 0;
}