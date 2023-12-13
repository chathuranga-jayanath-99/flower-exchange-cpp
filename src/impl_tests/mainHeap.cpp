#include "../Heap.cpp"
#include <iostream>
#include <vector>

using namespace std;

int main() {
  vector<OrderBookItem> v;
  
  OrderBookItem o1("a1", 100, 50);
  OrderBookItem o2("a2", 100, 50);
  OrderBookItem o3("a3", 100, 50);

  MaxHeap m;
  m.insert(o1);
  m.insert(o2);
  m.insert(o3);

  OrderBookItem pt = m.peek_top();
  cout << pt.getOrderId() << endl;
  cout << pt.getQty() << endl;

  m.update_top_item_quantity(200);
  pt = m.peek_top();
  cout << pt.getOrderId() << endl;
  cout << pt.getQty() << endl;

  // pt = m.pop_top();
  // pt = m.peek_top();
  // cout << pt.getOrderId() << endl;

  // pt = m.pop_top();
  // cout << pt.getOrderId() << endl;
  return 0;
}