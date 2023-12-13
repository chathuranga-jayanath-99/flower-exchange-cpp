#include "Heap.h"
#include "Order.h"
#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

MaxHeap::MaxHeap(vector<Order> orders) {
    heap = orders;
    make_heap(heap.begin(), heap.end());
};

MaxHeap::MaxHeap() {
    vector<Order> v({});
    heap = v;
    make_heap(heap.begin(), heap.end());
};

void MaxHeap::insert(Order order) {
    heap.push_back(order);
    push_heap(heap.begin(), heap.end());
};

Order MaxHeap::peek_top() {
    return heap[0];
};

Order MaxHeap::pop_top() {
    pop_heap(heap.begin(), heap.end());
    Order top = heap.back();
    heap.pop_back();
    return top;
};

bool MaxHeap::is_empty() {
    return heap.begin() == heap.end();
};

void MaxHeap::update_top_item_quantity(int newQuantity) {
    heap[0].setQuantity(newQuantity);
};

MinHeap::MinHeap(vector<Order> values) {
    heap = values;
    make_heap(heap.begin(), heap.end(), greater<>{});
};

MinHeap::MinHeap() {
    vector<Order> v({});
    heap = v;
    make_heap(heap.begin(), heap.end(), greater<>{});
};

void MinHeap::insert(Order value) {
    heap.push_back(value);
    push_heap(heap.begin(), heap.end(), greater<>{});
};

Order MinHeap::peek_top() {
    return heap[0];
};

Order MinHeap::pop_top() {
    pop_heap(heap.begin(), heap.end(), greater<>{});
    Order top = heap.back();
    heap.pop_back();
    return top;
};

bool MinHeap::is_empty() {
    return heap.begin() == heap.end();
};

void MinHeap::update_top_item_quantity(int newQuantity) {
    heap[0].setQuantity(newQuantity);
}

