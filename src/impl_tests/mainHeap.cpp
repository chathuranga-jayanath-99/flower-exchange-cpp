#include "../Heap.h"
#include "../Order.h"
#include <iostream>
#include <vector>

using namespace std;

int main() {
  vector<Order> v;
  
  Order o1("a1","c1","rose",2,55,100);
  Order o2("a2","c2","rose",2,45,150);
  Order o3("a3","c3","rose",1,70,200);

  MaxHeap m;
  m.insert(o1);
  m.insert(o2);
  m.insert(o3);

  Order pt = m.peek_top();
  cout << pt.getOrderID() << endl;
  cout << pt.getQuantity() << endl;

  m.update_top_item_quantity(500);
  pt = m.peek_top();
  cout << pt.getOrderID() << endl;
  cout << pt.getQuantity() << endl;

  pt = m.pop_top();
  pt = m.peek_top();
  cout << pt.getOrderID() << endl;

  // pt = m.pop_top();
  // cout << pt.getOrderId() << endl;
  return 0;
}