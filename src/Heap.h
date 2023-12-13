#ifndef HEAP_H
#define HEAP_H

#include "Order.h"
#include <string>
#include <vector>

using namespace std;

class Heap {
    public:
        virtual void insert(Order Order) = 0;
        virtual Order peek_top() = 0;  
        virtual Order pop_top() = 0;
        virtual bool is_empty() = 0; 
        virtual void update_top_item_quantity(int newQuantity) = 0;
};

class MaxHeap : public Heap {
    private:
        vector<Order> heap;

    public:
        MaxHeap(vector<Order> Orders);
        MaxHeap();
        void insert(Order Order);
        Order peek_top();
        Order pop_top();
        bool is_empty();
        void update_top_item_quantity(int newQuantity);
};

class MinHeap : public Heap {
    private:
        vector<Order> heap;
    
    public:
        MinHeap(vector<Order> Orders);
        MinHeap();
        void insert(Order Order);
        Order peek_top();
        Order pop_top();
        bool is_empty();
        void update_top_item_quantity(int newQuantity);
};

#endif