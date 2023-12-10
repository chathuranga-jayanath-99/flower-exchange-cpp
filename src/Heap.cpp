#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

class Heap {
    public:
        void insert(int value);  
        int pop_top();
        virtual bool is_empty() = 0; 
};

class MaxHeap : public Heap {
    private:
        vector<int> heap;

    public:
        MaxHeap(vector<int> values) {
            heap = values;
            make_heap(heap.begin(), heap.end());
        };

        void insert(int value) {
            heap.push_back(value);
            push_heap(heap.begin(), heap.end());
        }

        int pop_top() {
            pop_heap(heap.begin(), heap.end());
            int top = heap.back();
            heap.pop_back();
            return top;
        }

        bool is_empty() {
            return heap.begin() == heap.end();
        }
};

class MinHeap : public Heap {
    private:
        vector<int> heap;
    
    public:
        MinHeap(vector<int> values) {
            heap = values;
            make_heap(heap.begin(), heap.end(), greater<>{});
        }

        void insert(int value) {
            heap.push_back(value);
            push_heap(heap.begin(), heap.end(), greater<>{});
        }

        int pop_top() {
            pop_heap(heap.begin(), heap.end(), greater<>{});
            int top = heap.back();
            heap.pop_back();
            return top;
        }

        bool is_empty() {
            return heap.begin() == heap.end();
        }
};
