#include <algorithm>
#include <vector>
#include <iostream>
#include "Heap.h"

using namespace std;

MaxHeap::MaxHeap(vector<int> values) {
    heap = values;
    make_heap(heap.begin(), heap.end());
};

void MaxHeap::insert(int value) {
    heap.push_back(value);
    push_heap(heap.begin(), heap.end());
};

int MaxHeap::pop_top() {
    pop_heap(heap.begin(), heap.end());
    int top = heap.back();
    heap.pop_back();
    return top;
};

bool MaxHeap::is_empty() {
    return heap.begin() == heap.end();
};

MinHeap::MinHeap(vector<int> values) {
    heap = values;
    make_heap(heap.begin(), heap.end(), greater<>{});
};

void MinHeap::insert(int value) {
    heap.push_back(value);
    push_heap(heap.begin(), heap.end(), greater<>{});
};

int MinHeap::pop_top() {
    pop_heap(heap.begin(), heap.end(), greater<>{});
    int top = heap.back();
    heap.pop_back();
    return top;
};

bool MinHeap::is_empty() {
    return heap.begin() == heap.end();
};
