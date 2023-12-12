#include <algorithm>
#include <vector>
#include <iostream>
#include "Heap.h"

using namespace std;

MaxHeap::MaxHeap(vector<OrderBookItem> orderBookItems) {
    heap = orderBookItems;
    make_heap(heap.begin(), heap.end());
};

MaxHeap::MaxHeap() {
    vector<OrderBookItem> v({});
    heap = v;
    make_heap(heap.begin(), heap.end());
};

void MaxHeap::insert(OrderBookItem orderBookItem) {
    heap.push_back(orderBookItem);
    push_heap(heap.begin(), heap.end());
};

OrderBookItem MaxHeap::peek_top() {
    return heap[0];
};

OrderBookItem MaxHeap::pop_top() {
    pop_heap(heap.begin(), heap.end());
    OrderBookItem top = heap.back();
    heap.pop_back();
    return top;
};

bool MaxHeap::is_empty() {
    return heap.begin() == heap.end();
};

void MaxHeap::update_top_item_quantity(int newQuantity) {
    heap[0].setQty(newQuantity);
};

MinHeap::MinHeap(vector<OrderBookItem> values) {
    heap = values;
    make_heap(heap.begin(), heap.end(), greater<>{});
};

MinHeap::MinHeap() {
    vector<OrderBookItem> v({});
    heap = v;
    make_heap(heap.begin(), heap.end(), greater<>{});
};

void MinHeap::insert(OrderBookItem value) {
    heap.push_back(value);
    push_heap(heap.begin(), heap.end(), greater<>{});
};

OrderBookItem MinHeap::peek_top() {
    return heap[0];
};

OrderBookItem MinHeap::pop_top() {
    pop_heap(heap.begin(), heap.end(), greater<>{});
    OrderBookItem top = heap.back();
    heap.pop_back();
    return top;
};

bool MinHeap::is_empty() {
    return heap.begin() == heap.end();
};

void MinHeap::update_top_item_quantity(int newQuantity) {
    heap[0].setQty(newQuantity);
}

